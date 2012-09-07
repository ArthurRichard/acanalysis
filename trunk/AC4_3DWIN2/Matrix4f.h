#pragma once
#include"EasyMatrix.h"
#include"Vec4f.h"

__declspec(align(16)) union _Matrix4f
{
	_Vec4f V[4];
	float F[16];
	__m128 M[4];
	float F4X4[4][4];
	_Matrix4X4FPos P;
};
__declspec(align(16)) class CMatrix4x4f
{
public:
	CMatrix4x4f()
	{
		Easy_matrix_identity(Data.M);
	}
	~CMatrix4x4f()
	{
	}
	_Matrix4f Data;
	_Matrix4f Tmp;
	_Vec4f Tmpv;
	CQuatf Tmpq;
	void Identity()
	{
		Easy_matrix_identity(Data.M);
	}
	CMatrix4x4f(double * DataIn)
	{
		Data.F[0]=(float)DataIn[0];
		Data.F[1]=(float)DataIn[1];
		Data.F[2]=(float)DataIn[2];
		Data.F[3]=(float)DataIn[3];
		
		Data.F[4]=(float)DataIn[4];
		Data.F[5]=(float)DataIn[5];
		Data.F[6]=(float)DataIn[6];
		Data.F[7]=(float)DataIn[7];
		
		Data.F[8]=(float)DataIn[8];
		Data.F[9]=(float)DataIn[9];
		Data.F[10]=(float)DataIn[10];
		Data.F[11]=(float)DataIn[11];
		
		Data.F[12]=(float)DataIn[12];
		Data.F[13]=(float)DataIn[13];
		Data.F[14]=(float)DataIn[14];
		Data.F[15]=(float)DataIn[15];
	}
	CMatrix4x4f(float * DataIn)
	{
		Data.F[0]=DataIn[0];
		Data.F[1]=DataIn[1];
		Data.F[2]=DataIn[2];
		Data.F[3]=DataIn[3];
		
		Data.F[4]=DataIn[4];
		Data.F[5]=DataIn[5];
		Data.F[6]=DataIn[6];
		Data.F[7]=DataIn[7];
		
		Data.F[8]=DataIn[8];
		Data.F[9]=DataIn[9];
		Data.F[10]=DataIn[10];
		Data.F[11]=DataIn[11];
		
		Data.F[12]=DataIn[12];
		Data.F[13]=DataIn[13];
		Data.F[14]=DataIn[14];
		Data.F[15]=DataIn[15];
	}
	CMatrix4x4f & operator=(CMatrix4x4f & DataIn)
	{
		Data=DataIn.Data;
		return *this;
	}
	
	CMatrix4x4f & operator=(_Matrix4f & DataIn)
	{
		Data=DataIn;
		return *this;
	}
	CMatrix4x4f & operator=(CQuatf & DataIn)
	{
		Easy_quat_to_matrix(Data.M,DataIn.Data.m);
		return *this;
	}
	CQuatf GetQuatf()
	{
		QuatFromMatrix(Tmpq.Data.F,Data.F);
		return Tmpq;
	}
	CMatrix4x4f & operator=(double * DataIn)
	{
		Data.F[0]=(float)DataIn[0];
		Data.F[1]=(float)DataIn[1];
		Data.F[2]=(float)DataIn[2];
		Data.F[3]=(float)DataIn[3];
		
		Data.F[4]=(float)DataIn[4];
		Data.F[5]=(float)DataIn[5];
		Data.F[6]=(float)DataIn[6];
		Data.F[7]=(float)DataIn[7];
		
		Data.F[8]=(float)DataIn[8];
		Data.F[9]=(float)DataIn[9];
		Data.F[10]=(float)DataIn[10];
		Data.F[11]=(float)DataIn[11];
		
		Data.F[12]=(float)DataIn[12];
		Data.F[13]=(float)DataIn[13];
		Data.F[14]=(float)DataIn[14];
		Data.F[15]=(float)DataIn[15];
		return *this;
	}
	CMatrix4x4f & operator=(float * DataIn)
	{
		Data.F[0]=DataIn[0];
		Data.F[1]=DataIn[1];
		Data.F[2]=DataIn[2];
		Data.F[3]=DataIn[3];
		
		Data.F[4]=DataIn[4];
		Data.F[5]=DataIn[5];
		Data.F[6]=DataIn[6];
		Data.F[7]=DataIn[7];
		
		Data.F[8]=DataIn[8];
		Data.F[9]=DataIn[9];
		Data.F[10]=DataIn[10];
		Data.F[11]=DataIn[11];
		
		Data.F[12]=DataIn[12];
		Data.F[13]=DataIn[13];
		Data.F[14]=DataIn[14];
		Data.F[15]=DataIn[15];
		return *this;
	}
	void transpose()
	{
		Easy_matrix_transpose(Data.M);
	}
	void translate_Internal(CVec4f & DataIn)
	{
		Easy_matrix_translate_Internal(Data.M,DataIn.Data.m);
	}
	void translate_External(CVec4f & DataIn)
	{
		Easy_matrix_translate_External(Data.M,DataIn.Data.m);
	}

	_Matrix4f & operator*(CMatrix4x4f & DataIn)
	{
		Easy_matrix_mult(Tmp.M,Data.M,DataIn.Data.M);
		return Tmp;
	}
	void operator*=(CMatrix4x4f & DataIn)
	{
		Easy_matrix_mult(Data.M,Data.M,DataIn.Data.M);
	}
	
	_Matrix4f & operator*(_Matrix4f & DataIn)
	{
		Easy_matrix_mult(Tmp.M,Data.M,DataIn.M);
		return Tmp;
	}
	void operator*=(_Matrix4f & DataIn)
	{
		Easy_matrix_mult(Data.M,Data.M,DataIn.M);
	}
	
	void operator*=(CVec4f & DataIn)
	{
		Easy_matrix_scale(Data.M,DataIn.Data.m);
	}
	void operator*=(_Vec4f & DataIn)
	{
		Easy_matrix_scale(Data.M,DataIn.m);
	}
	void Scale(_Vec4f & DataIn)
	{
		Easy_matrix_scale(Data.M,DataIn.m);
	}
	
	void Scale(float x,float y,float z)
	{
		Tmpv.F[0]=x;
		Tmpv.F[1]=y;
		Tmpv.F[2]=z;
		Tmpv.F[3]=1.0;
		Easy_matrix_scale(Data.M,Tmpv.m);
	}
	void Scale(float xyz)
	{
		Tmpv.F[0]=xyz;
		Tmpv.F[1]=xyz;
		Tmpv.F[2]=xyz;
		Tmpv.F[3]=1.0;
		Easy_matrix_scale(Data.M,Tmpv.m);
	}
	_Vec4f & operator*(CVec4f & DataIn)
	{
		Easy_matrix_mult_vector4X4(&Tmpv.m,Data.M,DataIn.Data.m);
		return Tmpv;
	}
	_Vec4f & operator*(_Vec4f & DataIn)
	{
		Easy_matrix_mult_vector4X4(&Tmpv.m,Data.M,DataIn.m);
		return Tmpv;
	}
	void rotate(float angle,float x,float y,float z)
	{
		Easy_matrix_rotate(Data.M,_mm_set_ps(angle*3.1415926f/180.0f,z,y,x));
	}
	void Inv()
	{
		Easy_matrix_inv(Data.M,Data.M);
	}
	void Ortho(float left, float right, float bottom, float top, float n, float f)
	{
		EasyOrtho(left,right,bottom,top,n,f,Data.F);
	}
	void Perspective(float fovyInDegrees, float aspectRatio,
                      float znear, float zfar)
	{
		EastPerspective(fovyInDegrees,aspectRatio,znear,zfar,Data.F);
	}
	/*Matrix4x4f & operator=(Matrix4x4f & MatrixIn)
	{
	}*/
};