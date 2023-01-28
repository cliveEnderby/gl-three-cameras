#include"intersect.h"
bool intersect(float *hit,
			const float *near,
			const float *far,
			const float *pa,
			const float *pb,
			const float *pc,
			const float *m)
{
	const float EPSILON = 0.0000001;
	float rayVector[4];
	float vA[4],vB[4],vC[4];
	float edge1[4],edge2[4];
	float h[4],s[4],q[4];
	float a,f,u,v,t;
	vecSub(rayVector,far,near);
	matVec(vA,m,pa);
	matVec(vB,m,pb);
	matVec(vC,m,pc);
	vecSub(edge1,vB,vA);
	vecSub(edge2,vC,vA);
	vecCross(h,rayVector,edge2);
	a=vecDot(edge1,h);
	if (a>-EPSILON&&a<EPSILON)return false;
	f=1.0/a;
	vecSub(s,near,vA);
	u=f*vecDot(s,h);
	if(u<0.0||u>1.0)return false;
	vecCross(q,s,edge1);
	v=f*vecDot(rayVector,q);
	if(v<0.0||u+v>1.0)return false;
	t=f*vecDot(edge2,q);
	if(t<=EPSILON)return false;
	vecMult(h,rayVector,t);
	vecAdd(hit,near,h);
	return true;
}


