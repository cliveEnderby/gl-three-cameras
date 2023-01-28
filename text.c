#include"text.h"
char str[100];
void grunt(const struct _Window *w,float x,float y)
{
	int i,ix,iy;
	GLubyte bits;

	glPushAttrib( GL_ALL_ATTRIB_BITS);
	glDisable(GL_BLEND);
	glPointSize(1);

	for(i=0;str[i]>0;i++)
	{
		if(str[i]>31&&str[i]<128)
		{
			glBegin(GL_POINTS);
			for(iy=0;iy<13;iy++)
			{
				bits=rasters[str[i]-32][iy];
				for(ix=0;ix<8;ix++)
				{
					if(bits&(128>>ix))
						glVertex2f(x+windowDx(w)*(i*8+ix+1),y+windowDy(w)*iy);
				}
			}
			glEnd();
		}
	}

	glPopAttrib();
}
void textPlot(const struct _Window *w,float x, float y, const char *s, ...)
{
	va_list st;
	va_start(st, s);
	vsnprintf(str,50,s,st);
	va_end(st);
	grunt(w,x,y);
}
void textPrint(const struct _Window *w,int x, int y, const char *s, ...)
{
	va_list st;
	va_start(st, s);
	vsnprintf(str,50,s,st);
	va_end(st);
	grunt(w,-1+windowDx(w)*(8*x),1-windowDy(w)*13*(y+1));
}

