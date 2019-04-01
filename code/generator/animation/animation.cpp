#include "animation.h"
#include "animBall.h"
#include "animRain.h"
#include "animGrow.h"
#include <iostream>
#include <string.h>

using namespace std;

bool validAnimation(char* name)
{
	if(strcmp(name, "ball")==0)
		return true;
	if(strcmp(name, "rain")==0)
		return true;
	if(strcmp(name, "grow")==0)
		return true;
	return false;
}


Animation* makeAnim(char* name, float duration)
{
	Animation* a=NULL;
	if(strcmp(name, "ball")==0)
		a = new AnimBall(duration);
	if(strcmp(name, "rain")==0)
		a = new AnimRain(duration);
	if(strcmp(name, "grow")==0)
		a = new AnimGrow(duration);
	return a;
}

Animation::Animation(float dur)
{
	duration = dur;
}
