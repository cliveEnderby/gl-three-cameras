#include"ball.h"
void drawBall(float *m)
{
	float i;
	float v[4];
	glColor4f(0,0,0,0);

	glBegin(GL_LINE_STRIP);
	for(i=-1.0;i<=1.0;i+=0.002)
	{
		float r=sqrt(1-i*i);
		glVertex4fv(matVec(v,m,(float[]){r*sin(64*i),i,r*cos(64*i),1}));
	}
	glEnd();
}
