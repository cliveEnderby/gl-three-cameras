#include"axis.h"

void axis(float *m)
{
	int i;
	float v[4];
	glBegin(GL_LINES);
	for(i=-50;i<50;i+=5)
	{
		glVertex4fv(matVec(v,m,(float[]){i,-1,-50,1}));
		glVertex4fv(matVec(v,m,(float[]){i,-1, 50,1}));
		glVertex4fv(matVec(v,m,(float[]){-50,-1,i,1}));
		glVertex4fv(matVec(v,m,(float[]){ 50,-1,i,1}));
	}
	glVertex4fv(matVec(v,m,(float[]){0,-50,0,1}));
	glVertex4fv(matVec(v,m,(float[]){0, 50,0,1}));
	glEnd();
}
