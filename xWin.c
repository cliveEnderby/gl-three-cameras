#include "xWin.h"
extern const char	*windowName;
extern bool 		doubleBuffer;
extern void 		setup();
extern bool 		running;
extern int			version;
extern const int	winsize[2];
static int context_attribs[] = {	GLX_CONTEXT_MAJOR_VERSION_ARB,2,
										GLX_CONTEXT_MINOR_VERSION_ARB,1,None};
static bool ctxErrorOccurred = false;
static useconds_t tim;
static bool redraw;
static Window *win;
static Display *disp;
static int winHeight;
static void (*run)() = 0;
static void (*resize)(int x,int y) = 0;
static void (*mousemove)(int x,int y) = 0;
static void (*mousebuttonpress)(int b) = 0;
static void (*mousebuttonrelease)(int b) = 0;
static void (*keypress)(KeySym k) = 0;
static void (*keyrelease)(KeySym k) = 0;
static void (*keyd)(KeySym k,bool d) =0;
/////////////////////////////////////////////////////
void setRun(void(*r)(), unsigned int t){run=r;tim=t;}
void setResize(void(*r)(int x, int y)){resize=r;}
void setMousemove(void(*r)(int x,int y)){mousemove=r;}
void setMousebuttonpress(void(*r)(int b)){mousebuttonpress = r;}
void setMousebuttonrelease(void(*r)(int b)){mousebuttonrelease = r;}
void setKeypress(void(*r)(KeySym k)){keypress=r;}
void setKeyrelease(void(*r)(KeySym k)){keyrelease=r;}
void setKey(void(*r)(KeySym k, bool d)){keyd=r;}
int getWinHeight(){return winHeight;}

static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
	ctxErrorOccurred = true;
	return 0;
}
static bool isExtensionSupported(const char *list, const char *ext)
{
	const char *l=list, *e=ext;
	for(l=list;*l!='\0';l++)
	{
		if(*e=='\0' &&(*l == ' ' || *l == '\0') )return true;
		if(*e != *l)e=ext; else e++;
	}
	return false;
}
////////////////////////////////
void makeWindow(Window *window, Display **display)
{
	const int visual_attribs[] =
	{
	GLX_RENDER_TYPE		,GLX_RGBA_BIT,
	GLX_DEPTH_SIZE	,24,
	None
	};
/*	GLX_X_RENDERABLE	,True,
	GLX_DRAWABLE_TYPE	,GLX_WINDOW_BIT,
	GLX_X_VISUAL_TYPE	,GLX_TRUE_COLOR,
	GLX_RED_SIZE	,8,
	GLX_GREEN_SIZE	,8,
	GLX_BLUE_SIZE	,8,
	GLX_ALPHA_SIZE	,8,
	GLX_STENCIL_SIZE	, 8,
	GLX_SAMPLE_BUFFERS  , 1,
	GLX_SAMPLES		 , 4,
	GLX_DOUBLEBUFFER	, doubleBuffer,
	None
	};
*/
	int fbcount;
	int glxVersion,glxVersion2;
	Colormap cmap;
	XVisualInfo *vi;
	GLXFBConfig *fbcList, fbc;
	XSetWindowAttributes swa;

	typedef GLXContext (*glXCreateContextAttribsARBProc)
					(Display*, GLXFBConfig, GLXContext, Bool, const int*);
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB;
	GLXContext ctx = 0;
	bool ctxErrorOccurred = false; 
	int (*oldHandler)(Display*, XErrorEvent*);
//
	run = 0;
	resize = 0;
	win = window;
	disp =disp;
//	 
	*display = XOpenDisplay(":0");
//
	glXQueryVersion( *display, &glxVersion, &glxVersion2 );
	if((glxVersion=(10*glxVersion + glxVersion2)) <13 )
	{
		printf("Invalid GLX version\n");
		exit(1);
	}
	printf("glx=%d\n",glxVersion);
//	
	fbcList = glXChooseFBConfig(*display, DefaultScreen(display),
							visual_attribs, &fbcount);
	if(fbcList == NULL)
	{
		printf("No frame buffers with required spec\n");
		exit(1);
	}

	printf("there are %d possible frame buffers\n",fbcount);
	fbc =fbcList[0]; //use the first fbc returned
	XFree(fbcList); //and free the list	
//
	vi = glXGetVisualFromFBConfig( *display, fbc );
//  printf("Using visual ID 0x%lx\n",vi->visualid);
//
	swa.colormap = cmap = XCreateColormap( *display,
								RootWindow( *display, vi->screen),
								vi->visual, AllocNone);
	swa.background_pixmap   = None;
	swa.border_pixel		= 0;
	swa.event_mask		  =   StructureNotifyMask | ExposureMask |
								KeyPressMask | KeyReleaseMask |
								PointerMotionMask | ButtonPressMask | ButtonReleaseMask;
//
	*window = XCreateWindow( *display,
							RootWindow( *display, vi->screen),
							20,20,winsize[0],winsize[1],0,vi->depth,
							InputOutput,
							vi->visual,
							CWBorderPixel|CWColormap|CWEventMask,
							&swa);
	if( *window == 0)
	{
		printf("Failed to create Window\n");
		exit(1);
	}
//
	const char *glxExts = glXQueryExtensionsString( *display,
													DefaultScreen( display ) );
//
	XFree(vi);
//
	XStoreName( *display, *window, windowName );
	XMapWindow( *display, *window );
	glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
		   glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
	if( glXCreateContextAttribsARB == NULL )
	{
		printf("Failed to get glXContextAttribsARB\n");
		exit(1);
	};
	oldHandler = XSetErrorHandler(ctxErrorHandler);
	
	if ( !isExtensionSupported( glxExts, "GLX_ARB_create_context" ) )
	{
		printf("Extension GLX_ARB_create_context unavailable\n");
		exit(1);
	}
	context_attribs[1]=version/10;
	context_attribs[3]=version%10;
	ctx = glXCreateContextAttribsARB(*display, fbc, 0, True, context_attribs);
	if(!ctx)
	{
		printf("glXCreateContextAttribsARB failed\n");
		exit(1);
	}
	XSync( *display, False );
	if(ctxErrorOccurred)
	{
		printf("ctxErrorOccurred\n");
		exit(1);
	}
	XSetErrorHandler( oldHandler );
	
	glXMakeCurrent(*display, *window, ctx);

	XAutoRepeatOff(*display);	
}
void *toast(void *id)
{
	while(running)
	{
		usleep(tim);
		int *p = (int*)id;
		(*p)++;
		redraw=true;
	}
	return NULL;
}
void mainLoop(Window window, Display *display)
{

	pthread_t thread;
	XEvent xev;
	Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &wmDeleteMessage, 1);
	XWindowAttributes gwa;
	int i=0;
	pthread_create(&thread, NULL, toast, (void*)&i);
	setup();
	while(running)
	{
		if(XPending(display))
		{
			XNextEvent(display, &xev);
			if(xev.type == Expose)
			{
				XGetWindowAttributes(display, window, &gwa);
				winHeight=gwa.height;
				if(resize)
				{
					resize(gwa.width, gwa.height);
				}
			}
			if(xev.type == KeyPress)
			{
				KeySym k = XkbKeycodeToKeysym( display, xev.xkey.keycode, 
										0, xev.xkey.state & ShiftMask ? 1 : 0);
				if(keypress)keypress(k);
				if(keyd)keyd(k,true);
			}
			if(xev.type == KeyRelease)
			{
				KeySym k = XkbKeycodeToKeysym( display, xev.xkey.keycode, 
										0, xev.xkey.state & ShiftMask ? 1 : 0);
				if(keyrelease)keyrelease(k);
				if(keyd)keyd(k,false);
			}
			if(xev.type == MotionNotify)
			{
				if(mousemove)mousemove(	((XMotionEvent*)&xev)->x,
										((XMotionEvent*)&xev)->y	);
			}
			if((xev.type == ButtonPress) && (mousebuttonpress))
				mousebuttonpress(((XButtonEvent*)&xev)->button);
			if((xev.type == ButtonRelease) && (mousebuttonrelease))
				mousebuttonrelease(((XButtonEvent*)&xev)->button);
			if(xev.type == ClientMessage)
			{
				if (xev.xclient.data.l[0] == wmDeleteMessage)
					running = false;
			};
		}
		if(redraw && run)
		{
			run();
			glXSwapBuffers(display,window);
			redraw = false;
		};
	}
	XAutoRepeatOn(display);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}
