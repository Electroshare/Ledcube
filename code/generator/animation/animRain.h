#ifndef ANIM_RAIN_H
#define ANIM_RAIN_H

#include "animation.h"

class AnimRain : public Animation
{
	private:
		int ex, ey;
		bool dirUp;
	public:
		AnimRain(float dur);
		Cube* nextFrame(Cube* cur);
		Cube* firstFrame(Cube* cur);
		~AnimRain();
};

#endif
