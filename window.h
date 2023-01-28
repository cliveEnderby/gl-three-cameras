#ifndef _WINDOW
#define _WINDOW
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<GL/gl.h>
#include"util.h"
#include"mat.h"
#include"eye.h"
#include"xWin.h"


struct _Window;

struct _Window *windowMalloc(int x,int y, int w, int h);
struct _Window *windowSet(struct _Window *W,
						int x,int y, int w, int h);
void windowCB(const struct _Window *W);
const struct _Window *windowUse(const struct _Window *W);
float windowDx(const struct _Window *w);
float windowDy(const struct _Window *w);
void windowBox(const struct _Window *w);
float windowAspect(const struct _Window *w);
void windowSetMouse(struct _Window *w,int x, int y);
void windowFill(const struct _Window *w);
void windowWrite(const struct _Window *w,const char *name);
bool windowGetMouse(float *v,const struct _Window *w);
const float *windowMat(const struct _Window *w);
float *windowSetMat(struct _Window *w);
#endif

