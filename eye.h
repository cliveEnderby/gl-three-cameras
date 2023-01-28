#ifndef _EYE
#define _EYE
#include"mat.h"

struct _Eye;

struct _Eye *eyeMake();
struct _Eye *eyeSet(struct _Eye *eye,float *p,float dir,float pitch);
const float *eyeGetMat(const struct _Eye *eye);
struct _Eye *eyeRot(struct _Eye *eye,float t);
struct _Eye *eyePitch(struct _Eye *eye,float t);
struct _Eye *eyeForward(struct _Eye *eye,float t);
struct _Eye *eyeUp(struct _Eye *eye,float t);
const char *eyeString(struct _Eye *eye);
#endif

