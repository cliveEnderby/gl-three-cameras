#include"drawVert.h"
static int vn=0;
void drawQuadsBFQ(const float *m,const float *v)
{

	float o[4][4];
	float ab[4],bc[4];
	float normal[4];
	int i;
	matVec(o[vn],m,v);
	vn++;
	if(vn<4)return;
	vn=0;
	vecSub(ab,o[0],o[1]);
	vecSub(bc,o[1],o[2]);
	vecCross(normal,ab,bc);
	if(vecDot(normal,o[0])<=0)return;
	glBegin(GL_LINE_LOOP);
	for(i=0;i<4;i++)
		glVertex4fv(o[i]);
	glEnd();
}

