#include"cube.h"
/*
0-----1			a0
|\     \		b1
| \     \		c2
|  3-----2		d3
4  |  5  |		e4
 \ |     |		f5
  \|     |		g6
   7-----6		h7
*/

const float cube_vert[][4]={
	{-1.0,-1.0,-1.0, 1.0},		//a
	{ 1.0,-1.0,-1.0, 1.0},		//b
	{ 1.0, 1.0,-1.0, 1.0},		//c
	{-1.0, 1.0,-1.0, 1.0},		//d
	{-1.0,-1.0, 1.0, 1.0},		//e
	{ 1.0,-1.0, 1.0, 1.0},		//f
	{ 1.0, 1.0, 1.0, 1.0},		//g
	{-1.0, 1.0, 1.0, 1.0}	};	//h

const int cube_edge_idx[][2]={
		{0,1},	{1,2},	{2,3},	{3,0},		//ab bc cd da
		{4,7},	{7,6},	{6,5},	{5,4},		//ef fg gh he
		{0,4},	{1,5},	{2,6},	{3,7}	};	//ae bf cg dh

const int cube_triangle_idx[][3]={
		{0,3,2},{0,2,1},
		{0,1,5},{0,5,4},
		{0,4,7},{0,7,3},
		{6,2,3},{6,3,7},
		{6,5,1},{6,1,2},
		{6,7,4},{6,4,5}		};
		
void cubeDrawEdges(float *m)
{
	int i;
	float v[4];
	for(i=0;i<12;i++)
	{
	glBegin(GL_LINES);
		glVertex4fv(matVec(v,m,cube_vert[cube_edge_idx[i][0]]));
		glVertex4fv(matVec(v,m,cube_vert[cube_edge_idx[i][1]]));
	glEnd();
	}
}

