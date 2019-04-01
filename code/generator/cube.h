#ifndef CUBE_H
#define CUBE_H


class Cube
{
	private:
		char*** voxels;
	
	public:
		Cube();
		~Cube();
	
		char at(int i, int j, int k);
		void set(int i, int j, int k, char v);
		void setRange(int iStart, int iEnd, int jStart, int jEnd, int kStart, int kEnd, char v);
		void setRange(int iStart, int iEnd, int jStart, int jEnd, int kStart, int kEnd, char*** v);
		void setAll(char v);
};


#endif
