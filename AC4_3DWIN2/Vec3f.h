#pragma once
#include"EasyMatrix.h"

class CVec3f
{
public:
	CVec3f()
	{
		Data[0]=0.0f;
		Data[1]=0.0f;
		Data[2]=0.0f;
	}
	CVec3f(float * Vec3fIn)
	{
		Data[0]=Vec3fIn[0];
		Data[1]=Vec3fIn[1];
		Data[2]=Vec3fIn[2];
	}
	CVec3f(float x,float y,float z)
	{
		Data[0]=x;
		Data[1]=y;
		Data[2]=x;
	}
	~CVec3f()
	{
	}
	float Data[3];
	/*Matrix4x4f & operator=(Matrix4x4f & MatrixIn)
	{
	}*/
};