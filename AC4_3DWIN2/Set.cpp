#include"GL\glew.h"
#include <windows.h>
#include"set.h"
float  MaterialData[17]={0.0f};//DIFFUSE:0,SPECULAR:4,AMBIENT:8,EMISSION:12,SHININESS:16
float ZeroF4[4]={ 0.0f, 0.0f, 0.0f, 1.0f };

extern HANDLE Mutex;
bool LightSwitch[8]={false};

float LightData[8][16]={0.0f};//DIFFUSE:0,SPECULAR:4,AMBIENT:8,pos:12

int RenderPart(int PartID);
extern "C" _declspec(dllexport) void SetMaterial(float *Data)
{
	WaitForSingleObject(Mutex,INFINITE);
	memcpy_s(MaterialData,sizeof(MaterialData),Data,sizeof(MaterialData));
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetLightSwitch(int LightID,bool Switch)
{
	if(LightID<0)
		return;
	if(LightID>7)
		return;
	WaitForSingleObject(Mutex,INFINITE);
	LightSwitch[LightID]=Switch;
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetLight(int LightID,float * Data)
{
	if(LightID<0)
		return;
	if(LightID>7)
		return;
	WaitForSingleObject(Mutex,INFINITE);
	memcpy_s(LightData[LightID],sizeof(float)*16,Data,sizeof(float)*16);
	ReleaseMutex(Mutex);
}
void DrawLightMark()
{	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
	glBegin(GL_LINES);
	glVertex3f( 0.0f, 0.0f, 2.0f);
	glVertex3f( 0.0f, 0.0f,      0.0f);

	glVertex3f( 0.0f, 0.0f,      0.0f);
	glVertex3f( 0.0f, 0.0f,-2.0f);

	glVertex3f( 0.0f, 2.0f, 0.0f);
	glVertex3f( 0.0f,      0.0f, 0.0f);

	glVertex3f( 0.0f,      0.0f, 0.0f);
	glVertex3f( 0.0f,-2.0f, 0.0f);

	glVertex3f( 2.0f, 0.0f, 0.0f);
	glVertex3f(      0.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(      0.0f, 0.0f, 0.0f);


	glEnd();

	glColor3f(1.0f,1.0f,1.0f);
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_LIGHTING);
}
void DrawModelNoalpha()
{		
	for(int i=0;i<8;i++)
	{
		glDisable(GL_LIGHT0+i);
		if(LightSwitch[i])
		{
			glEnable(GL_LIGHT0+i);
			glLightfv(GL_LIGHT0+i, GL_DIFFUSE, LightData[i]+0);
			glLightfv(GL_LIGHT0+i, GL_SPECULAR, LightData[i]+4);
			glLightfv(GL_LIGHT0+i, GL_AMBIENT, LightData[i]+8);
			glLightfv(GL_LIGHT0+i, GL_POSITION,LightData[i]+12);
			
			glColor3fv(LightData[i]);
			glPushMatrix();
			glTranslatef(LightData[i][12],LightData[i][13],LightData[i][14]);
			DrawLightMark();
			glPopMatrix();
		}
	}
	
	glColor3f(1.0f,1.0f,1.0f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MaterialData);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,ZeroF4);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MaterialData+8);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,MaterialData+12);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,MaterialData+16);
	RenderPart(0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MaterialData+4);
	
	for(int i=0;i<8;i++)
	{
		if(LightSwitch[i])
		{
			glLightfv(GL_LIGHT0+i, GL_DIFFUSE, ZeroF4);
			glLightfv(GL_LIGHT0+i, GL_AMBIENT, ZeroF4);
		}
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE   );
	RenderPart(0);
	RenderPart(0);
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
			
}
void DrawModelalpha()
{	
	for(int i=0;i<8;i++)
	{
		glDisable(GL_LIGHT0+i);
		if(LightSwitch[i])
		{
			glEnable(GL_LIGHT0+i);
			glLightfv(GL_LIGHT0+i, GL_DIFFUSE, LightData[i]+0);
			glLightfv(GL_LIGHT0+i, GL_SPECULAR, LightData[i]+4);
			glLightfv(GL_LIGHT0+i, GL_AMBIENT, LightData[i]+8);
			glLightfv(GL_LIGHT0+i, GL_POSITION,LightData[i]+12);

			glColor3fv(LightData[i]);
			glPushMatrix();
			glTranslatef(LightData[i][12],LightData[i][13],LightData[i][14]);
			DrawLightMark();
			glPopMatrix();
		}
	}
	glColor3f(1.0f,1.0f,1.0f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MaterialData);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MaterialData+4);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MaterialData+8);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,MaterialData+12);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,MaterialData+16);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.99f);
	RenderPart(0);
	glAlphaFunc(GL_LEQUAL, 0.99f);
	glDepthMask(GL_FALSE);
	RenderPart(0);
	glDisable(GL_ALPHA_TEST); 
	glDepthMask(GL_TRUE);
}
void DrawModel(bool alpha)
{
	if(alpha)
		DrawModelalpha();
	else
		DrawModelNoalpha();
}