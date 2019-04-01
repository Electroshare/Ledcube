#include <GL/gl.h>
#include <GL/glu.h>
#include <chrono>
#include <iostream>
#include <math.h>
#include "draw.h"

std::string curFrame;
GLuint diamond_list;
GLuint base_list;
GLfloat diamond_vertex[6][3] = {{0.0f, 0.0f, -1.0f},
								{0.0f, 0.0f,  1.0f},
								{0.0f, -1.0f, 0.0f},
								{0.0f,  1.0f, 0.0f},
								{-1.0f, 0.0f, 0.0f},
								{ 1.0f, 0.0f, 0.0f}};
GLfloat base_vertex[8][3] = {{-1.0f,-1.0f,-1.0f},
							 {-1.0f,-1.0f, 1.0f},
							 {-1.0f, 1.0f,-1.0f},
							 {-1.0f, 1.0f, 1.0f},
							 { 1.0f,-1.0f,-1.0f},
							 { 1.0f,-1.0f, 1.0f},
							 { 1.0f, 1.0f,-1.0f},
							 { 1.0f, 1.0f, 1.0f}};

void initGL(){
	// GL settings
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Display list
	diamond_list = glGenLists(2);
	base_list = diamond_list +1;

	glNewList(diamond_list, GL_COMPILE);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3fv(diamond_vertex[0]);
	glVertex3fv(diamond_vertex[2]);
	glVertex3fv(diamond_vertex[4]);
	glVertex3fv(diamond_vertex[3]);
	glVertex3fv(diamond_vertex[5]);
	glVertex3fv(diamond_vertex[2]);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3fv(diamond_vertex[1]);
	glVertex3fv(diamond_vertex[2]);
	glVertex3fv(diamond_vertex[4]);
	glVertex3fv(diamond_vertex[3]);
	glVertex3fv(diamond_vertex[5]);
	glVertex3fv(diamond_vertex[2]);
	glEnd();
	glEndList();

	glNewList(base_list, GL_COMPILE);
	glBegin(GL_QUADS);
	glVertex3fv(base_vertex[0]);
	glVertex3fv(base_vertex[1]);
	glVertex3fv(base_vertex[3]);
	glVertex3fv(base_vertex[2]);

	glVertex3fv(base_vertex[4]);
	glVertex3fv(base_vertex[5]);
	glVertex3fv(base_vertex[7]);
	glVertex3fv(base_vertex[6]);

	glVertex3fv(base_vertex[0]);
	glVertex3fv(base_vertex[1]);
	glVertex3fv(base_vertex[5]);
	glVertex3fv(base_vertex[4]);

	glVertex3fv(base_vertex[2]);
	glVertex3fv(base_vertex[3]);
	glVertex3fv(base_vertex[7]);
	glVertex3fv(base_vertex[6]);

	glVertex3fv(base_vertex[0]);
	glVertex3fv(base_vertex[2]);
	glVertex3fv(base_vertex[6]);
	glVertex3fv(base_vertex[4]);

	glVertex3fv(base_vertex[1]);
	glVertex3fv(base_vertex[3]);
	glVertex3fv(base_vertex[7]);
	glVertex3fv(base_vertex[5]);
	glEnd();
	glEndList();
	
	// Variables
	curFrame = "";
	for(int i=0; i<512; i++)
		curFrame += 'a';
}

void resizeGL(int w, int h){
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1., 1., -1., 1., 1., 20.);
	gluPerspective(30.0f, (float)w/h, 1., 20.);
	glMatrixMode(GL_MODELVIEW);
}

void setGLframe(std::string frame){
	curFrame = frame;
}

void drawGL(){	
	// get the delta-time
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	long ts = now_ms.time_since_epoch().count();

	// draw
	glClearColor(0.8f, 0.8f, 0.8f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glPushMatrix();
	glRotatef(-60.0f, 1, 0, 0);
	glRotatef((float)(ts%20000)*360.0f/20000.0f, 0, 0, 1);
	//glRotatef(30.0f, 0, 0, 1);
	glScalef(0.16f, 0.16f, 0.16f);
	glScalef(2.0f, 2.0f, 2.0f);
	
	for(int k=0; k<8; k++){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				int val = curFrame[i*64 + j*8 + k] - 'a';
				float lvl = (float)val/8.0f;
				//glColor3f(0.1f, 0.1f, 0.8f*lvl);
				//glColor4f(0.8f*lvl, 0.1f, 0.1f, 0.5f);
				glColor4f(1.0f-0.8f*lvl, 1.0f-0.8f*lvl, 0.9f, 0.3f+0.7f*lvl);
				glPushMatrix();
				glTranslatef(i-3.5f, j-3.5f, k-3.5f);
				glScalef(0.2f, 0.2f, 0.2f);
				glCallList(diamond_list);
				glPopMatrix();
			}
		}
	}

	glPushMatrix();
	glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glScalef(5.0f, 5.0f, 1.0f);
	glCallList(base_list);
	glPopMatrix();

	glPopMatrix();
}





