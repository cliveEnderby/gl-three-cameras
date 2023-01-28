#ifndef _TEXT
#define _TEXT
#include<stdio.h>
#include<stdarg.h>

#include"window.h"
#include"font.h"

void textPlot(const struct _Window *w,float x, float y, const char *s, ...);
void textPrint(const struct _Window *w,int x, int y, const char *s, ...);
#endif
