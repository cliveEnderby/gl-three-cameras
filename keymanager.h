#ifndef _KEYMANAGER
#define _KEYMANAGER
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<X11/XKBlib.h>

struct _KeyManager;
void keyManagerAddKey(struct _KeyManager **km,KeySym k);
void keyManagerSubKey(struct _KeyManager **km,KeySym k);
bool keyManagerTest(struct _KeyManager *km,KeySym k);
void keyManagerListKeys(struct _KeyManager *km);
#endif
