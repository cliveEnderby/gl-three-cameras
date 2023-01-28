#ifndef _LIST
#define _LIST
#include"mat.h"
#include"window.h"
struct _List;
void listPush(struct _List **l,
			float *v,
			void(*cb)(struct _Window *w,float *v));
void listCB(struct _List *l,struct _Window *w);

#endif

