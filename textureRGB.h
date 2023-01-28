#ifndef _TEXTURERGB
#define _TEXTURERGB
#include<stdio.h>
#include<stdlib.h>
#include<GL/glx.h>
#include"util.h"
struct _TextureRGB
{
	int w, h;
	GLuint t;
	uint8_t *d;
};
struct _TextureRGB *textureRGBMake(struct _TextureRGB *t,int w, int h);
struct _TextureRGB *textureRGBRandom(struct _TextureRGB *t);
void textureRGBDestroy(struct _TextureRGB *t);
void textureRGBBind(const struct _TextureRGB *t);
void textureRGBWrite(struct _TextureRGB *t,const char *name);
#endif
