#include "animGrow.h"
#include <iostream>
#include <random>

using namespace std;

AnimGrow::AnimGrow(float dur)
	:Animation(dur)
{
	cout<<"made animgrow:"<<dur<<endl;
	corner = 0;
	step = -1;
}
AnimGrow::~AnimGrow(){
}
void AnimGrow::plotWirecube(Cube* cur, int imin, int imax, int jmin, int jmax, int kmin, int kmax){
	cur->setRange(imin, imax, jmin, jmin, kmin, kmin, 8);
	cur->setRange(imin, imax, jmin, jmin, kmax, kmax, 8);
	cur->setRange(imin, imax, jmax, jmax, kmax, kmax, 8);
	cur->setRange(imin, imax, jmax, jmax, kmin, kmin, 8);

	cur->setRange(imin, imin, jmin, jmax, kmin, kmin, 8);
	cur->setRange(imin, imin, jmin, jmax, kmax, kmax, 8);
	cur->setRange(imax, imax, jmin, jmax, kmax, kmax, 8);
	cur->setRange(imax, imax, jmin, jmax, kmin, kmin, 8);

	cur->setRange(imin, imin, jmin, jmin, kmin, kmax, 8);
	cur->setRange(imin, imin, jmax, jmax, kmin, kmax, 8);
	cur->setRange(imax, imax, jmax, jmax, kmin, kmax, 8);
	cur->setRange(imax, imax, jmin, jmin, kmin, kmax, 8);

	if((imax > imin+1) && (jmax > jmin+1) && (kmax > kmin+1)){
		cur->setRange(imin+1, imax-1, jmin+1, jmax-1, kmin+1, kmax-1, 4);
	}
}
Cube* AnimGrow::firstFrame(Cube* cur)
{
	// Set cube
	cur->setAll(0);
	corner = 0;
	step = -1;
	return cur;
}
Cube* AnimGrow::nextFrame(Cube* cur)
{
	// Update values
	cnter ++;
	if(cnter%2 == 0)
		step -= 1;
	if(step <= 0){
		step = 14;
		corner = (corner+ 1+ rand()%6 )%8;
	}
	int cubeSize = (step>8)? step-8 : 8-step;

	int imin = ((corner&1) != 0)? 7-cubeSize : 0;
	int imax = ((corner&1) != 0)? 7 : cubeSize;

	int jmin = ((corner&2) != 0)? 7-cubeSize : 0;
	int jmax = ((corner&2) != 0)? 7 : cubeSize;

	int kmin = ((corner&4) != 0)? 7-cubeSize : 0;
	int kmax = ((corner&4) != 0)? 7 : cubeSize;
	
	// Set cube
	cur->setAll(0);
	plotWirecube(cur, imin, imax, jmin, jmax, kmin, kmax);
	return cur;
}
