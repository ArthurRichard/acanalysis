#include "NodeMath.h"
#include "EasyMatrix.h"

NodeMath::NodeMath(void)
{
	Mat=new _NodeMatrix4f;
	Quat=new _NodeQuat;
	Pos =new _NodeQuat;
	Clear();
}


NodeMath::~NodeMath(void)
{
	if(Mat)
		delete Mat;
	if(Quat)
		delete Quat;
	if(Pos)
		delete Pos;
}


void NodeMath::Move(float x, float y, float z)
{
	Easy_quat_to_matrix((__m128*)Mat,((__m128*)Quat)[0]);
	Mat->F[12]=Pos->Q[0];
	Mat->F[13]=Pos->Q[1];
	Mat->F[14]=Pos->Q[2];
	Easy_matrix_translate_Internal(Mat->F4X4,x,y,z);
	Pos->Q[0]=Mat->F[12];
	Pos->Q[1]=Mat->F[13];
	Pos->Q[2]=Mat->F[14];
}


void NodeMath::Turn(float a, float x, float y, float z)
{
	__m128 UnitPosTMP;
	Easy_quat_axis_angle(&UnitPosTMP,x,y,z,-a*3.1415926f/180.0f);
	Easy_quat_normalize(&UnitPosTMP,UnitPosTMP);
	Easy_quat_Mult((__m128*)Quat,((__m128*)Quat)[0],UnitPosTMP);
	Easy_quat_normalize((__m128*)Quat,((__m128*)Quat)[0]);
}


void NodeMath::Inv(void)
{
	Easy_quat_to_matrix((__m128*)Mat,((__m128*)Quat)[0]);
	Mat->F[12]=Pos->Q[0];
	Mat->F[13]=Pos->Q[1];
	Mat->F[14]=Pos->Q[2];
	Easy_matrix_inv(Mat->F);
}


void NodeMath::Clear(void)
{
	Easy_matrix_identity(Mat->F);
	Pos->Q[0] = Quat->Q[0]=0.0f;
	Pos->Q[1] = Quat->Q[1]=0.0f;
	Pos->Q[2] = Quat->Q[2]=0.0f;
	Pos->Q[3] = Quat->Q[3]=1.0f;
}
