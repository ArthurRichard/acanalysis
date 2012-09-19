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
AC4MapPack * MapPack=0;
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
	if(MapPack)
		MapPack->Draw(posx,posz);
	//if(ListSize!=MapList.Count)
	//{
	//	MapList.Clear();
	//	MapList.ChangeMaxCount(ListSize);
	//}
	//for(int y=int(posz/310.0f)-4+8;y<(int(posz/310.0f)+4+8);y++)
	//for(int x=int(posx/310.0f)-4+8;x<(int(posx/310.0f)+4+8);x++)
	//{
	//	if(x<0) return;
	//	if(y<0) return;
	//	int MapID=x+y*0x10;
	//	if(MapID>=0x100)
	//		return;
	//	glPushMatrix();
	//	glTranslatef((x-8)*310.0f,0.0f,(y-8)*310.0f);
	//	int ID=MapIndex[MapID];
	//	MapList[ID].Draw();
	//	glPopMatrix();
	//}
}

extern "C" _declspec(dllexport) void SetMapPackData(unsigned char * Data,int size,int MapTexAdd)
{
	WaitForSingleObject(Mutex,INFINITE);
	if(!MapPack) MapPack=new AC4MapPack;
	MapPack->SetData(Data,size);
	MapPack->MapTexAdd=MapTexAdd;
	ReleaseMutex(Mutex);
}

AC4MapPack::AC4MapPack(void)
	: PackBuf(NULL)
	, Changed(false)
	, MapTexAdd(0)
{
}

AC4MapPack::~AC4MapPack(void)
{
	if(PackBuf) delete [] PackBuf;
}

void AC4MapPack::SetData(unsigned char * Data,int size)
{
	if(PackBuf) delete [] PackBuf;
	PackBuf=new unsigned char [size];
	memcpy_s(PackBuf,size,Data,size);
	int * AddsTmp=(int *)PackBuf;
	for(int i=0;i<36;i++)
	{
		_MapAdd AddTmp;
		AddTmp.Add=AddsTmp[i+1];
		AddTmp.Size=AddsTmp[i+2]-AddTmp.Add;
		Adds[i]=AddTmp;
	}
	Adds[35].Size=size-Adds[35].Add;
	Changed=true;
}

void AC4MapPack::Init(void)
{
	Changed=false;
	eachlist(Texs,i)
	{
		delete Texs[i];
	}
	eachlist(Meshs,i)
	{
		delete Meshs[i];
	}
	Texs.Clear();
	AC4MapTex::SetPal((_PalColor *)(PackBuf+Adds[8].Add));
	memcpy_s(AC4MapTex::TexIDs,0x100,PackBuf+Adds[6].Add,0x100);
	unsigned char * SubMapAdd=PackBuf+Adds[5].Add;
	Texs.ChangeMaxCount(Adds[5].Size/0x200);
	Texs.Count=Adds[5].Size/0x200;
	eachlist(Texs,i)
	{
		Texs[i]=new AC4MapTex;
		Texs[i]->Build(SubMapAdd+i*0x200,PackBuf+MapTexAdd);
	}
	
	memcpy_s(AC4MapMesh::MeshIDs,0x100,PackBuf+Adds[10].Add,0x100);
	unsigned char * MeshAdd=PackBuf+Adds[9].Add;
	Meshs.ChangeMaxCount(Adds[9].Size/0x400);
	Meshs.Count=Adds[9].Size/0x400;
	eachlist(Meshs,i)
	{
		Meshs[i]=new AC4MapMesh;
		Meshs[i]->Set(MeshAdd+i*0x400);
	}
}

void AC4MapPack::Draw(float posx,float posz)
{
	if(Changed)
		Init();
	for(int y=int(posz/320.0f)-4+8;y<(int(posz/320.0f)+4+8);y++)
	for(int x=int(posx/320.0f)-4+8;x<(int(posx/320.0f)+4+8);x++)
	{
		if(x<0) return;
		if(y<0) return;
		int MapID=x+y*0x10;
		if(MapID>=0x100)
			return;
		int meshID=AC4MapMesh::MeshIDs[MapID];
		int texID=AC4MapTex::TexIDs[MapID];
		glPushMatrix();
		glTranslatef((x-8)*320.0f,0.0f,(y-8)*320.0f);
		glBindTexture( GL_TEXTURE_2D, Texs[texID]->TID ); 
		Meshs[meshID]->Draw();
		glPopMatrix();
	}
}


unsigned char AC4MapMesh::MeshIDs[0x100];
AC4MapMesh::AC4MapMesh(void)
{
}

AC4MapMesh::~AC4MapMesh(void)
{
}

void AC4MapMesh::Draw(void)
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, VecPos.ListData1 );
	glTexCoordPointer( 2, GL_FLOAT, 0, TexCood.ListData1 );
	glDrawArrays(GL_TRIANGLES,0,VecPos.Count*3);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

void AC4MapMesh::Set(unsigned char * Data)
{	
	VecPos.Count=0;
	TexCood.Count=0;
	float size=10.0f,hsize=1.0f,texsize=float(1.0/32.0);

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
}


_PalColor AC4MapTex::Pal[256];
unsigned char AC4MapTex::TexIDs[0x100];

AC4MapTex::AC4MapTex(void)
	: TID(0)
{
	glGenTextures( 1, &TID );
	glBindTexture( GL_TEXTURE_2D, TID ); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	if(glewIsSupported("GL_EXT_texture_filter_anisotropic"))
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4 ); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

AC4MapTex::~AC4MapTex(void)
{
	if(TID)
		glDeleteTextures(1, &TID);
}

_PalColor AC4MapTexTmp[0x1000];

void AC4MapTex::Set(int posx,int posy,unsigned char * TexDataIn)
{
	int TurnedX = 0,TurnedY = 0;
	for (int y = 0; y < 64; y++)
	for (int x = 0; x < 64; x++)
	{
		if(posx<0)
			TurnedX = 63 - x;
		else
			TurnedX = x;

		if(posy<0)
			TurnedY = 63 - y;
		else
			TurnedY = y;
		AC4MapTexTmp[TurnedX+TurnedY*64]=AC4MapTex::Pal[TexDataIn[TurnedX+TurnedY*64]];
	}

	glTexSubImage2D(GL_TEXTURE_2D,0,abs(posx)*64,abs(posy)*64,64,64,GL_RGBA,GL_UNSIGNED_BYTE,AC4MapTexTmp);
}

void AC4MapTex::SetPal(_PalColor * PalIn)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			Pal[i * 32 + j + 8 * 0] = PalIn[i * 32 + j + 8 * 0];
		for (int j = 0; j < 8; j++)
			Pal[i * 32 + j + 8 * 2] = PalIn[i * 32 + j + 8 * 1];
		for (int j = 0; j < 8; j++)
			Pal[i * 32 + j + 8 * 1] = PalIn[i * 32 + j + 8 * 2];
		for (int j = 0; j < 8; j++)
			Pal[i * 32 + j + 8 * 3] = PalIn[i * 32 + j + 8 * 3];
	}
	for(int i=0;i<256;i++)
	{
		if(Pal[i].A==128)
			Pal[i].A=255;
		else
			Pal[i].A=Pal[i].A*2;
	}
}

void AC4MapTex::Build(unsigned char * SubTexIDs,unsigned char * TexData)
{
	glBindTexture( GL_TEXTURE_2D, TID ); 
	for (int y = 0; y < 16; y++)
	for (int x = 0; x < 16; x++)
	{
		int j=x+y*16;
		int MapID=SubTexIDs[j*2]+SubTexIDs[j*2+1]*0x100;
		bool turnX=false;bool turnY=false;
		if ((MapID / 0x800) % 2 == 1)
			turnY = true;
		if ((MapID / 0x400) % 2 == 1)
			turnX = true;
		MapID=MapID%0x400;
		Set(turnX?x:-x,turnY?y:-y,TexData+MapID*0x1000);
	}
    glGenerateMipmapEXT(GL_TEXTURE_2D);
}


