#include <iostream>
#include <vector>
#include <signal.h>
#include <chrono>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <string.h>
#include <time.h>
#include <random>
#include "cube.h"
#include "animation/animation.h"
#include "output/outputGraphics.h"
#include "output/outputNetwork.h"


using namespace std;
using namespace std::chrono;

void printUsage();
void sigHandler(int sig);

bool stopped = false;
const int FRAME_DURATION = 33; // duration of a frame in milliseconds

int main(int argc, char** argv)
{
	// Attach signal handler for SIGINT
	struct sigaction sig_struct;
	sig_struct.sa_handler = sigHandler;
	sigemptyset(&sig_struct.sa_mask);
	sig_struct.sa_flags = 0;

	sigaction(SIGINT, &sig_struct, NULL);

	// Seed random number generator
	srand(time(NULL));
	
	// Create base objects
	vector<Animation*> animList;
	
	// Parse inputs
	int argi = 1;                // position inside 'argv'
	bool parsingAnim = false;    // inside -a options list
	bool parsingNetwork = false; // inside -on options list
	bool parsingIndice= -1;      // indice inside an option list
	bool hasAll = false;         // -all flag
	bool hasGraphics = false;    // -og or -on specified
	bool doGraphics = true;      // -og or by default true
	bool doNetwork = false;      // -on activated
	bool hasError = false;       // the option list is invalid
	char* animName = NULL;       // the animation beeing read
	char* networkAdd = NULL;     // address of the network output
	while(argi < argc)
	{
		if(strcmp(argv[argi], "-all")==0){
			hasAll = true;
			parsingAnim = false;
			parsingNetwork = false;
			parsingIndice = -1;
		}
		else if(strcmp(argv[argi], "-a")==0){
			if(hasAll){
				hasError = true;
				break;
			}
			parsingAnim = true;
			parsingNetwork = false;
			parsingIndice = 0;
		}
		else if(strcmp(argv[argi], "-og")==0){
			if(hasGraphics){
				hasError = true;
				break;
			}
			doGraphics = true;
			hasGraphics = true;
			parsingAnim = false;
			parsingNetwork = false;
			parsingIndice = -1;
		}
		else if(strcmp(argv[argi], "-on")==0){
			if(hasGraphics){
				hasError = true;
				break;
			}
			doGraphics = false;
			doNetwork = true;
			hasGraphics = true;
			parsingIndice = 0;
			parsingAnim = false;
			parsingNetwork = true;
		}
		else if(strcmp(argv[argi], "-help")==0){
			hasError = true;
		}
		else if(parsingAnim){
			if(parsingIndice % 2 == 1){
				// anim type
				if(!validAnimation(argv[argi])){
					hasError = true;
					break;
				}
				animName = argv[argi];
			}else{
				// anim duration
				float duration = stof(argv[argi]);
				animList.push_back(makeAnim(animName, duration));
			}
		}
		else if(parsingNetwork){
			if(parsingIndice == 1){
				networkAdd = argv[argi];
				parsingIndice = -1;
				parsingNetwork = false;
			}
		}
		// next indicies
		argi ++;
		if(parsingIndice >= 0)
			parsingIndice++;
	}
	
	// show error
	if(hasError || (!hasAll && !animList.size())){
		printUsage();
		return 0;
	}
	
	// all animations
	if(hasAll){
		animList.push_back(makeAnim(strdup("ball"), 20));
		animList.push_back(makeAnim(strdup("rain"), 20));
		animList.push_back(makeAnim(strdup("grow"), 20));
	}
	
	// initialize output
	Output* out;
	if(doGraphics){
		out = new OutputGraphics();
	}else{
		out = new OutputNetwork(networkAdd);
	}
	out->start();
	
	// initialize cube
	Cube* c=new Cube();

	// initialize first animation
	int currentAnim = rand() % animList.size();
	currentAnim = 2;
	c = animList[currentAnim]->firstFrame(c);
	
	// Animate
	auto ts=high_resolution_clock::now();
	milliseconds frame_duration(FRAME_DURATION);

	auto tstart=system_clock::now();
	milliseconds animDuration((long)animList[currentAnim]->getDuration()*1000);

	cerr<<"start"<<endl;
	while(!stopped){
		// do one frame
		c = animList[currentAnim]->nextFrame(c);
		// wait for next frame
		ts += frame_duration;
		this_thread::sleep_until(ts);
		// output
		out->outputFrame(c);
		// change anim if needed
		if(high_resolution_clock::now() - tstart > animDuration){
			currentAnim = (currentAnim + 1) % animList.size();
			c = animList[currentAnim]->firstFrame(c);
			animDuration = milliseconds((long)animList[currentAnim]->getDuration()*1000);
			tstart=system_clock::now();
		}
	}
	cerr<<"stop gracefully"<<endl;
	
	// throw output
	out->stop();
	delete out;

	for(int i=0; i<animList.size(); i++)
		delete animList[i];
	
	return 0;
}

void printUsage()
{
	cerr<<"Utilisation: generator [-all | -a <a1> <t1> [...]] {[-og] | -on <add>}"<<endl;
	cerr<<endl;
	cerr<<" Options générales"<<endl;
	cerr<<"  -help        Affiche l'aide"<<endl;
	cerr<<endl;
	cerr<<" Options de génération"<<endl;
	cerr<<"  -all         Utilise toutes les animations"<<endl;
	cerr<<"  -a <a> <t>   Ajoute l'animation 'a' à la fin de la liste actuelle, sur une durée de 't' secondes"<<endl;
	cerr<<endl;
	cerr<<" Options de sorties"<<endl;
	cerr<<"  -og          Lance le programme de sortie graphique et l'utilise comme sortie. C'est la sortie par défaut"<<endl;
	cerr<<"  -on <add>    Transfert la sortie par un socket vers 'add'"<<endl;
}

void sigHandler(int sig)
{
	stopped = true;
}




