#ifndef OUTPUT_H
#define OUTPUT_H

#include "../cube.h"

enum OutputType
{
	OUTPUT_GRAPHICS,
	OUTPUT_NETWORK
};

class Output
{
	private:
		OutputType type;

	protected:
		bool running=false;
	
	public:
		Output(OutputType t){type = t;};
		bool isRunning(){return running;}
		virtual void outputFrame(Cube* c){};
		virtual void start(){};
		virtual void stop(){};
};

#endif
