#include "AC4_3DWIN2.h"
#include <process.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL\glew.h"
#include"GL\glfw.h"
#include"AC4Map.h"
#include "NodeMath.h"
NodeMath * ViewMAth;
//AC4Map * Map=0;
#ifdef _DEBUG
#pragma comment( lib, "glew32sd.lib" )
#pragma comment( lib, "GLFWd.lib" )
#else
#pragma comment( lib, "glew32s.lib" )
#pragma comment( lib, "GLFW.lib" )
#endif
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
int winwidth=640, winheight=480;
HWND ParentHWND=0;
HANDLE RenderThreadHANDLE=NULL;
extern HANDLE Mutex=0;
float ViewTurnX=45.0f,ViewTurnY=45.0f;
bool UseLight=false;
bool UseAlpha=false;
unsigned int TexID=0;
int TexW=0;
int TexH=0;
unsigned char * TexData=0;
bool TexChanged=false;
extern bool DrawMap=false;
float * Vecs=0;
float * Nors=0;
float * Texs=0;
float * PartTR=0;
int * PartInfo=0;
int VecSize=0;
int TexsSize=0;
int PartSize=0;
float WHEEL=0.0f;
float Pmat[16];
int w;
int h;
float msize=200.0f;
float mpos[3]={0.0f,0.0f,100.0f};
BOOL	done=FALSE;	
int MouseWheel=0;
enum _ViewMode
{
	_ViewMode_View,
	_ViewMode_Free
};
_ViewMode ViewMode=_ViewMode_View;
float MoveStep=10.0f;
int FSAAsamples=4;

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
	glGenerateMipmapEXT(GL_TEXTURE_2D);
	if(glewIsSupported("GL_EXT_texture_filter_anisotropic"))
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4 ); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
extern "C" _declspec(dllexport) void ClearViewTurn()
{
	ViewTurnX=45.0f;
	ViewTurnY=45.0f;
	WHEEL=0.0f;
	mpos[2]=msize;
	ViewMAth->Clear();
	ViewMAth->Turn(-45.0f,0.0f,1.0f,0.0f);
	ViewMAth->Turn(-45.0f,1.0f,0.0f,0.0f);
	ViewMAth->Move(0.0f,0.0f,mpos[2]);
}

void DrawTestLine()
{	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f( 0.0f, 0.0f, 1.0f);
		glVertex3f( 0.0f, 0.0f,      0.0f);

		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f( 0.0f, 0.0f,      0.0f);
		glVertex3f( 0.0f, 0.0f,-1.0f);

		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( 0.0f,      0.0f, 0.0f);

		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f( 0.0f,      0.0f, 0.0f);
		glVertex3f( 0.0f,-1.0f, 0.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 1.0f, 0.0f, 0.0f);
		glVertex3f(      0.0f, 0.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(      0.0f, 0.0f, 0.0f);


	glEnd();
	
	glColor3f(1.0f,1.0f,1.0f);
	glEnable( GL_TEXTURE_2D );
	if(UseLight)
	glEnable(GL_LIGHTING);
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
		//SetMatrix(PartID);
		glTranslatef(PartTR[PartID*6],PartTR[PartID*6+1],PartTR[PartID*6+2]);
		glRotatef((PartTR[PartID*6+5]/3.1415926f)*180.0f,0.0f,0.0f,1.0f);
		glRotatef((PartTR[PartID*6+4]/3.1415926f)*180.0f,0.0f,1.0f,0.0f);
		glRotatef((PartTR[PartID*6+3]/3.1415926f)*180.0f,1.0f,0.0f,0.0f);
		
		

		
		glBegin(GL_TRIANGLES);
		for(int i=PartInfo[PartID*3+1];i<PartInfo[PartID*3+1]+PartInfo[PartID*3+2];i++)
		{
			glNormal3f(Nors[i*3+0],Nors[i*3+1], Nors[i*3+2]);
			glTexCoord2f(Texs[i*2+0],Texs[i*2+1]);
			glVertex3f(Vecs[i*3+0],Vecs[i*3+1], Vecs[i*3+2]);
		}
		glEnd();
	
		if(PartInfo[PartID*3+2]==0)
			DrawTestLine();
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
GLfloat LightMaterialDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightAmbient[]= { 0.75f, 0.75f, 0.75f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };
void InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glewInit();
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.5f, 1.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    GLfloat mat_shininess[]={90.0};
 //   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,LightMaterialDiffuse);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,LightAmbient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightDiffuse);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_SPECULAR,LightDiffuse);	// Position The Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One
	
	glLineWidth(1.0f);
	//glEnable(GL_LIGHTING);
}

/* Callback function for window resize events */
void GLFWCALL handle_resize( int width, int height )
{
	winwidth=width;
	winheight=height;
  float ratio = 1.0f;

  if( height > 0 )
  {
      ratio = (float) width / (float) height;
  }

  /* Setup viewport (Place where the stuff will appear in the main window). */
  glViewport(0, 0, width, height);

  /*
   * Change to the projection matrix and set
   * our viewing volume.
   */
  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  //gluPerspective(45.0, ratio, 10.0, 100000.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	EastPerspective(45.0f,(GLfloat)width/(GLfloat)height,10.0f,1000000.0f,Pmat);
	glLoadMatrixf(Pmat);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	float ViewPos[2];
	switch(ViewMode)
	{
		case _ViewMode_View:
			glTranslatef(0.0f,0.0f,-mpos[2]);	
			glRotatef(ViewTurnY,1.0f,0.0f,0.0f);
			glRotatef(ViewTurnX,0.0f,1.0f,0.0f);
			ViewPos[0]=0.0f;ViewPos[1]=0.0f;
			break;
		case _ViewMode_Free:
			ViewPos[0]=ViewMAth->Pos->m128_f32[0];ViewPos[1]=ViewMAth->Pos->m128_f32[2];
			ViewMAth->Inv();
			glMultMatrixf(ViewMAth->Mat->m128_f32);
			break;
	}
	
	//glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glColor3f(1.0f,1.0f,1.0f);
	if(FSAAsamples>1)
    glEnable(GL_MULTISAMPLE_ARB);
	if(DrawMap)
	{
		DrawMaps(ViewPos[0],ViewPos[1]);
		//if(Map)
		//	Map->Draw();
	}
	else
	{
	glRotatef(180.0f,1.0f,0.0f,0.0f); // 模型方向反的
		if(!UseAlpha)
		{
			
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightPosition);
			RenderPart(0);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightDiffuse);
			if(UseLight)
			{
				glLightfv(GL_LIGHT1, GL_AMBIENT, LightPosition);		// Setup The Ambient Light
				glLightfv(GL_LIGHT1, GL_DIFFUSE, LightPosition);		// Setup The Diffuse Light
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE   );
				RenderPart(0);
				RenderPart(0);
				glDisable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
				glLightfv(GL_LIGHT1, GL_AMBIENT, LightDiffuse);		// Setup The Ambient Light
				glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
			}
		}
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
	}
	if(FSAAsamples>1)
    glDisable(GL_MULTISAMPLE_ARB);
	ReleaseMutex(Mutex);
	return TRUE;										// Keep Going
}
bool RMousePRESS=false;
bool MMousePRESS=false;
int LastMousePos[]={0,0};
int MousePos[]={0,0};
void GLFWCALL handle_MousePos( int x, int y )
{
	LastMousePos[0]=MousePos[0];
	LastMousePos[1]=MousePos[1];
	MousePos[0]=x;
	MousePos[1]=y;
	switch(ViewMode)
	{
		case _ViewMode_View:
			if(RMousePRESS)
			{
				ViewTurnX+=float(MousePos[0]-LastMousePos[0])*0.25f;
				ViewTurnY+=float(MousePos[1]-LastMousePos[1])*0.25f;
			}
			break;
		case _ViewMode_Free:
			if(RMousePRESS)
			{
				ViewMAth->Turn(float(MousePos[0]-LastMousePos[0])*0.25f,0.0f,1.0f,0.0f);
				ViewMAth->Turn(float(MousePos[1]-LastMousePos[1])*0.25f,1.0f,0.0f,0.0f);
			}
			if(MMousePRESS)
			{
				ViewMAth->Move(MoveStep*float(MousePos[0]-LastMousePos[0])*0.1f,0.0f,0.0f);
				ViewMAth->Move(0.0f,-MoveStep*float(MousePos[1]-LastMousePos[1])*0.1f,0.0f);
			}
			break;
	}
}
void GLFWCALL handle_key_down(int key, int action)
{
	switch(key)
	{
	case GLFW_MOUSE_BUTTON_RIGHT:
		{
			if( action == GLFW_PRESS )
				RMousePRESS=true;
			else
				RMousePRESS=false;
			break;
		}
	case GLFW_MOUSE_BUTTON_MIDDLE:
		{
			if( action == GLFW_PRESS )
				MMousePRESS=true;
			else
				MMousePRESS=false;
			break;
		}
		default:
			break;
	}
}
int lastMouseWheel=0;
void GLFWCALL handle_MouseWheel( int pos )
{
	if(pos)
	{
		switch(ViewMode)
		{
			case _ViewMode_View:
				WHEEL+=(float)(pos-lastMouseWheel);
				mpos[2]+=(float)(pos-lastMouseWheel)*MoveStep;
				break;
			case _ViewMode_Free:
				ViewMAth->Move(0.0f,0.0f,-(float)(pos-lastMouseWheel)*MoveStep);
				break;
		}
		lastMouseWheel=pos;
	}
}
unsigned int __stdcall RenderThread(LPVOID lpvoid)
{
	ViewMAth=new NodeMath;
	if(glfwInit() == GL_FALSE)
		return 0;
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, FSAAsamples);
	if( glfwOpenSubWindow(winwidth,winheight,0,0,0,0,24,0,GLFW_WINDOW,(unsigned int)ParentHWND) == GL_FALSE )
	{
		glfwTerminate();
		return 0;
	}
	
    FSAAsamples = glfwGetWindowParam(GLFW_FSAA_SAMPLES);
	glfwSwapInterval( 1 );
	glfwSetKeyCallback( handle_key_down );
	glfwSetMouseButtonCallback(handle_key_down);
	glfwSetMousePosCallback(handle_MousePos);
	glfwSetMouseWheelCallback(handle_MouseWheel);
	glfwEnable( GLFW_KEY_REPEAT );

	glfwSetWindowSizeCallback( handle_resize );
	InitGL();
	while((!done)&&glfwGetWindowParam( GLFW_OPENED ))
	{
		DrawGLScene();
		glfwSwapBuffers();
		glfwSleep(0.005);
	}
	delete ViewMAth;
	return 0;
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
	mpos[2]=msize=min(1000.0f,msize);
	ClearViewTurn();
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetSub3DData(float * VecsIn,float * NorsIn,int VecHeadIn,int VecSizeIn,float * TexsIn,int TexHeadIn,int TexsSizeIn)
{
	WaitForSingleObject(Mutex,INFINITE);
	if(Vecs)
		memcpy_s(Vecs+VecHeadIn,sizeof(float)*VecSizeIn,VecsIn,sizeof(float)*VecSizeIn);
	if(Nors)
		memcpy_s(Nors+VecHeadIn,sizeof(float)*VecSizeIn,NorsIn,sizeof(float)*VecSizeIn);
	if(Texs)
		memcpy_s(Texs+TexHeadIn,sizeof(float)*TexsSizeIn,TexsIn,sizeof(float)*TexsSizeIn);
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetPartData(float * PartTRIn,int * PartInfoIn,int PartSizeIn)
{
	WaitForSingleObject(Mutex,INFINITE);
	DrawMap=false;
	if(PartTR) delete [] PartTR;
	if(PartInfo) delete [] PartInfo;
	PartSize=PartSizeIn;

	PartTR=new float [PartSizeIn*6];
	PartInfo=new int [PartSizeIn*3];

	memcpy_s(PartTR,sizeof(float)*PartSizeIn*6,PartTRIn,sizeof(float)*PartSizeIn*6);
	memcpy_s(PartInfo,sizeof(int)*PartSizeIn*3,PartInfoIn,sizeof(int)*PartSizeIn*3);
	//ClearViewTurn();
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

extern "C" _declspec(dllexport) void ShowMap()
{
	DrawMap=true;
}
//extern "C" _declspec(dllexport) void InputMap(unsigned char * Data,int Size)
//{
//	DrawMap=true;
//	WaitForSingleObject(Mutex,INFINITE);
//	if(Map)
//	{
//		delete Map;
//	}
//	Map=new AC4Map;
//	Map->Set(Data);
//	ReleaseMutex(Mutex);
//}
extern "C" _declspec(dllexport) void SetMoveStep(float MoveStepIn)
{
	MoveStep=MoveStepIn;
}
extern "C" _declspec(dllexport) void ResetView()
{
	ClearViewTurn();
}
extern "C" _declspec(dllexport) void ChangeViewMode(int mode)
{
	ViewMode=(_ViewMode)mode;
}