#include"eye.h"
static char buffer[50];
static int deg(float rad){return (int)(rad*180.0/M_PI);}
struct _Eye
{
	float pos[4];
	float dir;
	float pitch;
	float mat[16];
};
struct _Eye *eyeUpdate(struct _Eye *eye)
{
	float matX[16],matY[16],matP[16];
	matRotX(matX,eye->pitch);
	matRotY(matY,eye->dir);
	matTranslateV(matP,(float[]){-eye->pos[0],-eye->pos[1],-eye->pos[2],1});
	matMultiMat(eye->mat,(const float *[]){matX,matY,matP,0});
	return eye;
}
struct _Eye *eyeMake()
{
	return (struct _Eye*)malloc(sizeof(struct _Eye));
}
struct _Eye *eyeSet(struct _Eye *eye,float *p,float dir,float pitch)
{
	vecCopy(eye->pos,p);
	eye->dir=dir;
	eye->pitch=pitch;
	eyeUpdate(eye);
	return eye;
}
const float *eyeGetMat(const struct _Eye *eye)
{
	return eye->mat;
}

struct _Eye *eyeRot(struct _Eye *eye,float t)
{
	eye->dir+=t;
	return eyeUpdate(eye);
}
struct _Eye *eyePitch(struct _Eye *eye,float t)
{
	eye->pitch+=t;
	return eyeUpdate(eye);
}
struct _Eye *eyeForward(struct _Eye *eye,float t)
{
	vecAdd(eye->pos,eye->pos,(float[]){-t*sin(eye->dir),0,t*cos(eye->dir),0});
	return eyeUpdate(eye);
}
struct _Eye *eyeUp(struct _Eye *eye,float t)
{
	vecAdd(eye->pos,eye->pos,(float[]){0,t,0,0});
	return eyeUpdate(eye);
}
const char *eyeString(struct _Eye *eye)
{
	sprintf(buffer,"[%2.2f %2.2f %2.2f %2.2f]  %3d  %3d",
			eye->pos[0],eye->pos[1],eye->pos[2],eye->pos[3],
			deg(eye->dir),deg(eye->pitch));
	return buffer;
}
