#include"window.h"

struct _Window
{
	int x,y;				/*top left*/
	int w,h;				/*width height*/
	int mx,my;				/*mouse window scale*/
	float dx,dy;			/*pixel deltas*/
	bool mouse;				/*true if mouse in window*/
	float fm[2];			/*mouse gl scale*/
	float matrix[16];
};

struct _Window *windowMalloc(int x,int y, int w, int h)
{
	struct _Window *W=malloc(sizeof(struct _Window));
	return windowSet(W,x,y,w,h);
}
struct _Window *windowSet(struct _Window *W,
						int x,int y, int w, int h)
{
	W->x=x;
	W->y=y;
	W->w=w;
	W->h=h;
	W->dx=2.0/w;
	W->dy=2.0/h;
	return W;
}

const struct _Window *windowUse(const struct _Window *W)
{
	glViewport(W->x,getWinHeight()-W->y-W->h,W->w,W->h);
	return W;
}
float windowDx(const struct _Window *w){return w->dx;}
float windowDy(const struct _Window *w){return w->dy;}

void windowBox(const struct _Window *w)
{
	float dx=2.0/w->w;
	float dy=2.0/w->h;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor4f(0,0,0,0);
	glDisable(GL_BLEND);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-1+dx,-1);
	glVertex2f( 1,-1);
	glVertex2f( 1, 1);
	glVertex2f(-1, 1-dy);
	glEnd();
	glPopAttrib();
}
float windowAspect(const struct _Window *w){return w->w/(float)w->h;}

//
void windowSetMouse(struct _Window *w,int x, int y)
{
	w->mouse=
	(	(x>=w->x)&&
		(x<=(w->x+w->w))&&
		(y>=w->y)&&
		(y<=(w->y+w->h))	);
	w->mx=x-w->x;
	w->my=y-w->y;
	w->fm[0]=(w->mx/(float)w->w)*2.0-1.0;
	w->fm[1]=1.0-(w->my/(float)w->h)*2.0;
}

void windowFill(const struct _Window *w)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-1,-1);
	glVertex2f( 1,-1);
	glVertex2f( 1, 1);
	glVertex2f(-1, 1);
	glEnd();
}
void windowWrite(const struct _Window *w,const char *name)
{
	uint8_t *buffer;
	int i,x,y;
	FILE *f;
	buffer=malloc(3*w->w*3*w->h);
	glReadPixels(w->x,getWinHeight()-w->y-w->h,w->w,w->h,
					GL_RGB,GL_UNSIGNED_BYTE,buffer);

	f=fopen(name,"wb");
	fprintf(f,"P3\n%d %d\n255\n",w->w,w->h);
	for(y=0;y<w->h;y++)
	{
		for(x=0;x<w->w;x++)
		{
			i=3*(x+(w->h-y)*w->w);
			fprintf(f,"%d %d %d\n",buffer[i],buffer[i+1],buffer[i+2]);
		}
	}
	fclose(f);
	free(buffer);
}
/*
	New stuff
*/
bool windowGetMouse(float *v,const struct _Window *w)
{
	v[0]=w->fm[0];
	v[1]=w->fm[1];
	v[2]=0.0f;
	v[3]=1.0f;
	return w->mouse;
}
const float *windowMat(const struct _Window *w)
{
	return w->matrix;
}
float *windowSetMat(struct _Window *w)
{
	return w->matrix;
}

