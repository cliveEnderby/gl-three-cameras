#include"textureRGB.h"

struct _TextureRGB *textureRGBMake(struct _TextureRGB *t,int w, int h)
{
	t->w=w;
	t->h=h;
	glGenTextures(1,&(t->t));
	if(t->t==0){fprintf(stderr,"1\n");exit(0);};
	t->d=malloc(3*w*h*sizeof(uint8_t));
	glBindTexture(GL_TEXTURE_2D,t->t);
	if(t->d==0){fprintf(stderr,"2\n");exit(0);};
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//NEAREST
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
				t->w,t->h,
				0,GL_RGB, GL_UNSIGNED_BYTE,t->d);
	return t;
}
struct _TextureRGB *textureRGBRandom(struct _TextureRGB *t)
{
	glBindTexture(GL_TEXTURE_2D,t->t);
	for(int i=0;i<3*t->w*t->h;i++)
		t->d[i]=rnd(0,255);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
					t->w,t->h,
					0,GL_RGB, GL_UNSIGNED_BYTE,t->d);
	return t;
}
void textureRGBDestroy(struct _TextureRGB *t)
{
	if(t->d)free(t->d);
}
void textureRGBBind(const struct _TextureRGB *t)
{
	glBindTexture(GL_TEXTURE_2D,t->t);
}
void textureRGBWrite(struct _TextureRGB *t,const char *name)
{
	int i,x,y;
	FILE *f;
	f=fopen(name,"wb");
	fprintf(f,"P3\n%d %d\n255\n",t->w,t->h);

	for(y=0;y<t->h;y++)
	{
		for(x=0;x<t->w;x++)
		{
			i=3*(x+(t->h-y)*t->w);
			fprintf(f,"%d %d %d\n",t->d[i],t->d[i+1],t->d[i+2]);
		}
	}

	fclose(f);
}
