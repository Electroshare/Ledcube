#include <iostream>
#include <signal.h>
#include <thread>
#include <sys/poll.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "draw.h"

using namespace std;

void sigHandler(int sig);

bool stopped = false;

int main(int argc, char** argv)
{
	// Variables for x display
	Display                 *dpy;
	Window                  root;
	GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo             *vi;
	Colormap                cmap;
	XSetWindowAttributes    swa;
	Window                  win;
	GLXContext              glc;
	XWindowAttributes       gwa;
	XEvent                  xev;

	struct timeval tv;

	// Attach signal handler for SIGINT
	struct sigaction sig_struct;
	sig_struct.sa_handler = sigHandler;
	sigemptyset(&sig_struct.sa_mask);
	sig_struct.sa_flags = 0;

	sigaction(SIGINT, &sig_struct, NULL);

	// Create X Display for opengl
	dpy = XOpenDisplay(NULL);
	if(dpy == NULL) {
		cerr<<"Cannot connect to X server"<<endl;
		exit(0);
	}
	root = DefaultRootWindow(dpy);
	vi = glXChooseVisual(dpy, 0, att);
	if(vi == NULL) {
		cerr<<"No appropriate visual found"<<endl;
		exit(0);
	} 
	else {
		//cout<<"Visual "<<hex<<(void *)vi->visualid<<" selected"<<endl;
	}
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	win = XCreateWindow(dpy, root, 0, 0, 500, 500, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "3DViewer");
		
	// Attach close-window handler
	Atom wmDeleteMessage = XInternAtom(dpy, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(dpy, win, &wmDeleteMessage, 1);
	
	// Get file descriptor
	int x11_fd = ConnectionNumber(dpy);

	// Create opengl context
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	initGL();

	// stdin input
	std::string curInput="";

	struct pollfd fds;
        fds.fd = 0;
        fds.events = POLLIN;

	bool readingFrame = false;
	int framePos = 0;
	
	cerr<<"start"<<endl;
	while(!stopped){
        	// Create a File Description Set containing x11_fd
		fd_set in_fds;
		FD_ZERO(&in_fds);
		FD_SET(x11_fd, &in_fds);

		// Set our timer
		tv.tv_usec = 32000;
		tv.tv_sec = 0;

		// Wait for X Event or a Timer
		if (select(x11_fd+1, &in_fds, 0, 0, &tv)){
			// X Event
			// Handle XEvents and flush the input 
			while(XPending(dpy)){
				XNextEvent(dpy, &xev);
				if(xev.type == Expose) {
					XGetWindowAttributes(dpy, win, &gwa);
					resizeGL(gwa.width, gwa.height);
					drawGL(); 
					glXSwapBuffers(dpy, win);
				}
				else if(xev.type == KeyPress) {
					//stopped = true;
				}
				else if(xev.type == ClientMessage) {
					if (xev.xclient.data.l[0] == wmDeleteMessage)
						stopped = true;
				}
			}
		}else{
			// Timer
			int counter = 0;
			while(counter < 1000){
				counter ++;
				int ret = poll(&fds, 1, 0);
				if(ret == 1){
					char c;
					cin>>c;
					if(readingFrame){
						curInput += c;
						framePos += 1;
						if(framePos == 512){
							curInput[512] = 0;
							setGLframe(curInput);
							readingFrame = false;
						}
					}else{
						if(c == 'F'){
							framePos = 0;
							readingFrame = true;
							curInput = "";
						}
					}
				}else if(ret != 0){
					stopped=true;
				}else{
					counter += 1000;
				}
			}
			// Redraw
			drawGL();
			glXSwapBuffers(dpy, win);
		}
	}
	cerr<<"Stop gracefully"<<endl;

        glXMakeCurrent(dpy, None, NULL);
        glXDestroyContext(dpy, glc);
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
	cerr<<"Closed"<<endl;	
	return 0;
}

void sigHandler(int sig)
{
	stopped = true;
}



