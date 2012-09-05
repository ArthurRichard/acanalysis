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
/* Callback function for window resize events */

static void GLFWCALL window_size_callback(int width, int height)
{
    glViewport(0, 0, width, height);
}


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{  
	/* Dimensions of our window. */
	int width, height;
	/* Style of our window. */
	int mode;
	/* Frame time */
	double t, t_old, dt_total;
	if(glfwInit() == GL_FALSE)
	{
		exit(-1);
	}  
	/* Desired window properties */
	width  = 640;
	height = 480;
	mode   = GLFW_WINDOW;

	/* Open window */
	if( glfwOpenWindow(width,height,0,0,0,0,16,0,mode) == GL_FALSE )
	{
		fprintf(stderr, "Could not open window\n");
		glfwTerminate();
		exit(-1);
	}
  
	glfwSetWindowTitle( "Wave Simulation" );

	glfwSwapInterval( 1 );
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.f, 1.f, 0.f, 1.f);
	bool quit=false;
	while(glfwGetWindowParam(GLFW_OPENED))
	{
        GLfloat time = (GLfloat) glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.5f, 0.f, 0.f);
        glRotatef(time, 0.f, 0.f, 1.f);


        glColor3f(1.f, 1.f, 1.f);
        glRectf(-0.25f, -0.25f, 0.25f, 0.25f);

        glfwSwapBuffers();
	}
	glfwTerminate();
	return 0;
}