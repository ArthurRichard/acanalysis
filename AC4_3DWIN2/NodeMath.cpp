#include "NodeMath.h"

NodeMath::NodeMath(void)
{
	Mat=(__m128*)_aligned_malloc(sizeof(__m128)*4,16);
	Quat=(__m128*)_aligned_malloc(sizeof(__m128),16);
	Pos =(__m128*)_aligned_malloc(sizeof(__m128),16);
	Clear();
}


NodeMath::~NodeMath(void)
{
	_aligned_free(Mat);
	_aligned_free(Quat);
	_aligned_free(Pos);
}


void NodeMath::Move(float x, float y, float z)
{
	Easy_quat_to_matrix(Mat,*Quat);
	Mat[3]=*Pos;
	Easy_matrix_translate_Internal(Mat,_mm_set_ps(1.0f,z,y,x));
	Pos[0]=Mat[3];
}


void NodeMath::Turn(float a, float x, float y, float z)
{
	__m128 UnitPosTMP,UnitPosTMP2;
	Easy_quat_axis_angle(&UnitPosTMP,x,y,z,-a*3.1415926f/180.0f);
	Easy_quat_normalize(&UnitPosTMP,UnitPosTMP);
	Easy_quat_Mult(&UnitPosTMP2,Quat[0],UnitPosTMP);
	Easy_quat_normalize(Quat,UnitPosTMP2);
}


void NodeMath::Inv(void)
{
	Easy_quat_to_matrix((__m128*)Mat,((__m128*)Quat)[0]);
	Mat[3]=*Pos;
	Easy_matrix_inv(Mat->m128_f32);
}


void NodeMath::Clear(void)
{
	Easy_matrix_identity(Mat);
	*Pos=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	*Quat=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
}
