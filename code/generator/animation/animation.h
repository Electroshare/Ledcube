#ifndef ANIMATION_H
#define ANIMATION_H

#include "../cube.h"

class Animation;

bool validAnimation(char* name);
Animation* makeAnim(char* name, float duration);


class Animation
{
	private:
		float duration;
	
	public:
		Animation(float dur);
		float getDuration(){return duration;}
		virtual Cube* nextFrame(Cube* cur){}
		virtual Cube* firstFrame(Cube* cur){}
};

#endif
