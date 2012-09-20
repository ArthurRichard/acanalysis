#pragma once
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
//class AC4Map
//{
//public:
//	AC4Map(void);
//	~AC4Map(void);
//	void Set(unsigned char * Data);
//	void Draw(void);
//	CTAList<_VecPos> VecPos;
//	CTAList<_TexCood> TexCood;
//
//	unsigned int vecBuf;
//	unsigned int texBuf;
//	bool DataChanged;
//	unsigned int TID;
//	unsigned char TextureBuf[1024*1024*4];
//	bool TextureChanged;
//	void SetTexture(unsigned char * TexDataIn);
//	void Clear(void);
//};

void DrawMaps(float posx,float posz);
struct _MapAdd
{
	int Add;
	int Size;
};
struct _PalColor
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};
class AC4MapTex
{
public:
	AC4MapTex(void);
	~AC4MapTex(void);
	unsigned int TID;
	void Set(int posx,int posy,bool turnX,bool turnY,unsigned char * TexDataIn);
	static _PalColor Pal[256];
	static unsigned char TexIDs[0x100];
	static void SetPal(_PalColor * PalIn);
	void Build(unsigned char * SubTexIDs,unsigned char * TexData);
};
class AC4MapMesh
{
public:
	AC4MapMesh(void);
	~AC4MapMesh(void);
	CTAList<_VecPos> VecPos;
	CTAList<_TexCood> TexCood;
	unsigned int vecBuf;
	unsigned int texBuf;
	void Set(unsigned char * Data);
	static unsigned char MeshIDs[0x100];
	void Draw(void);
	unsigned char MeshData[0x400];
};
class AC4MapMeshBoder
{
public:
	AC4MapMeshBoder(void);
	~AC4MapMeshBoder(void);
	CTAList<_VecPos> VecPos;
	CTAList<_TexCood> TexCood;
	unsigned int vecBuf;
	unsigned int texBuf;
	void Set(unsigned char * Data00,unsigned char * Data10,unsigned char * Data01,unsigned char * Data11);
	void Draw(void);
	int LastTime;
};
struct _ModelSet
{
	int x;
	int y;
	int id;
};
class AC4MapModel
{
public:
	AC4MapModel(void);
	~AC4MapModel(void);
	void Set(unsigned char *DataIn);
	void Draw();
	static unsigned char IDs[0x100];
	CTAList<_ModelSet> Models;
};
class AC4MapPack
{
public:
	AC4MapPack(void);
	~AC4MapPack(void);
	unsigned char *PackBuf;
	void SetData(unsigned char * Data,int size);
	bool Changed;
	void Init(void);
	void Draw(float posx,float posz);
	CTAList<AC4MapTex *> Texs;
	CTAList<AC4MapMesh *> Meshs;
	CTAList<AC4MapModel *> Models;
	_MapAdd Adds[36];
	int MapTexAdd;
	AC4MapMeshBoder * Boders[0x100];
};