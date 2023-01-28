#ifndef _INTERSECT
#define _INTERSECT
#include"util.h"
#include"mat.h"

bool intersect(float *hit,
			const float *near,
			const float *far,
			const float *a,
			const float *b,
			const float *c,
			const float *m);
#endif
