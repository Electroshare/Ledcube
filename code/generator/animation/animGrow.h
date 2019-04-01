#ifndef ANIM_GROW_H
#define ANIM_GROW_H

#include "animation.h"

class AnimGrow : public Animation
{
	private:
		int corner;
		int step;
		int cnter = 0;

		void plotWirecube(Cube* cur, int imin, int imax, int jmin, int jmax, int kmin, int kmax);
	public:
		AnimGrow(float dur);
		Cube* nextFrame(Cube* cur);
		Cube* firstFrame(Cube* cur);
		~AnimGrow();
};

#endif
