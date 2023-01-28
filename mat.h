#ifndef _MATRIX_H
#define _MATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

float *vecPoint(float *v,float x, float y, float z);
float *vecVec(float *v,float x,float y,float z);
float *vecQuat(float *v, float x,float y, float z, float w);
float *vecAdd(float *v,const float *m, const float *n);
float *vecDivW(float *v,const float *m);
float *vecSub(float *v,const float *m, const float *n);
float *vecMult(float *v, const float *m, float d);
float *vecCopy(float *v, const float *m);
float vecMag(const float *v);
float vecDot(const float *v, const float *w);
float *vecCross(float *v,const float *m, const float *n);
float *vecNorm(float *v, const float *m);
bool vecComp(const float *v, const float *m);
const float *vecPrint(const float *v);
float *matZero(float *m);
float *matOne(float *m);
const float *matPrint(const float *m);
float *matCopy(float *o,const float *m);
float *matTranslate(float *p, float x, float y, float z);
float *matTranslateV(float *p, const float *v);
float *matScale(float *p, float x, float y, float z);
float *matPerspective(float *p, float fov, float aspect, float near, float far);
float *matRotX(float *p, float a);  
float *matRotY(float *p, float a);
float *matRotZ(float *p, float a);
float *quatX(float *v,const float *m, const float *n);
float *matQuat(float *p, const float *v);
float *matOrtho(float *p, float left, float right, float bottom,
						float top, float near, float far);
float *matVec(float *o, const float *m, const float *v);
float *matMat(float *o, const float *m, const float *n);
float *matMultiMat(float *o,const float **ms);
float *matTranspose(float *o, const float *m);
float matCofactor(int p, const float *m);
float matDet(const float *m);
float *matInverse(float *out, const float *in);
#endif

