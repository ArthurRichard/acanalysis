#ifndef _DEF_H
#define _DEF_H


#define USE_SSE 1
#define LIB3DS_EPSILON (1e-5)
typedef enum _AbLocID
{
	AbLoc_Pos=0,
	AbLoc_Tex0,
	AbLoc_Normal,
	AbLoc_Color,
	AbLoc_Tangent,
	AbLocNUM
}_AbLocID;
typedef enum _TexShot
{
	DifTexShot=0,
	ShaTexShot,//shadow
	RefTexShot,
	SpeTexShot,
	NorTexShot,//normal
	TexShotNUM
}_TexShot;
enum _TexRefShot
{
	_RefBK=0,
	_RefDN,
	_RefFR,
	_RefLF,
	_RefRT,
	_RefUP,
	_RefNUM
};
#endif