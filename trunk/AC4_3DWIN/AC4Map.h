#pragma once
#include <vector>
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include "TAList.h"
struct _VecPos
{
	float x0;
	float y0;
	float z0;
	
	float x1;
	float y1;
	float z1;

	float x2;
	float y2;
	float z2;
};
struct _TexCood
{
	float x0;
	float y0;
	
	float x1;
	float y1;
	
	float x2;
	float y2;
};
class AC4Map
{
public:
	AC4Map(void);
	~AC4Map(void);
	void Set(unsigned char * Data);
	void Draw(void);
	CTAList<_VecPos> VecPos;
	CTAList<_TexCood> TexCood;

};

