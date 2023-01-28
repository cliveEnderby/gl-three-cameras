#include"util.h"
float rnd(float a,float b)
{
	return a+(b-a)*rand()/(float)RAND_MAX;
}

