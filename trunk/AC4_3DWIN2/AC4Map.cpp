#include "AC4Map.h"
#include "GL\glew.h"
#include <windows.h>		// Header File For Windows

AC4Map::AC4Map(void)
	: vecBuf(0)
	, texBuf(0)
	, DataChanged(false)
{
	VecPos.ChangeMaxCount(31*31*2);
	TexCood.ChangeMaxCount(31*31*2);
}


AC4Map::~AC4Map(void)
{
}


void AC4Map::Set(unsigned char * Data)
{
	VecPos.Count=0;
	TexCood.Count=0;
	float size=10.0f,hsize=1.0f,texsize=float(1.0/31.0);

	for(int y=0;y<31;y++)
	for(int x=0;x<31;x++)
	{
		float Height00=Data[x+y*32];
		float Height10=Data[x+1+y*32];
		float Height01=Data[x+(y+1)*32];
		float Height11=Data[x+1+(y+1)*32];

		_VecPos PosTmp;
		_TexCood TexTmp;
		
		PosTmp.y0=Height00*hsize;
		PosTmp.x0=x*size;
		PosTmp.z0=y*size;
		TexTmp.x0=x*texsize;
		TexTmp.y0=y*texsize;
		
		PosTmp.y1=Height01*hsize;
		PosTmp.x1=x*size;
		PosTmp.z1=(y+1)*size;
		TexTmp.x1=x*texsize;
		TexTmp.y1=(y+1)*texsize;
		
		PosTmp.y2=Height10*hsize;
		PosTmp.x2=(x+1)*size;
		PosTmp.z2=y*size;
		TexTmp.x2=(x+1)*texsize;
		TexTmp.y2=y*texsize;

		VecPos.push_back(PosTmp);
		TexCood.push_back(TexTmp);
		
		PosTmp.y0=Height11*hsize;
		PosTmp.x0=(x+1)*size;
		PosTmp.z0=(y+1)*size;
		TexTmp.x0=(x+1)*texsize;
		TexTmp.y0=(y+1)*texsize;
		
		PosTmp.y1=Height01*hsize;
		PosTmp.x1=x*size;
		PosTmp.z1=(y+1)*size;
		TexTmp.x1=x*texsize;
		TexTmp.y1=(y+1)*texsize;
		
		PosTmp.y2=Height10*hsize;
		PosTmp.x2=(x+1)*size;
		PosTmp.z2=y*size;
		TexTmp.x2=(x+1)*texsize;
		TexTmp.y2=y*texsize;

		VecPos.push_back(PosTmp);
		TexCood.push_back(TexTmp);

	}
	DataChanged =true;
}


void AC4Map::Draw(void)
{
	if(DataChanged)
	{
		if(vecBuf) glDeleteBuffersARB(1,&vecBuf);
		if(texBuf) glDeleteBuffersARB(1,&texBuf);

		glGenBuffersARB( 1,&vecBuf);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, vecBuf );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VecPos.Count*sizeof(_VecPos), VecPos.ListData1, GL_STATIC_DRAW_ARB );

		glGenBuffersARB( 1,&texBuf);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, texBuf );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VecPos.Count*sizeof(_TexCood), TexCood.ListData1, GL_STATIC_DRAW_ARB );

		glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
		DataChanged=false;
	}

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vecBuf );
	glVertexPointer( 3, GL_FLOAT, 0, 0 );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, texBuf );
	glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
	glDrawArrays(GL_TRIANGLES,0,VecPos.Count*3);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
}
