#include"program.h"
const char	*windowName	="Cube";
const bool	doubleBuffer=false;
const int	version		=21;
const int	winsize[]	={630,630};
bool 		running		=true;
float 		t			=0;
struct _KeyManager	*kManager	=0;
struct _List		*list		=0;
struct _Window		*window[3];
struct _Eye			*eye[3];
const int CUBE_COUNT=50;
float **cubeMats;
int focus;
float matO[16],matTemp1[16],matTemp2[16];
void mouse(int x,int y)
{
	windowSetMouse(window[0],x,y);
	windowSetMouse(window[1],x,y);
	windowSetMouse(window[2],x,y);
}
void keyed(KeySym k,bool d)
{
	if(d) keyManagerAddKey(&kManager,k);
	else keyManagerSubKey(&kManager,k);
}
void mouseRay(	const struct _Window	*win_this,
				const struct _Eye		*eye_this,
				const struct _Window	*win_that,
				const struct _Eye		*eye_that,
				const float *a,
				const float *b,
				const float *c)
{
	float v[4],vn[4],vf[4],hit[4];
	float mat[16];
	if(windowGetMouse(v,win_that))
	{
		matInverse(mat,windowMat(win_that));
		vecCopy(vn,v);
		vecCopy(vf,v);
		vn[2]=-1;
		vf[2]=1;
		matMultiMat(matO,(const float*[]){
			matInverse(matTemp1,eyeGetMat(eye_that)),
			mat,
			0});
		matVec(vn,eyeGetMat(eye_this),vecDivW(vn,matVec(vn,matO,vn)));
		matVec(vf,eyeGetMat(eye_this),vecDivW(vf,matVec(vf,matO,vf)));
		if(intersect(hit,vn,vf,a,b,c,eyeGetMat(eye_this)))
		{
			glPointSize(5);
			glBegin(GL_POINTS);
			glVertex4fv(matVec(v,windowMat(win_this),hit));
			glEnd();
			glBegin(GL_LINES);
			glVertex4fv(matVec(v,windowMat(win_this),vn));
			glVertex4fv(matVec(v,windowMat(win_this),hit));
			glEnd();
		}
	}
}
void clearWindow(int win)
{
	windowUse(window[win]);
	glColor4f(1,1,0.8,0);
	windowFill(window[win]);
	glColor4f(0,0,0,0);
}
void drawAxis(int win)
{
	matMultiMat(matO,(const float*[]){
			windowMat(window[win]),
			eyeGetMat(eye[win]),
			0});
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor4f(.8,.8,.8,1);
	axis(matO);
	glPopAttrib();
}
void drawCube(int win)
{
	matMultiMat(matO,(const float*[]){
			windowMat(window[win]),
			eyeGetMat(eye[win]),
			0});
	cubeDrawEdges(matO);
}
void drawCamRay(int this,int that,float near, float far)
{
	float v[4];
	windowUse(window[this]);
//Draw camera cube
	matMultiMat(matO,(const float*[]){
		windowMat(window[this]),
		eyeGetMat(eye[this]),
		matInverse(matTemp1,eyeGetMat(eye[that])),//set eye A in global space
		0});									//inverse as
	cubeDrawEdges(matO);
//Lable camera
	matVec(v,matO,(float[]){0,0,0,1});
	if(v[2]>0)textPlot(window[this],v[0]/v[3],v[1]/v[3],"%d",that);
//Draw camera frustum
	matMultiMat(matO,(const float*[]){
			windowMat(window[this]),
			eyeGetMat(eye[this]),
			matInverse(matTemp1,eyeGetMat(eye[that])),
			matInverse(matTemp2,matPerspective(matTemp2,M_PI/4,
				windowAspect(window[that]),near,far)),
			0});
	cubeDrawEdges(matO);
	textPrint(window[this],1,1,"%s",eyeString(eye[this]));
}

void update(int a,int b, int c)	//update window a,display cameras b,c
{
	float matO[16],v1[4],v2[4],v3[4];
	int i,j;
	static float q=0;
	q+=0.01;
	clearWindow(a);
	drawAxis(a);
	drawCamRay(a,b,1,3);
	drawCamRay(a,c,1,3);
	for(j=0;j<CUBE_COUNT;j++)
	{
	matMultiMat(matO,(const float*[]){
			windowMat(window[a]),
			eyeGetMat(eye[a]),
			cubeMats[j],
			0});
	glBegin(GL_LINES);
	for(i=0;i<12;i++)
	{
		glVertex4fv(matVec(v1,matO,cube_vert[cube_edge_idx[i][0]]));
		glVertex4fv(matVec(v1,matO,cube_vert[cube_edge_idx[i][1]]));
	}
	glEnd();
	for(i=0;i<12;i++)
	{		
		mouseRay(	window[a],eye[a],
					window[b],eye[b],
					matVec(v1,cubeMats[j],cube_vert[cube_triangle_idx[i][0]]),
					matVec(v2,cubeMats[j],cube_vert[cube_triangle_idx[i][1]]),
					matVec(v3,cubeMats[j],cube_vert[cube_triangle_idx[i][2]]));
		mouseRay(	window[a],eye[a],
					window[c],eye[c],
					matVec(v1,cubeMats[j],cube_vert[cube_triangle_idx[i][0]]),
					matVec(v2,cubeMats[j],cube_vert[cube_triangle_idx[i][1]]),
					matVec(v3,cubeMats[j],cube_vert[cube_triangle_idx[i][2]]));
	}
	}
}
void run()
{
	glClearColor(0.8,0.8,0.8,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	update(0,1,2);
	update(1,2,0);
	update(2,0,1);
	glFlush();
	if(keyManagerTest(kManager,XK_Left))eyeRot(eye[focus],-0.01);
	if(keyManagerTest(kManager,XK_Right))eyeRot(eye[focus],0.01);
	if(keyManagerTest(kManager,XK_Up))eyeForward(eye[focus],-.01);
	if(keyManagerTest(kManager,XK_Down))eyeForward(eye[focus],.01);
	if(keyManagerTest(kManager,XK_q))eyeUp(eye[focus],.002);
	if(keyManagerTest(kManager,XK_a))eyeUp(eye[focus],-.002);
	if(keyManagerTest(kManager,XK_w))eyePitch(eye[focus],0.001);
	if(keyManagerTest(kManager,XK_s))eyePitch(eye[focus],-0.001);
	if(keyManagerTest(kManager,XK_0))focus=0;
	if(keyManagerTest(kManager,XK_1))focus=1;
	if(keyManagerTest(kManager,XK_2))focus=2;
}
void setup()
{
	int i;
	float tmp1[16],tmp2[16],tmp3[16];
	cubeMats=malloc(CUBE_COUNT*sizeof(float *));
	for(i=0;i<CUBE_COUNT;i++)
	{
		cubeMats[i]=malloc(16*sizeof(float));
		matMultiMat(cubeMats[i],(const float*[]){
			matTranslate(tmp1,rnd(-40,40),0,rnd(-40,40)),
			matRotX(tmp2,rnd(-M_PI,M_PI)),
			matRotY(tmp3,rnd(-M_PI,M_PI)),
			0});
	}
	glPointSize(9);
	glLineWidth(1);
	eye[0]=eyeSet(eyeMake(),(float[]){ 0,90,0,1},0,M_PI/2);
	eye[1]=eyeSet(eyeMake(),(float[]){-10,0,0,1},M_PI/2,0);
	eye[2]=eyeSet(eyeMake(),(float[]){ 10,0,0,1},-M_PI/2,0);
	focus=0;

	window[0]=windowMalloc(10,10,610,400);
	matPerspective(windowSetMat(window[0]),M_PI/4,
									windowAspect(window[0]),1,150);

	window[1]=windowMalloc(10,420,300,200);
	matPerspective(windowSetMat(window[1]),M_PI/4,
									windowAspect(window[1]),1,150);

	window[2]=windowMalloc(320,420,300,200);
	matPerspective(windowSetMat(window[2]),M_PI/4,
									windowAspect(window[1]),1,150);

	setMousemove(mouse);
	setKey(keyed);
	setRun(run,5000);
}
