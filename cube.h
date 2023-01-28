#ifndef _CUBE
#define _CUBE
#include<GL/gl.h>
#include"mat.h"
extern const float cube_vert[][4];
extern const int cube_edge_idx[][2];
extern const int cube_triangle_idx[][3];
void cubeDrawEdges(float *m);
#endif

