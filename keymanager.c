#include"keymanager.h"
struct _KeyManager
{
	KeySym k;
	struct _KeyManager *next;
};

void keyManagerAddKey(struct _KeyManager **km,KeySym k)
{
	k|=32;
	while(1)
	{
		if(*km==0)		//key not in list, add it.
		{
			*km=malloc(sizeof(struct _KeyManager));
			(*km)->k=k;
			(*km)->next=0;
			return;
		}
		if((*km)->k==k)return;	//key is in list, do nothing;
		km=&((*km)->next);
	}
	return;
}
void keyManagerSubKey(struct _KeyManager **km,KeySym k)
{
	k|=32;
	while(1)
	{
		if(*km==0)return;	//reached end of list
		if((*km)->k==k)		//key found in list delete it
		{
			struct _KeyManager *tmp=*km;
			*km=(*km)->next;
			free(tmp);
			return;
		}
		km=&((*km)->next);	//move to next;
	}
}
bool keyManagerTest(struct _KeyManager *km,KeySym k)
{
	k|=32;
	while(km)
	{
		if(km->k==k)return true;
		km=km->next;
	}
	return false;
}

void keyManagerListKeys(struct _KeyManager *km)
{
	while(km)
	{
		printf("%lu\n",km->k);
		km=km->next;
	}
}

