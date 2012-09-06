#include "AC4Map.h"


AC4Map::AC4Map(void)
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
}


void AC4Map::Draw(void)
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	
	glVertexPointer( 3, GL_FLOAT, 0, VecPos.ListData1 );
	glTexCoordPointer( 2, GL_FLOAT, 0, TexCood.ListData1 );
	glDrawArrays(GL_TRIANGLES,0,VecPos.Count*3);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}
