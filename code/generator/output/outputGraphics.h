#ifndef OUTPUT_GRAPHICS_H
#define OUTPUT_GRAPHICS_H

#include "output.h"

class OutputGraphics : public Output
{
	private:
		int aStdinPipe[2];
		int aStdoutPipe[2];
	public:
		OutputGraphics();
		void outputFrame(Cube* c);
		void start();
		void stop();
};

#endif
