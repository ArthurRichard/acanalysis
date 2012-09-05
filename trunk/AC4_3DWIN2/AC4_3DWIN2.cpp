#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"GL\glfw.h"
#ifdef _DEBUG
#pragma comment( lib, "GLFWd.lib" )
#else
#pragma comment( lib, "GLFW.lib" )
#endif
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
int winwidth=640, winheight=480;
HWND ParentHWND=0;
HANDLE RenderThreadHANDLE=NULL;
float Pmat[16];
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
void InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };
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
}

/* Callback function for window resize events */
void GLFWCALL handle_resize( int width, int height )
{
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
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, ratio, 1.0, 1024.0);
}

void GLFWCALL handle_key_down(int key, int action)
{
  if( action != GLFW_PRESS )
  {
    return;
  }

  //switch(key) {
  //  case GLFW_KEY_ESC:
  //    running = 0;
  //    break;
  //  case GLFW_KEY_SPACE:
  //    initSurface();
  //    break;
  //  case GLFW_KEY_LEFT:
  //    alpha+=5;
  //    break;
  //  case GLFW_KEY_RIGHT:
  //    alpha-=5;
  //    break;
  //  case GLFW_KEY_UP:
  //    beta-=5;
  //    break;
  //  case GLFW_KEY_DOWN:
  //    beta+=5;
  //    break;
  //  case GLFW_KEY_PAGEUP:
  //    if(zoom>1) zoom-=1;
  //    break;
  //  case GLFW_KEY_PAGEDOWN:
  //    zoom+=1;
  //    break;
  //  default:
  //    break;
  //}
}
unsigned int __stdcall RenderThread(LPVOID lpvoid)
{
	if(glfwInit() == GL_FALSE)
		return 0;
	if( glfwOpenSubWindow(winwidth,winheight,0,0,0,0,24,0,GLFW_WINDOW,(unsigned int)ParentHWND) == GL_FALSE )
	{
		glfwTerminate();
		return 0;
	}
	glfwSwapInterval( 1 );
  /* Keyboard handler */
  glfwSetKeyCallback( handle_key_down );
  glfwEnable( GLFW_KEY_REPEAT );

  /* Window resize handler */
  glfwSetWindowSizeCallback( handle_resize );
	InitGL();
	while(glfwGetWindowParam( GLFW_OPENED ))
	{
		glfwSwapBuffers();
		glfwSleep(0.01);
	}
	return 0;
}