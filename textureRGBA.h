#ifndef _TEXTURERGBA
#define _TEXTURERGBA
#include<stdio.h>
#include<stdlib.h>
#include<GL/glx.h>
#include<math.h>
#include"util.h"
struct _TextureRGBA;
struct _TextureRGBA *textureRGBAMake(struct _TextureRGBA *t,int w, int h);
struct _TextureRGBA *textureRGBARandom(struct _TextureRGBA *t);
struct _TextureRGBA *textureRGBAGrid(struct _TextureRGBA *t);
void textureRGBADestroy(struct _TextureRGBA *t);
void textureRGBABind(const struct _TextureRGBA *t);
void textureRGBAWrite(struct _TextureRGBA *t,const char *name);
#endif
