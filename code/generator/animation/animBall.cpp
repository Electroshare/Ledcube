#include "animBall.h"
#include <iostream>
#include <random>

using namespace std;

AnimBall::AnimBall(float dur)
	:Animation(dur)
{
	cout<<"made animball:"<<dur<<endl;
	ballShape = new char**[4];
	for(int i=0; i<4; i++){
		ballShape[i] = new char*[4];
		for(int j=0; j<4; j++){
			ballShape[i][j] = new char[4];
			for(int k=0; k<4; k++){
				ballShape[i][j][k] = 0;
				float dist = (i-1.5)*(i-1.5)+(j-1.5)*(j-1.5)+(k-1.5)*(k-1.5);
				if(dist <= 5)
					ballShape[i][j][k] = 2;
				if(dist <= 4)
					ballShape[i][j][k] = 5;
				if(dist <= 1)
					ballShape[i][j][k] = 8;
			}
		}
	}
	ballX = 1;
	ballY = 2;
	ballZ = 3;
	ballvX = ballvY = ballvZ = 0.5;
}
AnimBall::~AnimBall(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			delete ballShape[i][j];
		}
		delete ballShape[i];
	}
	delete ballShape;
}
float AnimBall::newv(float pos, float v)
{
	if (pos + v < -1)
		return (rand()%50+50.0f)/200.0f;
	if (pos + v > 5)
		return -(rand()%50+50.0f)/200.0f;
	return v;	
}
Cube* AnimBall::firstFrame(Cube* cur)
{
	// Set cube
	cur->setAll(0);
	return cur;
}
Cube* AnimBall::nextFrame(Cube* cur)
{
	// Bounce and advance
	ballvX = newv(ballX, ballvX);
	ballvY = newv(ballY, ballvY);
	ballvZ = newv(ballZ, ballvZ);
	ballX += ballvX;
	ballY += ballvY;
	ballZ += ballvZ;
	// Set cube
	cur->setAll(0);
	cur->setRange((int)ballX, (int)ballX+3, (int)ballY, (int)ballY+3, (int)ballZ, (int)ballZ+3, ballShape);
	return cur;
}
