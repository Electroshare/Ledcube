#include "animRain.h"
#include <iostream>
#include <random>

using namespace std;

AnimRain::AnimRain(float dur)
	:Animation(dur)
{
	cout<<"made animrain:"<<dur<<endl;
	ex = -1;
	ey = -1;
	dirUp = true;
}
AnimRain::~AnimRain(){
}
Cube* AnimRain::firstFrame(Cube* cur)
{
	cur->setAll(0);
	cur->setRange(0, 7, 0, 7, 7, 7, 8);
	ex = -1;
	ey = -1;
	return cur;
}
Cube* AnimRain::nextFrame(Cube* cur)
{
	if(ex==-1 && ey==-1){
		ex = rand()%8;
		ey = rand()%8;
		dirUp = cur->at(ex, ey, 0) == 8;
	}
	int pos = 0;
	while(cur->at(ex, ey, pos) != 8)
		pos+= 1;
	cur->set(ex, ey, pos, 0);
	if(dirUp)
		pos += 1;
	else
		pos -= 1;
	cur->set(ex, ey, pos, 8);
	if(pos == 0 || pos == 7){
		ex = -1;
		ey = -1;
	}
	return cur;
}
