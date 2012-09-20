#include "AC4Map.h"
#include "GL\glew.h"
#include <windows.h>		// Header File For Windows
#include <process.h>
#include"TAList.h"
extern HANDLE Mutex;
extern bool DrawMap;

AC4MapPack * MapPack=0;
void DrawMaps(float posx,float posz)
{
	if(MapPack)
		MapPack->Draw(posx,posz);
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
	memset(Boders,0,sizeof(Boders));
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
int MapReadProgress=0;
extern "C" _declspec(dllexport) int GetMapReadProgress()
{
	return MapReadProgress;
}
void AC4MapPack::Init(void)
{
	MapReadProgress=0;
	Changed=false;
	eachlist(Texs,i)
	{
		delete Texs[i];
	}
	eachlist(Meshs,i)
	{
		delete Meshs[i];
	}
	for(int i=0;i<0x100;i++)
	{
		if(Boders[i])
		{
			delete Boders[i];
			Boders[i]=0;
		}
	}
	Texs.Clear();
	Meshs.Clear();
	AC4MapTex::SetPal((_PalColor *)(PackBuf+Adds[8].Add));
	memcpy_s(AC4MapTex::TexIDs,0x100,PackBuf+Adds[6].Add,0x100);
	unsigned char * SubMapAdd=PackBuf+Adds[5].Add;
	Texs.ChangeMaxCount(Adds[5].Size/0x200);
	Texs.Count=Adds[5].Size/0x200;
	eachlist(Texs,i)
	{
		MapReadProgress=(50*(i+1))/Texs.Count;
		Texs[i]=new AC4MapTex;
		Texs[i]->Build(SubMapAdd+i*0x200,PackBuf+MapTexAdd);
	}

	memcpy_s(AC4MapMesh::MeshIDs,0x100,PackBuf+Adds[10].Add,0x100);
	unsigned char * MeshAdd=PackBuf+Adds[9].Add;
	Meshs.ChangeMaxCount(Adds[9].Size/0x400);
	Meshs.Count=Adds[9].Size/0x400;
	eachlist(Meshs,i)
	{
		MapReadProgress=50+(50*(i+1))/Texs.Count;
		Meshs[i]=new AC4MapMesh;
		Meshs[i]->Set(MeshAdd+i*0x400);
	}
	MapReadProgress=100;
}

void AC4MapPack::Draw(float posx,float posz)
{
	if(Changed)
		Init();
	for(int i=0;i<0x100;i++)
	{
		AC4MapMeshBoder * boder=Boders[i];
		if(boder)
		{
			boder->LastTime++;
			if(boder->LastTime>60)
			{
				delete Boders[i];
				Boders[i]=0;
			}
		}
	}
	for(int y=int(posz/320.0f)-4+8;y<(int(posz/320.0f)+4+8);y++)
		for(int x=int(posx/320.0f)-4+8;x<(int(posx/320.0f)+4+8);x++)
		{
			if(x<0) return;
			if(y<0) return;
			if(x>=16) return;
			if(y>=16) return;
			int MapID=x+y*0x10;
			if(MapID>=0x100)
				return;
			int meshID=AC4MapMesh::MeshIDs[MapID];
			int texID=AC4MapTex::TexIDs[MapID];
			glPushMatrix();
			glTranslatef((x-8)*320.0f,0.0f,(y-8)*320.0f);
			glBindTexture( GL_TEXTURE_2D, Texs[texID]->TID ); 
			Meshs[meshID]->Draw();
			if(x<15&&y<15)
			{
				AC4MapMeshBoder * boder=Boders[MapID];
				if(boder)
					boder->Draw();
				else
				{
					boder=new AC4MapMeshBoder;
					boder->Set(
						Meshs[meshID]->MeshData,
						Meshs[AC4MapMesh::MeshIDs[x+1+y*0x10]]->MeshData,
						Meshs[AC4MapMesh::MeshIDs[x+(y+1)*0x10]]->MeshData,
						Meshs[AC4MapMesh::MeshIDs[x+1+(y+1)*0x10]]->MeshData);
					boder->Draw();
					Boders[MapID]=boder;
				}
			}
			glPopMatrix();
		}
}


unsigned char AC4MapMesh::MeshIDs[0x100];
AC4MapMesh::AC4MapMesh(void)
	: vecBuf(0)
	, texBuf(0)
{
}

AC4MapMesh::~AC4MapMesh(void)
{
	if(vecBuf) glDeleteBuffersARB(1,&vecBuf);
	if(texBuf) glDeleteBuffersARB(1,&texBuf);
}

void AC4MapMesh::Draw(void)
{
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

void AC4MapMesh::Set(unsigned char * Data)
{	
	memcpy_s(MeshData,0x400,Data,0x400);
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
		glGenBuffersARB( 1,&vecBuf);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, vecBuf );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VecPos.Count*sizeof(_VecPos), VecPos.ListData1, GL_STATIC_DRAW_ARB );

		glGenBuffersARB( 1,&texBuf);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, texBuf );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VecPos.Count*sizeof(_TexCood), TexCood.ListData1, GL_STATIC_DRAW_ARB );

		glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
}

AC4MapTex::~AC4MapTex(void)
{
	if(TID)
		glDeleteTextures(1, &TID);
}

_PalColor AC4MapTexTmp[0x1000];

void AC4MapTex::Set(int posx,int posy,bool turnX,bool turnY,unsigned char * TexDataIn)
{
	int TurnedX = 0,TurnedY = 0;
	for (int y = 0; y < 64; y++)
		for (int x = 0; x < 64; x++)
		{
			if(turnX)
				TurnedX = 63 - x;
			else
				TurnedX = x;

			if(turnY)
				TurnedY = 63 - y;
			else
				TurnedY = y;
			AC4MapTexTmp[x+y*64]=AC4MapTex::Pal[TexDataIn[TurnedX+TurnedY*64]];
		}

		glTexSubImage2D(GL_TEXTURE_2D,0,posx*64,posy*64,64,64,GL_RGBA,GL_UNSIGNED_BYTE,AC4MapTexTmp);
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
			Set(x,y,turnX,turnY,TexData+MapID*0x1000);
		}
		glGenerateMipmapEXT(GL_TEXTURE_2D);
}

AC4MapMeshBoder::AC4MapMeshBoder()
	: LastTime(0)
	, vecBuf(0)
	, texBuf(0)
{
}
AC4MapMeshBoder::~AC4MapMeshBoder()
{
	if(vecBuf) glDeleteBuffersARB(1,&vecBuf);
	if(texBuf) glDeleteBuffersARB(1,&texBuf);
}
void AC4MapMeshBoder::Draw()
{
	LastTime=0;	
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
void AC4MapMeshBoder::Set(unsigned char * Data00,unsigned char * Data10,unsigned char * Data01,unsigned char * Data11)
{	
	VecPos.Count=0;
	TexCood.Count=0;
	_VecPos PosTmp;
	_TexCood TexTmp;
	float size=10.0f,hsize=1.0f,texsize=float(1.0/32.0);
	for(int y=0;y<31;y++)
	{
		int x=31;
		float Height00=Data00[31+y*32];
		float Height10=Data10[y*32];
		float Height01=Data00[31+(y+1)*32];
		float Height11=Data10[(y+1)*32];
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
	for(int x=0;x<31;x++)
	{
		int y=31;
		float Height00=Data00[x+y*32];
		float Height10=Data00[x+1+y*32];
		float Height01=Data01[x];
		float Height11=Data01[x+1];
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
	int x=31,y=31;
	float Height00=Data00[32*32-1];
	float Height10=Data10[31*32];
	float Height01=Data01[31];
	float Height11=Data11[0];
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

	glGenBuffersARB( 1,&vecBuf);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vecBuf );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, VecPos.Count*sizeof(_VecPos), VecPos.ListData1, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1,&texBuf);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, texBuf );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, VecPos.Count*sizeof(_TexCood), TexCood.ListData1, GL_STATIC_DRAW_ARB );

	glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
}
