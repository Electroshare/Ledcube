#ifndef ANIM_BALL_H
#define ANIM_BALL_H

#include "animation.h"

class AnimBall : public Animation
{
	private:
		char*** ballShape = __null;
		float ballX, ballY, ballZ;
		float ballvX, ballvY, ballvZ;
		
		float newv(float pos, float v);
	public:
		AnimBall(float dur);
		Cube* nextFrame(Cube* cur);
		Cube* firstFrame(Cube* cur);
		~AnimBall();
};

#endif
