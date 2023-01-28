#ifndef _MYWIN
#define _MYWIN
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<GL/glx.h>
#include<pthread.h>

void setRun(void(*r)(), unsigned int t);		//useconds_t
void setResize(void(*r)(int x,int y));
void setMousemove(void(*r)(int x,int y));
void setMousebuttonpress(void(*r)(int b));
void setMousebuttonrelease(void(*r)(int b));
int getWinHeight();

void setKeypress(void(*r)(KeySym k));
void setKeyrelease(void(*r)(KeySym k));
void setKey(void(*r)(KeySym k, bool d));
void makeWindow(Window *window, Display **display);
void mainLoop(Window window, Display *display);
void closeWindow(Window window, Display *display);
#endif
