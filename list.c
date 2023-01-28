#include"list.h"
struct _List
{
	float *v;
	void(*cb)(struct _Window *w,float *v);
	struct _List *next;
};
void listPush(struct _List **l,
			float *v,
			void(*cb)(struct _Window *w,float *v))
{
	struct _List *t=*l;
	*l=malloc(sizeof(struct _List));
	(*l)->v=malloc(4*sizeof(float));
	vecCopy((*l)->v,v);
	(*l)->cb=cb;
	(*l)->next=t;
}
void listCB(struct _List *l,struct _Window *w)
{
	while(l)
	{
		l->cb(w,l->v);
		l=l->next;
	}
}

