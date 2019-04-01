#include <stdexcept>
#include <iostream>
#include "cube.h"

#define min(a,b) ( ((a)<(b)) ? (a):(b) )
#define max(a,b) ( ((a)>(b)) ? (a):(b) )


using namespace std;

Cube::Cube()
{
	voxels = new char**[8];
	for(int i=0;i <8; i++){
		voxels[i] = new char*[8];
		for(int j=0;j<8; j++){
			voxels[i][j] = new char[8];
			for(int k=0; k<8; k++)
				voxels[i][j][k] = 0;
		}
	}
}

Cube::~Cube()
{
	for(int i=0;i <8; i++){
		for(int j=0;j<8; j++)
			delete voxels[i][j];
		delete voxels[i];
	}
	delete voxels;
}

char Cube::at(int i, int j, int k)
{
	if((i<0) || (i>=8))
		throw out_of_range("first indice");
	if((j<0) || (j>=8))
		throw out_of_range("second indice");
	if((k<0) || (k>=8))
		throw out_of_range("third indice");
	return voxels[i][j][k];
}
void Cube::set(int i, int j, int k, char v)
{
	if((i<0) || (i>=8))
		throw out_of_range("first indice");
	if((j<0) || (j>=8))
		throw out_of_range("second indice");
	if((k<0) || (k>=8))
		throw out_of_range("third indice");
	voxels[i][j][k] = v;
}
void Cube::setRange(int iStart, int iEnd, int jStart, int jEnd, int kStart, int kEnd, char v)
{
	for(short i=max(iStart, 0); i<=min(iEnd, 7); i++)
		for(short j=max(jStart, 0); j<=min(jEnd, 7); j++)
			for(short k=max(kStart, 0); k<=min(kEnd, 7); k++)
				voxels[i][j][k] = v;
}
void Cube::setRange(int iStart, int iEnd, int jStart, int jEnd, int kStart, int kEnd, char*** v)
{
	for(short i=max(iStart, 0); i<=min(iEnd, 7); i++)
		for(short j=max(jStart, 0); j<=min(jEnd, 7); j++)
			for(short k=max(kStart, 0); k<=min(kEnd, 7); k++){
				voxels[i][j][k] = v[i-iStart][j-jStart][k-kStart];
			}
}
void Cube::setAll(char v)
{
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			for(int k=0; k<8; k++)
				voxels[i][j][k] = v;
}

