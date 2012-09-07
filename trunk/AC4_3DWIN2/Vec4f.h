#pragma once
#include"EasyMatrix.h"
#include"Vec3f.h"
__declspec(align(16)) union _Vec4f
{
	float F[4];
	__m128 m;
};
union _Vec4d
{
	double D[4];
};
__declspec(align(16)) class CVec4f
{
public:
	CVec4f()
	{
		Data.m=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	}
	CVec4f(CVec3f & Vec3fIn,float w=1.0f)
	{
		Data.F[0]=Vec3fIn.Data[0];
		Data.F[1]=Vec3fIn.Data[1];
		Data.F[2]=Vec3fIn.Data[2];
		Data.F[3]=w;
	}
	CVec4f(CVec4f & Vec4fIn)
	{
		Data=Vec4fIn.Data;
	}
	CVec4f(_Vec4f & Vec4fIn)
	{
		Data=Vec4fIn;
	}
	CVec4f(float x,float y,float z,float w)
	{
		Data.F[0]=x;
		Data.F[1]=y;
		Data.F[2]=z;
		Data.F[3]=w;
	}
	~CVec4f()
	{
	}
	_Vec4f Data;
	_Vec4f Tmp;
	CVec4f & operator=(CVec4f& DataIn)
	{
		Data=DataIn.Data;
		return *this;
	}
	CVec4f & operator=(float * DataIn)
	{
		Data.F[0]=DataIn[0];
		Data.F[1]=DataIn[1];
		Data.F[2]=DataIn[2];
		Data.F[3]=1.0f;
		return *this;
	}
	void Set(float x,float y,float z,float w)
	{
		Data.F[0]=x;
		Data.F[1]=y;
		Data.F[2]=z;
		Data.F[3]=w;
	}
	CVec4f & operator=(_Vec4f& DataIn)
	{
		Data=DataIn;
		return *this;
	}
	CVec4f & operator=(__m128 & DataIn)
	{
		Data.m=DataIn;
		return *this;
	}
	_Vec4f & operator+(CVec4f & DataIn)
	{
		Easy_vector_add(&Tmp.m,Data.m,DataIn.Data.m);
		return Tmp;
	}
	_Vec4f & operator+(_Vec4f & DataIn)
	{
		Easy_vector_add(&Tmp.m,Data.m,DataIn.m);
		return Tmp;
	}

	void operator+=(CVec4f & DataIn)
	{
		Easy_vector_add(&Data.m,Data.m,DataIn.Data.m);
	}
	void operator+=(_Vec4f & DataIn)
	{
		Easy_vector_add(&Data.m,Data.m,DataIn.m);
	}

	_Vec4f & operator-(CVec4f & DataIn)
	{
		Easy_vector_sub(&Tmp.m,Data.m,DataIn.Data.m);
		return Tmp;
	}
	_Vec4f & operator-(_Vec4f & DataIn)
	{
		Easy_vector_sub(&Tmp.m,Data.m,DataIn.m);
		return Tmp;
	}
	
	void operator-=(CVec4f & DataIn)
	{
		Easy_vector_sub(&Data.m,Data.m,DataIn.Data.m);
	}
	void operator-=(_Vec4f & DataIn)
	{
		Easy_vector_sub(&Data.m,Data.m,DataIn.m);
	}

	float operator*(CVec4f & DataIn)
	{
		return Easy_vector_dot(Data.m,DataIn.Data.m);
	}
	float operator*(_Vec4f & DataIn)
	{
		return Easy_vector_dot(Data.m,DataIn.m);
	}

	_Vec4f operator*(float  DataIn)
	{
		Easy_vector_scalar_mul(&Tmp.m,Data.m,DataIn);
		return Tmp;
	}
	
	void operator*=(float  DataIn)
	{
		Easy_vector_scalar_mul(&Data.m,Data.m,DataIn);
	}

	_Vec4f & Cross(CVec4f & DataIn)
	{
		Easy_vector_cross(&Tmp.m,Data.m,DataIn.Data.m);
		return Tmp;
	}
	void normalize()
	{
		Easy_vector_normalize(&Data.m,Data.m);
	}
	float Length(CVec4f & DataIn)
	{
		return sqrt(Easy_vector_Getlenth_2(Data.m,DataIn.Data.m));
	}
	float Length()
	{
		return sqrt(Easy_vector_Getlenth_2(Data.m,_mm_set_ps(1.0f,0.0f,0.0f,0.0f)));
	}
	/*Matrix4x4f & operator=(Matrix4x4f & MatrixIn)
	{
	}*/
};


class CQuatf
{
public:
	CQuatf()
	{
		Data.m=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	}
	CQuatf(CQuatf & Vec4fIn)
	{
		Data=Vec4fIn.Data;
	}
	CQuatf(_Vec4f & Vec4fIn)
	{
		Data=Vec4fIn;
	}
	CQuatf(float x,float y,float z,float w)
	{
		Data.F[0]=x;
		Data.F[1]=y;
		Data.F[2]=z;
		Data.F[3]=w;
	}
	~CQuatf()
	{
	}
	_Vec4f Data;
	_Vec4f Tmp;
	CQuatf & operator=(CQuatf& DataIn)
	{
		Data=DataIn.Data;
		return *this;
	}
	CQuatf & operator=(_Vec4f& DataIn)
	{
		Data=DataIn;
		return *this;
	}
	CQuatf & operator=(__m128 & DataIn)
	{
		Data.m=DataIn;
		return *this;
	}
	_Vec4f & operator+(CQuatf & DataIn)
	{
		Easy_vector_add(&Tmp.m,Data.m,DataIn.Data.m);
		return Tmp;
	}
	_Vec4f & operator+(_Vec4f & DataIn)
	{
		Easy_vector_add(&Tmp.m,Data.m,DataIn.m);
		return Tmp;
	}
	
	void operator+=(CQuatf & DataIn)
	{
		Easy_vector_add(&Data.m,Data.m,DataIn.Data.m);
	}
	void operator+=(_Vec4f & DataIn)
	{
		Easy_vector_add(&Data.m,Data.m,DataIn.m);
	}

	_Vec4f & operator-(CQuatf & DataIn)
	{
		Easy_vector_sub(&Tmp.m,Data.m,DataIn.Data.m);
		return Tmp;
	}

	_Vec4f & operator-(_Vec4f & DataIn)
	{
		Easy_vector_sub(&Tmp.m,Data.m,DataIn.m);
		return Tmp;
	}

	void operator-=(CQuatf & DataIn)
	{
		Easy_vector_sub(&Data.m,Data.m,DataIn.Data.m);
	}

	void operator-=(_Vec4f & DataIn)
	{
		Easy_vector_sub(&Data.m,Data.m,DataIn.m);
	}

	_Vec4f operator*(CQuatf &  DataIn)
	{
		Easy_quat_Mult(&Tmp.m,Data.m,DataIn.Data.m);
		return Tmp;
	}
	void operator*=(CQuatf &  DataIn)
	{
		Easy_quat_Mult(&Data.m,Data.m,DataIn.Data.m);
	}
	void normalize()
	{
		Easy_quat_normalize(&Data.m,Data.m);
	}

	/*Matrix4x4f & operator=(Matrix4x4f & MatrixIn)
	{
	}*/
};