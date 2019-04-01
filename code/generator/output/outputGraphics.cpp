#include "outputGraphics.h"
#include <iostream>
#include <unistd.h>
#include <string.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

using namespace std;

OutputGraphics::OutputGraphics()
	:Output(OUTPUT_GRAPHICS)
{
}

void OutputGraphics::outputFrame(Cube* c)
{
	if(running){
		char message[515];
		message[0] = 'F';
		for(int i=0;i<8;i++)
			for(int j=0; j<8; j++)
				for(int k=0; k<8; k++)
					message[1+i*64+j*8+k] = (char)(c->at(i,j,k) + (int)'a');
		message[513] = '\n';
		message[514] = '\0';
		write(aStdinPipe[PIPE_WRITE], message, strlen(message));
	}
}

void OutputGraphics::start()
{
	int nChild;
	char nChar;
	int nResult;

 	if (pipe(aStdinPipe) < 0) {
		perror("allocating pipe for child input redirect");
		//return -1;
		return;
	}
	if (pipe(aStdoutPipe) < 0) {
		close(aStdinPipe[PIPE_READ]);
		close(aStdinPipe[PIPE_WRITE]);
		perror("allocating pipe for child output redirect");
		//return -1;
		return;
	}
	cerr<<"Pipe ok"<<endl;

	nChild = fork();
	if (0 == nChild) {
		// child continues here

		// redirect stdin
		if (dup2(aStdinPipe[PIPE_READ], STDIN_FILENO) == -1) {
			cerr<<"child 1"<<endl;
			exit(errno);
		}

		// redirect stdout
		if (dup2(aStdoutPipe[PIPE_WRITE], STDOUT_FILENO) == -1) {
			cerr<<"child 2"<<endl;
			exit(errno);
		}

		// redirect stderr
		/*
		if (dup2(aStdoutPipe[PIPE_WRITE], STDERR_FILENO) == -1) {
			cerr<<"child 3"<<endl;
			exit(errno);
		}
		*/

		// all these are for use by parent only
		close(aStdinPipe[PIPE_READ]);
		close(aStdinPipe[PIPE_WRITE]);
		close(aStdoutPipe[PIPE_READ]);
		close(aStdoutPipe[PIPE_WRITE]); 

		// run child process image
		const char* arg = "3Dview";
		nResult = execl("../3Dview/3Dview", arg, NULL);

		// if we get here at all, an error occurred, but we are in the child
		// process, so just exit
		exit(nResult);
	} else if (nChild > 0) {
		// parent continues here

		// close unused file descriptors, these are for child only
		close(aStdinPipe[PIPE_READ]);
		close(aStdoutPipe[PIPE_WRITE]); 

		running = true;
	} else {
		// failed to create child
		close(aStdinPipe[PIPE_READ]);
		close(aStdinPipe[PIPE_WRITE]);
		close(aStdoutPipe[PIPE_READ]);
		close(aStdoutPipe[PIPE_WRITE]);
	}
	//return nChild;
}

void OutputGraphics::stop()
{
	close(aStdinPipe[PIPE_WRITE]);
	close(aStdoutPipe[PIPE_READ]);
}
