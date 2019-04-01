#ifndef OUTPUT_NETWORK_H
#define OUTPUT_NETWORK_H

#include "output.h"

class OutputNetwork : public Output
{
	private:
		char* add;
	
	public:
		OutputNetwork(char* add);
		void outputFrame(Cube* c);
		void start();
		void stop();
};

#endif
