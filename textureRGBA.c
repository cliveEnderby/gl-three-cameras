#include"textureRGBA.h"

struct _TextureRGBA
{
	int w, h;
	GLuint t;
	uint8_t *d;
};

struct _TextureRGBA *textureRGBAMake(struct _TextureRGBA *t,int w, int h)
{
	t->w=w;
	t->h=h;
	glGenTextures(1,&(t->t));
	if(t->t==0){fprintf(stderr,"1\n");exit(0);};
	t->d=malloc(4*w*h*sizeof(uint8_t));
	glBindTexture(GL_TEXTURE_2D,t->t);
	if(t->d==0){fprintf(stderr,"2\n");exit(0);};
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//NEAREST
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
				t->w,t->h,
				0,GL_RGBA, GL_UNSIGNED_BYTE,t->d);
	return t;
}

struct _TextureRGBA *textureRGBARandom(struct _TextureRGBA *t)
{
	int x,y,i;
	glBindTexture(GL_TEXTURE_2D,t->t);
	for(y=0;y<t->h;y++)
	{
		for(x=0;x<t->w;x++)
		{
			i=4*(y*t->w+x);
			t->d[i+0]=rnd(0,255);//r
			t->d[i+1]=rnd(0,255);//g
			t->d[i+2]=rnd(0,255);//b
			t->d[i+3]=rnd(0,255);
		}
	}
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
					t->w,t->h,
					0,GL_RGBA, GL_UNSIGNED_BYTE,t->d);
	return t;
}
struct _TextureRGBA *textureRGBAGrid(struct _TextureRGBA *t)
{
	int x,y,i;
	int l;
	glBindTexture(GL_TEXTURE_2D,t->t);
	for(y=0;y<t->h;y++)
	{
		for(x=0;x<t->w;x++)
		{
			l=((x%10==0)|(y%10==0))?0:255-rnd(0,32);
			i=4*(y*t->w+x);
			t->d[i+0]=l;//r
			t->d[i+1]=l;//g
			t->d[i+2]=l*0.9;//b
			t->d[i+3]=128;
		}
	}
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
					t->w,t->h,
					0,GL_RGBA, GL_UNSIGNED_BYTE,t->d);
	return t;
}
void textureRGBADestroy(struct _TextureRGBA *t)
{
	if(t->d)free(t->d);
}
void textureRGBABind(const struct _TextureRGBA *t)
{
	glBindTexture(GL_TEXTURE_2D,t->t);
}
void textureRGBAWrite(struct _TextureRGBA *t,const char *name)
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
