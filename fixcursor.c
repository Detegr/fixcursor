#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc>1)
	{
		if(strcmp(argv[1], "-d")==0)
		{
			pid_t pid;
			pid=fork();
			if(pid<0) {printf("Failed to daemonize.\n"); return 1;}
			if(pid>0) {printf("Daemon running...\n"); return 0;}
		}
	}
	int border1=10; int border2=0;
	unsigned int w1,h1,x1,y1,w2,h2,x2,y2;
	w1=w2=1920; h1=h2=1080;
	x1=y1=0; x2=1920; y2=1080;

	Display* display;
	display = XOpenDisplay(getenv("DISPLAY"));
	if(!display)
	{
		fprintf( stderr, "\nCannot connect to X server '%s'\n", getenv("DISPLAY"));
		exit(1);
	}
	Window w=DefaultRootWindow(display);
	Window c;
	for (;;)
	{
		int wx, wy, rx, ry;
		unsigned int m;
		XQueryPointer(display, w, &w, &c, &rx, &ry, &wx, &wy, &m);
		#ifdef DEBUG
			printf("Mouse X:%d, Y:%d, WX:%d, WY:%d\n", rx, ry, wx, wy);
		#endif
		if(rx>x1+w1+border1 && ry<y2-150)
		{
			XWarpPointer(display, None, None, 0,0,0,0,-(rx-(x1+w1)-border2), 0);
		}
		else if(rx>x1+w1+border1 && ry<y2-border1)
		{
			XWarpPointer(display, None, None, 0,0,0,0,0,-(ry-(y2)-border2));
		}
		else if(rx<x1+w1-150 && ry>y2+border1)
		{
			XWarpPointer(display, None, None, 0,0,0,0,0,-(ry-(y2)+border2));
		}
		else if(rx<x1+w1 && ry>y2+border1)
		{
			XWarpPointer(display, None, None, 0,0,0,0,-(rx-(x2)+border2),0);
		}
		usleep(5000);
	}
	XCloseDisplay( display );
	_exit(0);
}
