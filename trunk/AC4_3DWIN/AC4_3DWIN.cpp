/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

#include <process.h>
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <math.h>
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
HANDLE Mutex=0;
bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
float ViewTurnX=45.0f,ViewTurnY=45.0f;
float ViewChanging[]={0.0f,0.0f,0.0f};
bool UseLight=false;
bool UseAlpha=false;
unsigned int TexID=0;
int TexW=0;
int TexH=0;
unsigned char * TexData=0;
bool TexChanged=false;
void ChangeTex()
{
	if(!TexChanged)
		return;
	TexChanged=false;
	if(TexID)
		glDeleteTextures(1, &TexID);
		glGenTextures( 1, &TexID );
		glBindTexture( GL_TEXTURE_2D, TexID ); 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexW, TexH, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, TexData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
GLfloat	rtri;				// Angle For The Triangle ( NEW )
GLfloat	rquad;				// Angle For The Quad ( NEW )
HWND ParentHWND=0;
HANDLE RenderThreadHANDLE=NULL;
float * Vecs=0;
float * Nors=0;
float * Texs=0;
float * PartTR=0;
int * PartInfo=0;
int VecSize=0;
int TexsSize=0;
int PartSize=0;
float WHEEL=0.0f;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
inline void EastPerspective(float fovyInDegrees, float aspectRatio,
                      float znear, float zfar,float * Matrix)
{
    float ymax, xmax;
    ymax = znear * tan(fovyInDegrees * 3.14159265358979323846f / 360.0f);
    xmax = ymax * aspectRatio;

	Matrix[0] = znear / xmax;
    Matrix[1] = 0.0;
    Matrix[2] = 0.0;
    Matrix[3] = 0.0;
    Matrix[4] = 0.0;
    Matrix[5] = znear / ymax;
    Matrix[6] = 0.0;
    Matrix[7] = 0.0;
    Matrix[8] = 0.0;
    Matrix[9] = 0.0;
    Matrix[10] = (-zfar - znear) / (zfar - znear);
    Matrix[11] = -1.0;
    Matrix[12] = 0.0;
    Matrix[13] = 0.0;
    Matrix[14] = (-2.0f*znear * zfar) /  (zfar - znear);
    Matrix[15] = 0.0;
}
float Pmat[16];
int w;
int h;
float msize=200.0f;
float mpos[3]={0.0f,0.0f,0.0f};
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };

extern "C" _declspec(dllexport) void ClearViewTurn()
{
	ViewTurnX=45.0f;
	ViewTurnY=45.0f;
	WHEEL=0.0f;
	ViewChanging[0]=0.0f;
	ViewChanging[1]=0.0f;
	ViewChanging[2]=0.0f;
}
void SetMatrix(int PartID)
{
	float Q[4];
	float T[4][4]={1.0f,0.0f,0.0f,0.0f,
										 0.0f,1.0f,0.0f,0.0f,
										 0.0f,0.0f,1.0f,0.0f,
										 0.0f,0.0f,0.0f,1.0f};
	float theta_z = PartTR[PartID*6+5];
	float theta_y = PartTR[PartID*6+4];
	float theta_x = PartTR[PartID*6+3];

	float cos_z_2 = cos(0.5f*theta_z);
	float cos_y_2 = cos(0.5f*theta_y);
	float cos_x_2 = cos(0.5f*theta_x);

	float sin_z_2 = sin(0.5f*theta_z);
	float sin_y_2 = sin(0.5f*theta_y);
	float sin_x_2 = sin(0.5f*theta_x);

Q[0] = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
Q[1] = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
Q[2] = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
Q[3] = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
    T[0][0] =   Q[0]*Q[0]+Q[1]*Q[1]-Q[2]*Q[2]-Q[3]*Q[3] ;
    T[0][1] =                    2*(Q[1]*Q[2]-Q[0]*Q[3]);
    T[0][2] =                    2*(Q[1]*Q[3]+Q[0]*Q[2]);

    T[1][0] =                    2*(Q[1]*Q[2]+Q[0]*Q[3]);
    T[1][1] =   Q[0]*Q[0]-Q[1]*Q[1]+Q[2]*Q[2]-Q[3]*Q[3] ;
    T[1][2] =                    2*(Q[2]*Q[3]-Q[0]*Q[1]);

    T[2][0] =                    2*(Q[1]*Q[3]-Q[0]*Q[2]);
    T[2][1] =                    2*(Q[2]*Q[3]+Q[0]*Q[1]);
    T[2][2] =   Q[0]*Q[0]-Q[1]*Q[1]-Q[2]*Q[2]+Q[3]*Q[3] ;
    T[3][0] =   PartTR[PartID*6];
    T[3][1] =   PartTR[PartID*6+1];
    T[3][2] =   PartTR[PartID*6+2];
	glMultMatrixf(&(T[0][0]));
}
int RenderPart(int PartID)
{
	int nextPartID = PartID + 1;
	if(PartSize>0)
	{
		glPushMatrix();
		SetMatrix(PartID);
		//glTranslatef(PartTR[PartID*6],PartTR[PartID*6+1],PartTR[PartID*6+2]);

		//glRotatef(PartTR[PartID*6+3]*180.0f,1.0f,0.0f,0.0f);
		//glRotatef(PartTR[PartID*6+4]*180.0f,0.0f,1.0f,0.0f);
		//glRotatef(PartTR[PartID*6+5]*180.0f,0.0f,0.0f,1.0f);

		
		glBegin(GL_TRIANGLES);
		for(int i=PartInfo[PartID*3+1];i<PartInfo[PartID*3+1]+PartInfo[PartID*3+2];i++)
		{
			glNormal3f(Nors[i*3+0],Nors[i*3+1], Nors[i*3+2]);
			glTexCoord2f(Texs[i*2+0],Texs[i*2+1]);
			glVertex3f(Vecs[i*3+0],Vecs[i*3+1], Vecs[i*3+2]);
		}
		glEnd();
	
		for(int i=0;i<PartInfo[PartID*3];i++)
		{
			nextPartID = RenderPart(nextPartID);
		}
		
		/*
		for(int j=0;j<PartSize;j++)
		{
			glBegin(GL_TRIANGLES);
			for(int i=PartInfo[j*3+1];i<PartInfo[j*3+1]+PartInfo[j*3+2];i++)
			{
				glNormal3f(Nors[i*3+0],Nors[i*3+1], Nors[i*3+2]);
				glTexCoord2f(Texs[i*2+0],Texs[i*2+1]);
				glVertex3f(Vecs[i*3+0],Vecs[i*3+1], Vecs[i*3+2]);
			}
			glEnd();
		}
		*/
		glPopMatrix();
		return nextPartID;
	}
	else
	{
		glBegin(GL_TRIANGLES);
		for(int i=0;i<VecSize/3;i++)
		{
			glNormal3f(Nors[i*3+0],Nors[i*3+1], Nors[i*3+2]);
			glTexCoord2f(Texs[i*2+0],Texs[i*2+1]);
			glVertex3f(Vecs[i*3+0],Vecs[i*3+1], Vecs[i*3+2]);
		}
		glEnd();
		return 0;
	}

}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	w=width;
	h=height;
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	EastPerspective(45.0f,(GLfloat)width/(GLfloat)height,10.0f,1000000.0f,Pmat);
	glLoadMatrixf(Pmat);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.5f, 1.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    GLfloat mat_shininess[]={50.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,LightAmbient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,LightDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One
	//glEnable(GL_LIGHTING);
	return TRUE;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	
	ViewTurnX+=ViewChanging[0];
	ViewTurnY+=ViewChanging[1];
	WHEEL+=ViewChanging[2];
	if(UseLight)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
	if(UseAlpha)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
	ChangeTex();
	glEnable(GL_TEXTURE_2D);
	WaitForSingleObject(Mutex,INFINITE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
											// Done Drawing The Triangle
	glLoadIdentity();
	//glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);
	glTranslatef(0.0f,0.0f,-msize*((100.0f+WHEEL)/100.0f));	
	
	glRotatef(ViewTurnY,1.0f,0.0f,0.0f);
	glRotatef(180.0f,1.0f,0.0f,0.0f); // 模型方向反的
	glRotatef(ViewTurnX,0.0f,1.0f,0.0f);// Done Drawing The Quad
	
	rtri+=1.2f;											// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=1.15f;										// Decrease The Rotation Variable For The Quad ( NEW )
	glColor3f(1.0f,1.0f,1.0f);
	if(!UseAlpha)
		RenderPart(0);
	else
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.99f);
		RenderPart(0);
		glAlphaFunc(GL_LEQUAL, 0.99f);
		glDepthMask(GL_FALSE);
		RenderPart(0);
		glDisable(GL_ALPHA_TEST); 
		glDepthMask(GL_TRUE);
	}

	ReleaseMutex(Mutex);
	return TRUE;										// Keep Going
}



GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{


	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	//if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW|WS_EX_TOPMOST;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		//ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	//else
	//{
	//	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	//	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	//}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								WS_CHILD,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								ParentHWND,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	//SetForegroundWindow(hWnd);						// Slightly Higher Priority
	//SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		case WM_LBUTTONUP:
			{
				SetFocus(hWnd);
				return 0;
			}
		
		case WM_MOUSEWHEEL:
			{
			WHEEL-=(float)(short)HIWORD (wParam)*0.1f;
			return 0;
			}
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

BOOL	done=FALSE;	

unsigned int __stdcall RenderThread(LPVOID lpvoid)
{
	MSG		msg;									// Windows Message Structure
							// Bool Variable To Exit Loop


	fullscreen=FALSE;
	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's Rotation Tutorial",640,480,32,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active && !DrawGLScene()) 	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}
		}
		Sleep(10);
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	ReleaseMutex(Mutex);
	CloseHandle(Mutex);
	return 0;
}
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	RenderThread(0);
	return 0;							// Exit The Program
}
extern "C" _declspec(dllexport) void InitRenderThread(HWND EditerHWND)
{
	Mutex=CreateMutexW(NULL,false,L"AC4_3DWIN_Mutex");
	ParentHWND=EditerHWND;
	RenderThreadHANDLE = (HANDLE)_beginthreadex(0,0,(unsigned int (__stdcall *)(void *))RenderThread,0,CREATE_SUSPENDED,0);
	ResumeThread(RenderThreadHANDLE);
}
extern "C" _declspec(dllexport) void Set3DData(float * VecsIn,float * NorsIn,int VecSizeIn,float * TexsIn,int TexsSizeIn)
{
	WaitForSingleObject(Mutex,INFINITE);
	if(Vecs) delete [] Vecs;
	if(Nors) delete [] Nors;
	if(Texs) delete [] Texs;
	VecSize=VecSizeIn;
	TexsSize=TexsSizeIn;
	Vecs=new float [VecSize];
	Nors=new float [VecSize];
	Texs=new float [TexsSize];

	memcpy_s(Vecs,sizeof(float)*VecSizeIn,VecsIn,sizeof(float)*VecSizeIn);
	memcpy_s(Nors,sizeof(float)*VecSizeIn,NorsIn,sizeof(float)*VecSizeIn);
	memcpy_s(Texs,sizeof(float)*TexsSizeIn,TexsIn,sizeof(float)*TexsSizeIn);

	for(int i=0;i<VecSizeIn;i++)
		msize=max(msize,abs(Vecs[i]));
	msize=min(1000.0f,msize);
	ClearViewTurn();
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetPartData(float * PartTRIn,int * PartInfoIn,int PartSizeIn)
{
	WaitForSingleObject(Mutex,INFINITE);

	if(PartTR) delete [] PartTR;
	if(PartInfo) delete [] PartInfo;
	PartSize=PartSizeIn;

	PartTR=new float [PartSizeIn*6];
	PartInfo=new int [PartSizeIn*3];

	memcpy_s(PartTR,sizeof(float)*PartSizeIn*6,PartTRIn,sizeof(float)*PartSizeIn*6);
	memcpy_s(PartInfo,sizeof(int)*PartSizeIn*3,PartInfoIn,sizeof(int)*PartSizeIn*3);
	ClearViewTurn();
	ReleaseMutex(Mutex);
}

extern "C" _declspec(dllexport) void CloseRenderThread()
{
	done=1;
}
extern "C" _declspec(dllexport) void InputTex(unsigned char * TexDataIn,int SizeX,int SizeY,int DataSize)
{
	WaitForSingleObject(Mutex,INFINITE);
	TexW=SizeX;
	TexH=SizeY;
	
	if(TexData) delete [] TexData;
	TexData=new unsigned char[DataSize];
	memcpy_s(TexData,DataSize,TexDataIn,DataSize);
	TexChanged=true;
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void LightSwitch(bool Use)
{
	UseLight=Use;
}
extern "C" _declspec(dllexport) void AlphaSwitch(bool Use)
{
	UseAlpha=Use;
}
extern "C" _declspec(dllexport) void ChangeView(float TurnX,float TurnY,float TurnZ)
{
	WaitForSingleObject(Mutex,INFINITE);
	ViewChanging[0]=TurnX;
	ViewChanging[1]=TurnY;
	ViewChanging[2]=TurnZ;
	ReleaseMutex(Mutex);
}