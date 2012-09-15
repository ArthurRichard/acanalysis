#include "AC4Map.h"
#include "GL\glew.h"
#include <windows.h>		// Header File For Windows
#include <process.h>
#include"TAList.h"
extern HANDLE Mutex;
extern bool DrawMap;
AC4Map::AC4Map(void)
	: vecBuf(0)
	, texBuf(0)
	, DataChanged(false)
	, TID(0)
	, TextureChanged(false)
{
	VecPos.ChangeMaxCount(31*31*2);
	TexCood.ChangeMaxCount(31*31*2);
}


AC4Map::~AC4Map(void)
{
	Clear();
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
	if(TextureChanged)
	{
		TextureChanged=false;
		if(TID)
			glDeleteTextures(1, &TID);
		glGenTextures( 1, &TID );
		glBindTexture( GL_TEXTURE_2D, TID ); 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, TextureBuf);
		glGenerateMipmapEXT(GL_TEXTURE_2D);
		if(glewIsSupported("GL_EXT_texture_filter_anisotropic"))
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4 ); 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if(!vecBuf)
		return;
	//glTranslatef(posX,0.0f,posY);	
	
	glBindTexture( GL_TEXTURE_2D, TID ); 
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
unsigned char MapIndex[0x100]={0};
void AC4Map::Clear(void)
{
	if(TID)
		glDeleteTextures(1, &TID);
	if(vecBuf) glDeleteBuffersARB(1,&vecBuf);
	if(texBuf) glDeleteBuffersARB(1,&texBuf);
	//if(TextureBuf) delete [] TextureBuf;
}

void AC4Map::SetTexture(unsigned char * TexDataIn)
{
	//if(TextureBuf) delete [] TextureBuf;
	//TextureBuf=new unsigned char[1024*1024];
	memcpy_s(TextureBuf,1024*1024*4,TexDataIn,1024*1024*4);
	TextureChanged=true;
}
CTAList<AC4Map> MapList;
int ListSize=0;
extern "C" _declspec(dllexport) void ChangeMapSize(int Size)
{
	WaitForSingleObject(Mutex,INFINITE);
	ListSize=Size;
	if(MapList.Count==0)
	{
		MapList.ChangeMaxCount(ListSize);
		MapList.Count=ListSize;
	}
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetMapData(int ID,unsigned char * Data)
{
	WaitForSingleObject(Mutex,INFINITE);
	MapList[ID].Set(Data);
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetMapTex(int ID,unsigned char * Data)
{
	WaitForSingleObject(Mutex,INFINITE);
	MapList[ID].SetTexture(Data);
	ReleaseMutex(Mutex);
}
extern "C" _declspec(dllexport) void SetMapIndex(unsigned char * Data)
{
	memcpy_s(MapIndex,0x100,Data,0x100);
}

void DrawMaps(float posx,float posz)
{
	if(ListSize!=MapList.Count)
	{
		MapList.Clear();
		MapList.ChangeMaxCount(ListSize);
	}
	for(int y=int(posz/310.0f)-4+8;y<(int(posz/310.0f)+4+8);y++)
	for(int x=int(posx/310.0f)-4+8;x<(int(posx/310.0f)+4+8);x++)
	{
		if(x<0) return;
		if(y<0) return;
		int MapID=x+y*0x10;
		if(MapID>=0x100)
			return;
		glPushMatrix();
		glTranslatef((x-8)*310.0f,0.0f,(y-8)*310.0f);
		int ID=MapIndex[MapID];
		MapList[ID].Draw();
		glPopMatrix();
	}
}

