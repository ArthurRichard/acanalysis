#ifndef _EASYMATRIX_H
#define _EASYMATRIX_H
#include "Def.h"	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>
#include "EasyQuat.h"
struct _Matrix4X4F{
	float m[16];
};
struct _Matrix4X4FPos{
	float u[12];
	float x;
	float y;
	float z;
	float w;
};
struct _Matrix4X4FPos4{
	float u[12];
	float Q[4];
};
typedef union  _Matrix4X4 {
     float              f16[16];
     float              f4X4[4][4];
     _Matrix4X4F		m16;
	 _Quat				Q4[4];
	 _Matrix4X4FPos		Pos;
	 _Matrix4X4FPos4	Pos4;
}_Matrix4X4,_Mat4;
static const float IdentityMatrix[4][4]={1.0f,0.0f,0.0f,0.0f,
										 0.0f,1.0f,0.0f,0.0f,
										 0.0f,0.0f,1.0f,0.0f,
										 0.0f,0.0f,0.0f,1.0f};
static const double IdentityMatrixd[4][4]={1.0,0.0,0.0,0.0,
										 0.0,1.0,0.0,0.0,
										 0.0,0.0,1.0,0.0,
										 0.0,0.0,0.0,1.0};
static const float IdentityDDSTexMatrix[4][4]={1.0f,0.0f,0.0f,0.0f,
											 0.0f,-1.0f,0.0f,0.0f,
											 0.0f,0.0f,1.0f,0.0f,
											 0.0f,0.0f,0.0f,1.0f};
static const float TurnYZ[4][4]={
		1.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f};
static const float TurnY[4][4]={
		1.0f,0.0f,0.0f,0.0f,
		0.0f,-1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f};
static const __m128 TurnYZm[4]={
		1.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f};
static const __m128 TurnYm[4]={
		1.0f,0.0f,0.0f,0.0f,
		0.0f,-1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f};
static const __m128 one = _mm_set_ps1(1.0f);
static const __m128 IdentityMatrix0 = _mm_set_ps(0.0f,0.0f,0.0f,1.0f);
static const __m128 IdentityMatrix1 = _mm_set_ps(0.0f,0.0f,1.0f,0.0f);
static const __m128 IdentityMatrix2 = _mm_set_ps(0.0f,1.0f,0.0f,0.0f);
static const __m128 IdentityMatrix3 = _mm_set_ps(1.0f,0.0f,0.0f,0.0f);
static const __m128 IdentityMatrixSSE[4]={IdentityMatrix0,IdentityMatrix1,IdentityMatrix2,IdentityMatrix3};
inline void Easy_matrix_identity(_Mat4 & Matrix)
{
	memcpy(&Matrix,IdentityMatrix,4*4*sizeof(float));
}
inline void Easy_matrix_identity(float Matrix[4][4])
{
	memcpy(Matrix,IdentityMatrix,4*4*sizeof(float));
}
inline void Easy_matrix_identity(float Matrix[16])
{
	memcpy(Matrix,IdentityMatrix,4*4*sizeof(float));
}
inline void Easy_matrix_identity(double Matrix[16])
{
	memcpy(Matrix,IdentityMatrixd,4*4*sizeof(double));
}
inline void Easy_matrix_identity(__m128 Matrix[4])
{
	_asm
	{
		movaps xmm0,IdentityMatrix0
		movaps xmm1,IdentityMatrix1
		movaps xmm2,IdentityMatrix2
		movaps xmm3,IdentityMatrix3
		mov edx,Matrix;
		movups [edx],xmm0
		movups [edx+16],xmm1
		movups [edx+32],xmm2
		movups [edx+48],xmm3
	}
	/*
	Matrix[0] = _mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	Matrix[1] = _mm_set_ps(0.0f,1.0f,0.0f,0.0f);
	Matrix[2] = _mm_set_ps(0.0f,0.0f,1.0f,0.0f);
	Matrix[3] = _mm_set_ps(0.0f,0.0f,0.0f,1.0f);
	*/
}
inline void Easy_matrix_identity(__m128 * Matrix,const unsigned int MatrixNum)
{
	_asm
	{
		movaps xmm0,IdentityMatrix0
		movaps xmm1,IdentityMatrix1
		movaps xmm2,IdentityMatrix2
		movaps xmm3,IdentityMatrix3
		mov ecx, MatrixNum
		mov edx, Matrix
sse_Loop:
		movaps [edx],xmm0
		movaps [edx+16],xmm1
		movaps [edx+32],xmm2
		movaps [edx+48],xmm3
		add edx,64
		dec ecx
		jnz sse_Loop
	}
	
}
inline void Easy_matrix_transpose(_Mat4 & Matrix) 
{
    int i, j;
    float swp;

    for (j = 0; j < 4; j++) {
        for (i = j + 1; i < 4; i++) {
			swp = Matrix.f4X4[j][i];
            Matrix.f4X4[j][i] = Matrix.f4X4[i][j];
            Matrix.f4X4[i][j] = swp;
        }
    }
}
inline void Easy_matrix_transpose(float m[4][4]) 
{
    int i, j;
    float swp;

    for (j = 0; j < 4; j++) {
        for (i = j + 1; i < 4; i++) {
            swp = m[j][i];
            m[j][i] = m[i][j];
            m[i][j] = swp;
        }
    }
}
inline void Easy_matrix_transpose(double m[4][4]) 
{
    int i, j;
    double swp;

    for (j = 0; j < 4; j++) {
        for (i = j + 1; i < 4; i++) {
            swp = m[j][i];
            m[j][i] = m[i][j];
            m[i][j] = swp;
        }
    }
}
inline void Easy_matrix_transpose(__m128 m[4]) 
{
	_MM_TRANSPOSE4_PS(m[0],m[1],m[2],m[3]);
}
inline void Easy_matrix_translate_Internal(_Mat4 & Matrix, float x, float y, float z)
{
	Matrix.f4X4[3][0] += Matrix.f4X4[0][0] * x + Matrix.f4X4[1][0] * y + Matrix.f4X4[2][0] * z;
	Matrix.f4X4[3][1] += Matrix.f4X4[0][1] * x + Matrix.f4X4[1][1] * y + Matrix.f4X4[2][1] * z;
	Matrix.f4X4[3][2] += Matrix.f4X4[0][2] * x + Matrix.f4X4[1][2] * y + Matrix.f4X4[2][2] * z;
}
inline void Easy_matrix_translate_Internal(_Mat4 & Matrix, _Vec3 Pos)
{
	Matrix.f4X4[3][0] += Matrix.f4X4[0][0] * Pos.Pos.x + Matrix.f4X4[1][0] * Pos.Pos.y + Matrix.f4X4[2][0] * Pos.Pos.z;
	Matrix.f4X4[3][1] += Matrix.f4X4[0][1] * Pos.Pos.x + Matrix.f4X4[1][1] * Pos.Pos.y + Matrix.f4X4[2][1] * Pos.Pos.z;
	Matrix.f4X4[3][2] += Matrix.f4X4[0][2] * Pos.Pos.x + Matrix.f4X4[1][2] * Pos.Pos.y + Matrix.f4X4[2][2] * Pos.Pos.z;
}
inline void Easy_matrix_translate_Internal(float Matrix[4][4], float x, float y, float z)
{
	Matrix[3][0] += Matrix[0][0] * x + Matrix[1][0] * y + Matrix[2][0] * z;
	Matrix[3][1] += Matrix[0][1] * x + Matrix[1][1] * y + Matrix[2][1] * z;
	Matrix[3][2] += Matrix[0][2] * x + Matrix[1][2] * y + Matrix[2][2] * z;
}
inline void Easy_matrix_translate_Internal(double Matrix[4][4], double x, double y, double z)
{
	Matrix[3][0] += Matrix[0][0] * x + Matrix[1][0] * y + Matrix[2][0] * z;
	Matrix[3][1] += Matrix[0][1] * x + Matrix[1][1] * y + Matrix[2][1] * z;
	Matrix[3][2] += Matrix[0][2] * x + Matrix[1][2] * y + Matrix[2][2] * z;
}
inline void Easy_matrix_translate_Internal(__m128 Matrix[4], const __m128 Pos)
{
	//Matrix[3].m128_f32[0] += Matrix[0].m128_f32[0] * Pos.m128_f32[0] + Matrix[1].m128_f32[0] * Pos.m128_f32[1] + Matrix[2].m128_f32[0] * Pos.m128_f32[2];
	//Matrix[3].m128_f32[1] += Matrix[0].m128_f32[1] * Pos.m128_f32[0] + Matrix[1].m128_f32[1] * Pos.m128_f32[1] + Matrix[2].m128_f32[1] * Pos.m128_f32[2];
	//Matrix[3].m128_f32[2] += Matrix[0].m128_f32[2] * Pos.m128_f32[0] + Matrix[1].m128_f32[2] * Pos.m128_f32[1] + Matrix[2].m128_f32[2] * Pos.m128_f32[2];

	//float m44=Matrix[3].m128_f32[3];
	_asm
	{
		mov edx,Matrix
		mov eax,[edx+60]
		movaps xmm4,[edx]
		movaps xmm5,[edx+16]
		movaps xmm6,[edx+32]
		movaps xmm7,[edx+48]

		movaps xmm0,Pos
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		//movups xmm3,xmm0

		shufps xmm0,xmm0,0x00
		shufps xmm1,xmm1,0x55
		shufps xmm2,xmm2,0xaa
		//shufps xmm3,xmm3,0xff

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		//mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm7//addps xmm0,xmm3
		//mov    edx, Matrix
		movaps [edx+48], xmm0
		mov [edx+60],eax
	}
	//Matrix[3].m128_f32[3]=m44;

}
inline void Easy_matrix_translate_External(_Mat4 & Matrix, _Vec3 Pos)
{
	Matrix.f4X4[3][0] += Pos.Pos.x ;
	Matrix.f4X4[3][1] += Pos.Pos.y ;
	Matrix.f4X4[3][2] += Pos.Pos.z ;
}
inline void Easy_matrix_translate_External(_Mat4 & Matrix, float x, float y, float z)
{
	Matrix.f4X4[3][0] += x ;
	Matrix.f4X4[3][1] += y ;
	Matrix.f4X4[3][2] += z ;
}
inline void Easy_matrix_translate_External(float Matrix[4][4], float x, float y, float z)
{
	Matrix[3][0] += x ;
	Matrix[3][1] += y ;
	Matrix[3][2] += z ;
}
inline void Easy_matrix_translate_External(double Matrix[4][4], double x, double y, double z)
{
	Matrix[3][0] += x ;
	Matrix[3][1] += y ;
	Matrix[3][2] += z ;
}
inline void Easy_matrix_translate_External(__m128 Matrix[4], const __m128 Pos)
{
	Matrix[3].m128_f32[0] += Pos.m128_f32[0];
	Matrix[3].m128_f32[1] += Pos.m128_f32[1];
	Matrix[3].m128_f32[2] += Pos.m128_f32[2];
}
inline void Easy_matrix_mult(float Matrix[4][4], float a[4][4], float b[4][4]) {

    float tmp[4][4];
    int i, j, k;
    float ab;

    memcpy(tmp, a, 16 * sizeof(float));
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            ab = 0.0f;
            for (k = 0; k < 4; k++) ab += tmp[k][i] * b[j][k];
            Matrix[j][i] = ab;
        }
    }
}

inline void Easy_matrix_mult(_Mat4 & Matrix, const _Mat4 In1, const _Mat4 In2) 
{
#ifdef USE_SSE
	int				i;
	__m128			_t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7;

	_t4 = _mm_loadu_ps(&In1.f16[0]);
	_t5 = _mm_loadu_ps(&In1.f16[4]);
	_t6 = _mm_loadu_ps(&In1.f16[8]);
	_t7 = _mm_loadu_ps(&In1.f16[12]);

	for(i = 0; i < 4; i++)
	{
		_t0 = _mm_load1_ps(&In2.f16[i * 4 + 0]);
		_t0 = _mm_mul_ps(_t4, _t0);

		_t1 = _mm_load1_ps(&In2.f16[i * 4 + 1]);
		_t1 = _mm_mul_ps(_t5, _t1);

		_t2 = _mm_load1_ps(&In2.f16[i * 4 + 2]);
		_t2 = _mm_mul_ps(_t6, _t2);

		_t3 = _mm_load1_ps(&In2.f16[i * 4 + 3]);
		_t3 = _mm_mul_ps(_t7, _t3);

		_t1 = _mm_add_ps(_t0, _t1);
		_t2 = _mm_add_ps(_t1, _t2);
		_t3 = _mm_add_ps(_t2, _t3);
		
		_mm_storeu_ps(&Matrix.f16[i * 4], _t3);
	}

#else
    float tmp[16];
    int j;
    memcpy(tmp, a, 16 * sizeof(float));
    for (j = 0; j < 4; j++) {
		Matrix[j*4+0] = tmp[0] * b[j*4+0]+tmp[4] * b[j*4+1]+tmp[8] * b[j*4+2]+tmp[12] * b[j*4+3];
		Matrix[j*4+1] = tmp[1] * b[j*4+0]+tmp[5] * b[j*4+1]+tmp[9] * b[j*4+2]+tmp[13] * b[j*4+3];
		Matrix[j*4+2] = tmp[2] * b[j*4+0]+tmp[6] * b[j*4+1]+tmp[10] * b[j*4+2]+tmp[14] * b[j*4+3];
		Matrix[j*4+3] = tmp[3] * b[j*4+0]+tmp[7] * b[j*4+1]+tmp[11] * b[j*4+2]+tmp[15] * b[j*4+3];
    }
#endif

}
inline void Easy_matrix_mult(double * Matrix, const double * a, const double * b) 
{
    double tmp[16];
    int j;
    memcpy(tmp, a, 16 * sizeof(double));
    for (j = 0; j < 4; j++) {
		Matrix[j*4+0] = tmp[0] * b[j*4+0]+tmp[4] * b[j*4+1]+tmp[8] * b[j*4+2]+tmp[12] * b[j*4+3];
		Matrix[j*4+1] = tmp[1] * b[j*4+0]+tmp[5] * b[j*4+1]+tmp[9] * b[j*4+2]+tmp[13] * b[j*4+3];
		Matrix[j*4+2] = tmp[2] * b[j*4+0]+tmp[6] * b[j*4+1]+tmp[10] * b[j*4+2]+tmp[14] * b[j*4+3];
		Matrix[j*4+3] = tmp[3] * b[j*4+0]+tmp[7] * b[j*4+1]+tmp[11] * b[j*4+2]+tmp[15] * b[j*4+3];
    }


}
inline void Easy_matrix_mult(float * Matrix, const float * a, const float * b) 
{
    float tmp[16];
    int j;
    memcpy(tmp, a, 16 * sizeof(float));
    for (j = 0; j < 4; j++) {
		Matrix[j*4+0] = tmp[0] * b[j*4+0]+tmp[4] * b[j*4+1]+tmp[8] * b[j*4+2]+tmp[12] * b[j*4+3];
		Matrix[j*4+1] = tmp[1] * b[j*4+0]+tmp[5] * b[j*4+1]+tmp[9] * b[j*4+2]+tmp[13] * b[j*4+3];
		Matrix[j*4+2] = tmp[2] * b[j*4+0]+tmp[6] * b[j*4+1]+tmp[10] * b[j*4+2]+tmp[14] * b[j*4+3];
		Matrix[j*4+3] = tmp[3] * b[j*4+0]+tmp[7] * b[j*4+1]+tmp[11] * b[j*4+2]+tmp[15] * b[j*4+3];
    }


}
inline void Easy_matrix_mult(__m128 MatrixOut[4], const __m128 in1[4], const __m128 in2[4])
{

	_asm
	{
		
		mov ecx,MatrixOut
		mov edx,in1
		movaps xmm4,[edx]
		movaps xmm5,[edx+16]
		movaps xmm6,[edx+32]
		movaps xmm7,[edx+48]

		mov edx,in2
//-------------------------------------------
		movaps xmm0,[edx]
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		movaps xmm3,xmm0

		shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3
		movaps [ecx], xmm0
//-------------------------------------------
		movaps xmm0,[edx+16]
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		movaps xmm3,xmm0

		shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3
		movaps [ecx+16], xmm0
//-------------------------------------------
		movaps xmm0,[edx+32]
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		movaps xmm3,xmm0

		shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3
		movaps [ecx+32], xmm0
//-------------------------------------------
		movaps xmm0,[edx+48]
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		movaps xmm3,xmm0

		shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3
		movaps [ecx+48], xmm0
	}
	/*{
		__m128 e0 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[0] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[1] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[2] = a2;
	}

	{
		//(__m128&)_mm_shuffle_epi32(__m128i&)in2[0], _MM_SHUFFLE(3, 3, 3, 3))
		__m128 e0 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[3] = a2;
	}*/
}
inline void Easy_matrix_rotate_quat(float m[4][4], float q[4]) {
    float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz, l;
    float R[4][4];

    l = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
    if (fabs(l) < 1e-5) {
        s = 1.0f;
    } else {
        s = 2.0f / l;
    }

    xs = q[0] * s;
    ys = q[1] * s;
    zs = q[2] * s;
    wx = q[3] * xs;
    wy = q[3] * ys;
    wz = q[3] * zs;
    xx = q[0] * xs;
    xy = q[0] * ys;
    xz = q[0] * zs;
    yy = q[1] * ys;
    yz = q[1] * zs;
    zz = q[2] * zs;

    R[0][0] = 1.0f - (yy + zz);
    R[1][0] = xy - wz;
    R[2][0] = xz + wy;
    R[0][1] = xy + wz;
    R[1][1] = 1.0f - (xx + zz);
    R[2][1] = yz - wx;
    R[0][2] = xz - wy;
    R[1][2] = yz + wx;
    R[2][2] = 1.0f - (xx + yy);
    R[3][0] = R[3][1] = R[3][2] = R[0][3] = R[1][3] = R[2][3] = 0.0f;
    R[3][3] = 1.0f;

    //Easy_matrix_mult(m, m, R);
	Easy_matrix_mult(&m[0][0],&m[0][0],&R[0][0]);
}
inline void Easy_matrix_rotate_quat(double m[4][4], double q[4]) {
    double s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz, l;
    double R[4][4];

    l = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
    if (fabs(l) < 1e-5) {
        s = 1.0;
    } else {
        s = 2.0 / l;
    }

    xs = q[0] * s;
    ys = q[1] * s;
    zs = q[2] * s;
    wx = q[3] * xs;
    wy = q[3] * ys;
    wz = q[3] * zs;
    xx = q[0] * xs;
    xy = q[0] * ys;
    xz = q[0] * zs;
    yy = q[1] * ys;
    yz = q[1] * zs;
    zz = q[2] * zs;

    R[0][0] = 1.0f - (yy + zz);
    R[1][0] = xy - wz;
    R[2][0] = xz + wy;
    R[0][1] = xy + wz;
    R[1][1] = 1.0f - (xx + zz);
    R[2][1] = yz - wx;
    R[0][2] = xz - wy;
    R[1][2] = yz + wx;
    R[2][2] = 1.0f - (xx + yy);
    R[3][0] = R[3][1] = R[3][2] = R[0][3] = R[1][3] = R[2][3] = 0.0;
    R[3][3] = 1.0;

    //Easy_matrix_mult(m, m, R);
	Easy_matrix_mult(&m[0][0],&m[0][0],&R[0][0]);
}
inline void Easy_matrix_rotate_quat(_Mat4 & Matrix, _Quat Quat)
{
	Easy_matrix_rotate_quat(Matrix.f4X4,Quat.f);
}
inline void Easy_matrix_rotate_quat(__m128 m[4],const __m128 q) {
 /*   float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz, l;
    __m128 R[4];

	l = q.m128_f32[0] * q.m128_f32[0] + q.m128_f32[1] * q.m128_f32[1] + q.m128_f32[2] * q.m128_f32[2] + q.m128_f32[3] * q.m128_f32[3];
    if (fabs(l) < 1e-5) {
        s = 1.0f;
    } else {
        s = 2.0f / l;
    }

    xs = q.m128_f32[0] * s;
    ys = q.m128_f32[1] * s;
    zs = q.m128_f32[2] * s;
    wx = q.m128_f32[3] * xs;
    wy = q.m128_f32[3] * ys;
    wz = q.m128_f32[3] * zs;
    xx = q.m128_f32[0] * xs;
    xy = q.m128_f32[0] * ys;
    xz = q.m128_f32[0] * zs;
    yy = q.m128_f32[1] * ys;
    yz = q.m128_f32[1] * zs;
    zz = q.m128_f32[2] * zs;

    R[0].m128_f32[0] = 1.0f - (yy + zz);
    R[1].m128_f32[0] = xy - wz;
    R[2].m128_f32[0] = xz + wy;
    R[0].m128_f32[1] = xy + wz;
    R[1].m128_f32[1] = 1.0f - (xx + zz);
    R[2].m128_f32[1] = yz - wx;
    R[0].m128_f32[2] = xz - wy;
    R[1].m128_f32[2] = yz + wx;
    R[2].m128_f32[2] = 1.0f - (xx + yy);
    R[3].m128_f32[0] = R[3].m128_f32[1] = R[3].m128_f32[2] = R[0].m128_f32[3] = R[1].m128_f32[3] = R[2].m128_f32[3] = 0.0f;
    R[3].m128_f32[3] = 1.0f;
*/
	__m128 q2;
	__m128 R[4];
	Easy_quat_normalize(&q2,q);
	Easy_quat_to_matrix(R,q2);
    //Easy_matrix_mult(m, m, R);
	Easy_matrix_mult(m,m,R);
}
inline void Easy_matrix_rotate(float m[4][4], float angle, float ax, float ay, float az) {
    float q[4];
	float axis[3]={ax,ay,az};

   // lib3ds_vector_make(axis, ax, ay, az);
    Easy_quat_axis_angle(q, axis, angle);
    Easy_matrix_rotate_quat(m, q);
}
inline void Easy_matrix_rotate(double m[4][4], double angle, double ax, double ay, double az) {
    double q[4];
	double axis[3]={ax,ay,az};

   // lib3ds_vector_make(axis, ax, ay, az);
    Easy_quat_axis_angle(q, axis, angle);
    Easy_matrix_rotate_quat(m, q);
}
inline void Easy_matrix_rotate(__m128 m[4],const __m128 axis_angle) {
    __m128 q;
    Easy_quat_axis_angle(&q, axis_angle);
    Easy_matrix_rotate_quat(m, q);
}
inline void Easy_matrix_scale(_Mat4 & Matrix, _Vec3 Scale) 
{
    int i;

    for (i = 0; i < 4; i++) {
		Matrix.f4X4[0][i] *= Scale.Pos.x;
        Matrix.f4X4[1][i] *= Scale.Pos.y;
        Matrix.f4X4[2][i] *= Scale.Pos.z;
    }
}
inline void Easy_matrix_scale(float m[4][4], float x, float y, float z) 
{
    int i;

    for (i = 0; i < 4; i++) {
        m[0][i] *= x;
        m[1][i] *= y;
        m[2][i] *= z;
    }
}
inline void Easy_matrix_scale(double m[4][4], double x, double y, double z) 
{
    int i;

    for (i = 0; i < 4; i++) {
        m[0][i] *= x;
        m[1][i] *= y;
        m[2][i] *= z;
    }
}
inline void Easy_matrix_scale(__m128 MatrixOut[4], const __m128 VecIn) 
{
	_asm
	{
		mov edx,MatrixOut
		movaps xmm0,[edx]
		movaps xmm1,[edx+16]
		movaps xmm2,[edx+32]
		movaps xmm3,[edx+48]

		movaps xmm4,VecIn
		movaps xmm5,xmm4
		movaps xmm6,xmm4
		movaps xmm7,xmm4

		shufps xmm4,xmm4,0x00
		shufps xmm5,xmm5,0x55
		shufps xmm6,xmm6,0xaa
		shufps xmm7,xmm7,0xff

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		mov edx,MatrixOut
		movaps [edx],xmm0
		movaps [edx+16],xmm1
		movaps [edx+32],xmm2
		movaps [edx+48],xmm3
	}
}
inline void Easy_matrix_copy(__m128 MatrixOut[4],const __m128 MatrixIn[4]) 
{
	_asm
	{
		mov edx,MatrixIn
		movaps xmm0,[edx]
		movaps xmm1,[edx+16]
		movaps xmm2,[edx+32]
		movaps xmm3,[edx+48]
		mov edx,MatrixOut
		movaps [edx],xmm0
		movaps [edx+16],xmm1
		movaps [edx+32],xmm2
		movaps [edx+48],xmm3
	}
}
inline void Easy_matrix_copy(float dest[4][4], float src[4][4]) {
    memcpy(dest, src, 16 * sizeof(float));
}
inline void Easy_matrix_copy(float dest[16], float src[16]) {
    memcpy(dest, src, 16 * sizeof(float));
}
inline void Easy_matrix_copy(double dest[16], double src[16]) {
    memcpy(dest, src, 16 * sizeof(double));
}
inline void Easy_matrix_copy(__m128 MatrixOut[4],const float MatrixIn[4][4]) 
{
	_asm
	{
		mov edx,MatrixIn
		movups xmm0,[edx]
		movups xmm1,[edx+16]
		movups xmm2,[edx+32]
		movups xmm3,[edx+48]
		mov edx,MatrixOut
		movaps [edx],xmm0
		movaps [edx+16],xmm1
		movaps [edx+32],xmm2
		movaps [edx+48],xmm3
	}
}
inline void Easy_matrix_copy(float MatrixOut[4][4],const __m128 MatrixIn[4]) 
{
	_asm
	{
		mov edx,MatrixIn
		movaps xmm0,[edx]
		movaps xmm1,[edx+16]
		movaps xmm2,[edx+32]
		movaps xmm3,[edx+48]
		mov edx,MatrixOut
		movups [edx],xmm0
		movups [edx+16],xmm1
		movups [edx+32],xmm2
		movups [edx+48],xmm3
	}
}
//http://www.devmaster.net/forums/showthread.php?t=14569
inline void Easy_matrix_mult_vector3X3(float vOut[3],const float * m,const float v[3])
{
//	v[0] = m[0]*v[0]+m[4]*v[1]+m[8]*v[2]+m[12]*v[3];
//	v[1] = m[1]*v[0]+m[5]*v[1]+m[9]*v[2]+m[13]*v[3];
//	v[2] = m[2]*v[0]+m[6]*v[1]+m[10]*v[2]+m[14]*v[3];
//	v[3] = m[3]*v[0]+m[7]*v[1]+m[11]*v[2]+m[15]*v[3];


	vOut[0] = m[0]*v[0]+m[4]*v[1]+m[8]*v[2]+m[12];
	vOut[1] = m[1]*v[0]+m[5]*v[1]+m[9]*v[2]+m[13];
	vOut[2] = m[2]*v[0]+m[6]*v[1]+m[10]*v[2]+m[14];

}
inline void Easy_matrix_mult_vector3X3(__m128 * vOut ,const __m128 MatrixIn[4],const __m128 vIN)
{

	_asm
	{
		mov edx,MatrixIn
		movaps xmm4,[edx]
		movaps xmm5,[edx+16]
		movaps xmm6,[edx+32]
		movaps xmm7,[edx+48]

		movaps xmm0,vIN
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		//movups xmm3,xmm0

		//shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		//mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm7//addps xmm0,xmm3
		mov    ecx, vOut
		movaps [ecx], xmm0
	}

}
inline void Easy_matrix_mult_Normal3X3(__m128 * vOut ,const __m128 MatrixIn[4],const __m128 vIN)
{

	_asm
	{
		mov edx,MatrixIn
		movaps xmm4,[edx]
		movaps xmm5,[edx+16]
		movaps xmm6,[edx+32]
		//movaps xmm7,[edx+48]

		movaps xmm0,vIN
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		//movups xmm3,xmm0

		//shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		//mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		//addps xmm0,xmm7//addps xmm0,xmm3
		mov    ecx, vOut
		movaps [ecx], xmm0
	}

}
inline void Easy_matrix_mult_vector4X4(float vOut[4],const float * m,const float v[4])
{
	vOut[0] = m[0]*v[0]+m[4]*v[1]+m[8]*v[2]+m[12]*v[3];
	vOut[1] = m[1]*v[0]+m[5]*v[1]+m[9]*v[2]+m[13]*v[3];
	vOut[2] = m[2]*v[0]+m[6]*v[1]+m[10]*v[2]+m[14]*v[3];
	vOut[3] = m[3]*v[0]+m[7]*v[1]+m[11]*v[2]+m[15]*v[3];
}

inline void Easy_matrix_mult_vector4X4(__m128 * vOut ,const __m128 MatrixIn[4],const __m128 vIN)
{

	_asm
	{
		mov edx,MatrixIn
		movaps xmm4,[edx]
		movaps xmm5,[edx+16]
		movaps xmm6,[edx+32]
		movaps xmm7,[edx+48]

		movaps xmm0,vIN
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		movaps xmm3,xmm0

		shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3
		mov    ecx, vOut
		movaps [ecx], xmm0
	}

}
inline void Easy_matrix_mult_vector4X4(float vOut[4] ,const __m128 MatrixIn[4],const float vIN[4])
{

	_asm
	{
		mov edx,MatrixIn
		movaps xmm4,[edx]
		movaps xmm5,[edx+16]
		movaps xmm6,[edx+32]
		movaps xmm7,[edx+48]

		mov edx,vIN
		movups xmm0,[edx]
		movaps xmm1,xmm0
		movaps xmm2,xmm0
		movaps xmm3,xmm0

		shufps xmm3,xmm3,0xff
		shufps xmm2,xmm2,0xaa
		shufps xmm1,xmm1,0x55
		shufps xmm0,xmm0,0x00

		mulps xmm0,xmm4
		mulps xmm1,xmm5
		mulps xmm2,xmm6
		mulps xmm3,xmm7

		addps xmm0,xmm1
		addps xmm0,xmm2
		addps xmm0,xmm3
		mov    ecx, vOut
		movups [ecx], xmm0
	}

}
inline __m128 _mm_dot_ps(__m128 v1, __m128 v2)
{
	__m128 mul0,swp0,add0,swp1,add1;
	 mul0 = _mm_mul_ps(v1, v2);
	 swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
	 add0 = _mm_add_ps(mul0, swp0);
	 swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
	 add1 = _mm_add_ps(add0, swp1);
	return add1;
}
inline void _mm_mul_matrix(__m128 in1[4], __m128 in2[4], __m128 out[4])
{
	{
		__m128 e0 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[0] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[1] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[2] = a2;
	}

	{
		//(__m128&)_mm_shuffle_epi32(__m128i&)in2[0], _MM_SHUFFLE(3, 3, 3, 3))
		__m128 e0 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(in1[0], e0);
		__m128 m1 = _mm_mul_ps(in1[1], e1);
		__m128 m2 = _mm_mul_ps(in1[2], e2);
		__m128 m3 = _mm_mul_ps(in1[3], e3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		out[3] = a2;
	}
}
inline void Easy_matrix_inv(__m128 const MatrixIn[4], __m128 MatrixOut[4])
{
	__m128 Fac0;
	{
		//	valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//	valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//	valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		//	valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Swp00 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac0 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	//__asm
	//{
	//	mov edx,MatrixIn
	//	movaps xmm4,[edx]
	//	movaps xmm5,[edx+16]
	//	movaps xmm6,[edx+32]
	//	movaps xmm7,[edx+48]
	//}
	__m128 Fac1;
	{
		//	valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//	valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//	valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		//	valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac1 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}


	__m128 Fac2;
	{
		//	valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//	valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//	valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		//	valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac2 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac3;
	{
		//	valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//	valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//	valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		//	valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac3 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac4;
	{
		//	valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//	valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//	valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		//	valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac4 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 Fac5;
	{
		//	valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//	valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//	valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		//	valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		__m128 Swp0a = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp0b = _mm_shuffle_ps(MatrixIn[3], MatrixIn[2], _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(MatrixIn[2], MatrixIn[1], _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac5 = _mm_sub_ps(Mul00, Mul01);

		bool stop = true;
	}

	__m128 SignA = _mm_set_ps( 1.0f,-1.0f, 1.0f,-1.0f);
	__m128 SignB = _mm_set_ps(-1.0f, 1.0f,-1.0f, 1.0f);

	// m[1][0]
	// m[0][0]
	// m[0][0]
	// m[0][0]
	__m128 Temp0 = _mm_shuffle_ps(MatrixIn[1], MatrixIn[0], _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Vec0 = _mm_shuffle_ps(Temp0, Temp0, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][1]
	// m[0][1]
	// m[0][1]
	// m[0][1]
	__m128 Temp1 = _mm_shuffle_ps(MatrixIn[1], MatrixIn[0], _MM_SHUFFLE(1, 1, 1, 1));
	__m128 Vec1 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][2]
	// m[0][2]
	// m[0][2]
	// m[0][2]
	__m128 Temp2 = _mm_shuffle_ps(MatrixIn[1], MatrixIn[0], _MM_SHUFFLE(2, 2, 2, 2));
	__m128 Vec2 = _mm_shuffle_ps(Temp2, Temp2, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][3]
	// m[0][3]
	// m[0][3]
	// m[0][3]
	__m128 Temp3 = _mm_shuffle_ps(MatrixIn[1], MatrixIn[0], _MM_SHUFFLE(3, 3, 3, 3));
	__m128 Vec3 = _mm_shuffle_ps(Temp3, Temp3, _MM_SHUFFLE(2, 2, 2, 0));

	// col0
	// + (Vec1[0] * Fac0[0] - Vec2[0] * Fac1[0] + Vec3[0] * Fac2[0]),
	// - (Vec1[1] * Fac0[1] - Vec2[1] * Fac1[1] + Vec3[1] * Fac2[1]),
	// + (Vec1[2] * Fac0[2] - Vec2[2] * Fac1[2] + Vec3[2] * Fac2[2]),
	// - (Vec1[3] * Fac0[3] - Vec2[3] * Fac1[3] + Vec3[3] * Fac2[3]),
	__m128 Mul00 = _mm_mul_ps(Vec1, Fac0);
	__m128 Mul01 = _mm_mul_ps(Vec2, Fac1);
	__m128 Mul02 = _mm_mul_ps(Vec3, Fac2);
	__m128 Sub00 = _mm_sub_ps(Mul00, Mul01);
	__m128 Add00 = _mm_add_ps(Sub00, Mul02);
	__m128 Inv0 = _mm_mul_ps(SignB, Add00);

	// col1
	// - (Vec0[0] * Fac0[0] - Vec2[0] * Fac3[0] + Vec3[0] * Fac4[0]),
	// + (Vec0[0] * Fac0[1] - Vec2[1] * Fac3[1] + Vec3[1] * Fac4[1]),
	// - (Vec0[0] * Fac0[2] - Vec2[2] * Fac3[2] + Vec3[2] * Fac4[2]),
	// + (Vec0[0] * Fac0[3] - Vec2[3] * Fac3[3] + Vec3[3] * Fac4[3]),
	__m128 Mul03 = _mm_mul_ps(Vec0, Fac0);
	__m128 Mul04 = _mm_mul_ps(Vec2, Fac3);
	__m128 Mul05 = _mm_mul_ps(Vec3, Fac4);
	__m128 Sub01 = _mm_sub_ps(Mul03, Mul04);
	__m128 Add01 = _mm_add_ps(Sub01, Mul05);
	__m128 Inv1 = _mm_mul_ps(SignA, Add01);

	// col2
	// + (Vec0[0] * Fac1[0] - Vec1[0] * Fac3[0] + Vec3[0] * Fac5[0]),
	// - (Vec0[0] * Fac1[1] - Vec1[1] * Fac3[1] + Vec3[1] * Fac5[1]),
	// + (Vec0[0] * Fac1[2] - Vec1[2] * Fac3[2] + Vec3[2] * Fac5[2]),
	// - (Vec0[0] * Fac1[3] - Vec1[3] * Fac3[3] + Vec3[3] * Fac5[3]),
	__m128 Mul06 = _mm_mul_ps(Vec0, Fac1);
	__m128 Mul07 = _mm_mul_ps(Vec1, Fac3);
	__m128 Mul08 = _mm_mul_ps(Vec3, Fac5);
	__m128 Sub02 = _mm_sub_ps(Mul06, Mul07);
	__m128 Add02 = _mm_add_ps(Sub02, Mul08);
	__m128 Inv2 = _mm_mul_ps(SignB, Add02);

	// col3
	// - (Vec1[0] * Fac2[0] - Vec1[0] * Fac4[0] + Vec2[0] * Fac5[0]),
	// + (Vec1[0] * Fac2[1] - Vec1[1] * Fac4[1] + Vec2[1] * Fac5[1]),
	// - (Vec1[0] * Fac2[2] - Vec1[2] * Fac4[2] + Vec2[2] * Fac5[2]),
	// + (Vec1[0] * Fac2[3] - Vec1[3] * Fac4[3] + Vec2[3] * Fac5[3]));
	__m128 Mul09 = _mm_mul_ps(Vec0, Fac2);
	__m128 Mul10 = _mm_mul_ps(Vec1, Fac4);
	__m128 Mul11 = _mm_mul_ps(Vec2, Fac5);
	__m128 Sub03 = _mm_sub_ps(Mul09, Mul10);
	__m128 Add03 = _mm_add_ps(Sub03, Mul11);
	__m128 Inv3 = _mm_mul_ps(SignA, Add03);

	__m128 Row0 = _mm_shuffle_ps(Inv0, Inv1, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row1 = _mm_shuffle_ps(Inv2, Inv3, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row2 = _mm_shuffle_ps(Row0, Row1, _MM_SHUFFLE(2, 0, 2, 0));

	//	valType Determinant = m[0][0] * Inverse[0][0] 
	//						+ m[0][1] * Inverse[1][0] 
	//						+ m[0][2] * Inverse[2][0] 
	//						+ m[0][3] * Inverse[3][0];
	__m128 Det0 = _mm_dot_ps(MatrixIn[0], Row2);
	__m128 Rcp0 = _mm_div_ps(one, Det0);
	//__m128 Rcp0 = _mm_rcp_ps(Det0);

	//	Inverse /= Determinant;
	MatrixOut[0] = _mm_mul_ps(Inv0, Rcp0);
	MatrixOut[1] = _mm_mul_ps(Inv1, Rcp0);
	MatrixOut[2] = _mm_mul_ps(Inv2, Rcp0);
	MatrixOut[3] = _mm_mul_ps(Inv3, Rcp0);
}

inline void Easy_matrix_inv(float m[4][4]) 
{
#ifdef USE_SSE
	__m128 matrixIN[4],matrixOUT[4];
	matrixIN[0]=_mm_loadu_ps(&m[0][0]);
	matrixIN[1]=_mm_loadu_ps(&m[1][0]);
	matrixIN[2]=_mm_loadu_ps(&m[2][0]);
	matrixIN[3]=_mm_loadu_ps(&m[3][0]);
	Easy_matrix_inv(matrixIN,matrixOUT);
	_mm_storeu_ps(&m[0][0],matrixOUT[0]);
	_mm_storeu_ps(&m[1][0],matrixOUT[1]);
	_mm_storeu_ps(&m[2][0],matrixOUT[2]);
	_mm_storeu_ps(&m[3][0],matrixOUT[3]);
#else
    int i, j, k;
    int pvt_i[4], pvt_j[4];            /* Locations of pivot elements */
    float pvt_val;               /* Value of current pivot element */
    float hold;                  /* Temporary storage */
    float determinat;

    determinat = 1.0f;
    for (k = 0; k < 4; k++)  {
        /* Locate k'th pivot element */
        pvt_val = m[k][k];          /* Initialize for search */
        pvt_i[k] = k;
        pvt_j[k] = k;
        for (i = k; i < 4; i++) {
            for (j = k; j < 4; j++) {
                if (fabs(m[i][j]) > fabs(pvt_val)) {
                    pvt_i[k] = i;
                    pvt_j[k] = j;
                    pvt_val = m[i][j];
                }
            }
        }

        /* Product of pivots, gives determinant when finished */
        determinat *= pvt_val;
        if (fabs(determinat) < 1e-5) {
            return;  /* Matrix is singular (zero determinant) */
        }

        /* "Interchange" rows (with sign change stuff) */
        i = pvt_i[k];
        if (i != k) {             /* If rows are different */
            for (j = 0; j < 4; j++) {
                hold = -m[k][j];
                m[k][j] = m[i][j];
                m[i][j] = hold;
            }
        }

        /* "Interchange" columns */
        j = pvt_j[k];
        if (j != k) {            /* If columns are different */
            for (i = 0; i < 4; i++) {
                hold = -m[i][k];
                m[i][k] = m[i][j];
                m[i][j] = hold;
            }
        }

        /* Divide column by minus pivot value */
        for (i = 0; i < 4; i++) {
            if (i != k) m[i][k] /= (-pvt_val) ;
        }

        /* Reduce the matrix */
        for (i = 0; i < 4; i++) {
            hold = m[i][k];
            for (j = 0; j < 4; j++) {
                if (i != k && j != k) m[i][j] += hold * m[k][j];
            }
        }

        /* Divide row by pivot */
        for (j = 0; j < 4; j++) {
            if (j != k) m[k][j] /= pvt_val;
        }

        /* Replace pivot by reciprocal (at last we can touch it). */
        m[k][k] = 1.0f / pvt_val;
    }

    /* That was most of the work, one final pass of row/column interchange */
    /* to finish */
    for (k = 4 - 2; k >= 0; k--) { /* Don't need to work with 1 by 1 corner*/
        i = pvt_j[k];          /* Rows to swap correspond to pivot COLUMN */
        if (i != k) {          /* If rows are different */
            for (j = 0; j < 4; j++) {
                hold = m[k][j];
                m[k][j] = -m[i][j];
                m[i][j] = hold;
            }
        }

        j = pvt_i[k];         /* Columns to swap correspond to pivot ROW */
        if (j != k)           /* If columns are different */
            for (i = 0; i < 4; i++) {
                hold = m[i][k];
                m[i][k] = -m[i][j];
                m[i][j] = hold;
            }
    }
#endif
}

inline void Easy_matrix_inv(float * m) 
{
	__m128 matrixIN[4],matrixOUT[4];
	matrixIN[0]=_mm_loadu_ps(m+0);
	matrixIN[1]=_mm_loadu_ps(m+4);
	matrixIN[2]=_mm_loadu_ps(m+8);
	matrixIN[3]=_mm_loadu_ps(m+12);
	Easy_matrix_inv(matrixIN,matrixOUT);
	_mm_storeu_ps(m+0,matrixOUT[0]);
	_mm_storeu_ps(m+4,matrixOUT[1]);
	_mm_storeu_ps(m+8,matrixOUT[2]);
	_mm_storeu_ps(m+12,matrixOUT[3]);
}
inline void Easy_matrix_inv(double m[4][4]) 
{

    int i, j, k;
    int pvt_i[4], pvt_j[4];            /* Locations of pivot elements */
    double pvt_val;               /* Value of current pivot element */
    double hold;                  /* Temporary storage */
    double determinat;

    determinat = 1.0;
    for (k = 0; k < 4; k++)  {
        /* Locate k'th pivot element */
        pvt_val = m[k][k];          /* Initialize for search */
        pvt_i[k] = k;
        pvt_j[k] = k;
        for (i = k; i < 4; i++) {
            for (j = k; j < 4; j++) {
                if (fabs(m[i][j]) > fabs(pvt_val)) {
                    pvt_i[k] = i;
                    pvt_j[k] = j;
                    pvt_val = m[i][j];
                }
            }
        }

        /* Product of pivots, gives determinant when finished */
        determinat *= pvt_val;
        if (fabs(determinat) < 1e-5) {
            return;  /* Matrix is singular (zero determinant) */
        }

        /* "Interchange" rows (with sign change stuff) */
        i = pvt_i[k];
        if (i != k) {             /* If rows are different */
            for (j = 0; j < 4; j++) {
                hold = -m[k][j];
                m[k][j] = m[i][j];
                m[i][j] = hold;
            }
        }

        /* "Interchange" columns */
        j = pvt_j[k];
        if (j != k) {            /* If columns are different */
            for (i = 0; i < 4; i++) {
                hold = -m[i][k];
                m[i][k] = m[i][j];
                m[i][j] = hold;
            }
        }

        /* Divide column by minus pivot value */
        for (i = 0; i < 4; i++) {
            if (i != k) m[i][k] /= (-pvt_val) ;
        }

        /* Reduce the matrix */
        for (i = 0; i < 4; i++) {
            hold = m[i][k];
            for (j = 0; j < 4; j++) {
                if (i != k && j != k) m[i][j] += hold * m[k][j];
            }
        }

        /* Divide row by pivot */
        for (j = 0; j < 4; j++) {
            if (j != k) m[k][j] /= pvt_val;
        }

        /* Replace pivot by reciprocal (at last we can touch it). */
        m[k][k] = 1.0f / pvt_val;
    }

    /* That was most of the work, one final pass of row/column interchange */
    /* to finish */
    for (k = 4 - 2; k >= 0; k--) { /* Don't need to work with 1 by 1 corner*/
        i = pvt_j[k];          /* Rows to swap correspond to pivot COLUMN */
        if (i != k) {          /* If rows are different */
            for (j = 0; j < 4; j++) {
                hold = m[k][j];
                m[k][j] = -m[i][j];
                m[i][j] = hold;
            }
        }

        j = pvt_i[k];         /* Columns to swap correspond to pivot ROW */
        if (j != k)           /* If columns are different */
            for (i = 0; i < 4; i++) {
                hold = m[i][k];
                m[i][k] = -m[i][j];
                m[i][j] = hold;
            }
    }

}

inline void Easy_matrix_camera(float matrix[4][4], float pos[3], float tgt[3], float roll) {
    float M[4][4];
    float x[3], y[3], z[3];

	y[0]=tgt[0]-pos[0];
	y[1]=tgt[1]-pos[1];
	y[2]=tgt[2]-pos[2];
    //Easy_vector_sub(y, tgt, pos);
    Easy_vector_normalize(y);

    if (y[0] != 0. || y[1] != 0) {
        z[0] = 0;
        z[1] = 0;
        z[2] = 1.0;
    } else { /* Special case:  looking straight up or down z axis */
        z[0] = -1.0;
        z[1] = 0;
        z[2] = 0;
    }

    Easy_vector_cross(x, y, z);
    Easy_vector_cross(z, x, y);
    Easy_vector_normalize(x);
    Easy_vector_normalize(z);

    Easy_matrix_identity(M);
    M[0][0] = x[0];
    M[1][0] = x[1];
    M[2][0] = x[2];
    M[0][1] = y[0];
    M[1][1] = y[1];
    M[2][1] = y[2];
    M[0][2] = z[0];
    M[1][2] = z[1];
    M[2][2] = z[2];

    Easy_matrix_identity(matrix);
    Easy_matrix_rotate(matrix, roll, 0, 1, 0);
    Easy_matrix_mult(&matrix[0][0], &matrix[0][0], &M[0][0]);
    Easy_matrix_translate_Internal(matrix, -pos[0], -pos[1], -pos[2]);
}
inline void Easy_matrix_camera(float matrix[4][4], float pos[3], float tgt[3]) {
    float x[3], y[3], z[3];

	y[0]=tgt[0]-pos[0];
	y[1]=tgt[1]-pos[1];
	y[2]=tgt[2]-pos[2];
    Easy_vector_normalize(y);

    if (y[0] != 0. || y[1] != 0) {
        z[0] = 0;
        z[1] = 0;
        z[2] = 1.0;
    } else { /* Special case:  looking straight up or down z axis */
        z[0] = -1.0;
        z[1] = 0;
        z[2] = 0;
    }

    Easy_vector_cross(x, y, z);
    Easy_vector_cross(z, x, y);
    Easy_vector_normalize(x);
    Easy_vector_normalize(z);

    Easy_matrix_identity(matrix);
    matrix[0][0] = x[0];
    matrix[1][0] = x[1];
    matrix[2][0] = x[2];
    matrix[0][1] = y[0];
    matrix[1][1] = y[1];
    matrix[2][1] = y[2];
    matrix[0][2] = z[0];
    matrix[1][2] = z[1];
    matrix[2][2] = z[2];

    Easy_matrix_translate_External(matrix, pos[0],pos[1], pos[2]);
}
inline void Easy_matrix_float4X4_to_m128X4(__m128 MatrixOut[4],const float * MatrixIn)
{
	_asm
	{
		mov edx,MatrixIn
		movups xmm0,[edx]
		movups xmm1,[edx+16]
		movups xmm2,[edx+32]
		movups xmm3,[edx+48]
		mov edx,MatrixOut
		movaps [edx],xmm0
		movaps [edx+16],xmm1
		movaps [edx+32],xmm2
		movaps [edx+48],xmm3
	}
}
inline void Easy_matrix_m128X4_to_float4X4(float * MatrixOut,const __m128 MatrixIn[4])
{
	_asm
	{
		mov edx,MatrixIn
		movaps xmm0,[edx]
		movaps xmm1,[edx+16]
		movaps xmm2,[edx+32]
		movaps xmm3,[edx+48]
		mov edx,MatrixOut
		movups [edx],xmm0
		movups [edx+16],xmm1
		movups [edx+32],xmm2
		movups [edx+48],xmm3
	}
}
inline void Easy_matrix_copy(__m128 MatrixOut[4],const float * MatrixIn)
{
	_asm
	{
		mov edx,MatrixIn
		movups xmm0,[edx]
		movups xmm1,[edx+16]
		movups xmm2,[edx+32]
		movups xmm3,[edx+48]
		mov edx,MatrixOut
		movaps [edx],xmm0
		movaps [edx+16],xmm1
		movaps [edx+32],xmm2
		movaps [edx+48],xmm3
	}
}
inline void Easy_matrix_copy(float * MatrixOut,const __m128 MatrixIn[4])
{
	_asm
	{
		mov edx,MatrixIn
		movaps xmm0,[edx]
		movaps xmm1,[edx+16]
		movaps xmm2,[edx+32]
		movaps xmm3,[edx+48]
		mov edx,MatrixOut
		movups [edx],xmm0
		movups [edx+16],xmm1
		movups [edx+32],xmm2
		movups [edx+48],xmm3
	}
}
inline void Test_matrix()
{
	__m128 TestSSE=_mm_set_ps(4.0f,3.0f,2.0f,1.0f);
	__m128 TestSSE2=_mm_set_ps(10.0f,10.0f,10.0f,10.0f);
	float TestFloat[4]={1.0f,2.0f,3.0f,4.0f};
	float TestFloat2[4]={10.0f,10.0f,10.0f,10.0f};
	float TestFloatmatrix[4][4]=
	{
		1,2,3,4,
		5,6,7,8,
		9,10,11,12,
		13,14,15,16
	};





}
inline void PointProjectD(double objx, double objy, double objz, double *modelview, double *projection, int *viewport, double *windowCoordinate)
  {
      //Transformation vectors
      double fTempo[8];
      //Modelview transform
      fTempo[0]=modelview[0]*objx+modelview[4]*objy+modelview[8]*objz+modelview[12];  //w is always 1
      fTempo[1]=modelview[1]*objx+modelview[5]*objy+modelview[9]*objz+modelview[13];
      fTempo[2]=modelview[2]*objx+modelview[6]*objy+modelview[10]*objz+modelview[14];
      fTempo[3]=modelview[3]*objx+modelview[7]*objy+modelview[11]*objz+modelview[15];
      //Projection transform, the final row of projection matrix is always [0 0 -1 0]
      //so we optimize for that.
      fTempo[4]=projection[0]*fTempo[0]+projection[4]*fTempo[1]+projection[8]*fTempo[2]+projection[12]*fTempo[3];
      fTempo[5]=projection[1]*fTempo[0]+projection[5]*fTempo[1]+projection[9]*fTempo[2]+projection[13]*fTempo[3];
      fTempo[6]=projection[2]*fTempo[0]+projection[6]*fTempo[1]+projection[10]*fTempo[2]+projection[14]*fTempo[3];
      fTempo[7]=-fTempo[2];
      //The result normalizes between -1 and 1
      if(abs(fTempo[7])>=0.0000001)	//The w value
      fTempo[7]=1.0/fTempo[7];
      //Perspective division
      fTempo[4]*=fTempo[7];
      fTempo[5]*=fTempo[7];
      fTempo[6]*=fTempo[7];
      //Window coordinates
      //Map x, y to range 0-1
      windowCoordinate[0]=(fTempo[4]*0.5+0.5)*viewport[2]+viewport[0];
      windowCoordinate[1]=(fTempo[5]*0.5+0.5)*viewport[3]+viewport[1];
      //This is only correct when glDepthRange(0.0, 1.0)
      windowCoordinate[2]=(1.0+fTempo[6])*0.5;	//Between 0 and 1
      //return 1;
  }

inline void PointProjectD(float * obj, double *projection, int *viewport, double *windowCoordinate)
  {
      //Transformation vectors
      double fTempo[8];
      //Modelview transform
      fTempo[0]=obj[0];  //w is always 1
      fTempo[1]=obj[1];
      fTempo[2]=obj[2];
      fTempo[3]=1.0;
      //Projection transform, the final row of projection matrix is always [0 0 -1 0]
      //so we optimize for that.
      fTempo[4]=projection[0]*fTempo[0]+projection[4]*fTempo[1]+projection[8]*fTempo[2]+projection[12]*fTempo[3];
      fTempo[5]=projection[1]*fTempo[0]+projection[5]*fTempo[1]+projection[9]*fTempo[2]+projection[13]*fTempo[3];
      fTempo[6]=projection[2]*fTempo[0]+projection[6]*fTempo[1]+projection[10]*fTempo[2]+projection[14]*fTempo[3];
      fTempo[7]=-fTempo[2];
      //The result normalizes between -1 and 1
      if(abs(fTempo[7])>=0.0000001)	//The w value
      fTempo[7]=1.0/fTempo[7];
      //Perspective division
      fTempo[4]*=fTempo[7];
      fTempo[5]*=fTempo[7];
      fTempo[6]*=fTempo[7];
      //Window coordinates
      //Map x, y to range 0-1
      windowCoordinate[0]=(fTempo[4]*0.5+0.5)*viewport[2]+viewport[0];
      windowCoordinate[1]=(fTempo[5]*0.5+0.5)*viewport[3]+viewport[1];
      //This is only correct when glDepthRange(0.0, 1.0)
      windowCoordinate[2]=(1.0+fTempo[6])*0.5;	//Between 0 and 1
      //return 1;
  }
inline void PointProjectF(float * obj, float *projection, int *viewport, float *windowCoordinate)
  {
      //Transformation vectors
      float fTempo[8];
      //Modelview transform
      fTempo[0]=obj[0];  //w is always 1
      fTempo[1]=obj[1];
      fTempo[2]=obj[2];
      fTempo[3]=1.0f;
      //Projection transform, the final row of projection matrix is always [0 0 -1 0]
      //so we optimize for that.
      fTempo[4]=projection[0]*fTempo[0]+projection[4]*fTempo[1]+projection[8]*fTempo[2]+projection[12]*fTempo[3];
      fTempo[5]=projection[1]*fTempo[0]+projection[5]*fTempo[1]+projection[9]*fTempo[2]+projection[13]*fTempo[3];
      fTempo[6]=projection[2]*fTempo[0]+projection[6]*fTempo[1]+projection[10]*fTempo[2]+projection[14]*fTempo[3];
      fTempo[7]=-fTempo[2];
      //The result normalizes between -1 and 1
      if(abs(fTempo[7])>=0.0000001f)	//The w value
      fTempo[7]=1.0f/fTempo[7];
      //Perspective division
      fTempo[4]*=fTempo[7];
      fTempo[5]*=fTempo[7];
      fTempo[6]*=fTempo[7];
      //Window coordinates
      //Map x, y to range 0-1
      windowCoordinate[0]=(fTempo[4]*0.5f+0.5f)*viewport[2]+viewport[0];
      windowCoordinate[1]=(fTempo[5]*0.5f+0.5f)*viewport[3]+viewport[1];
      //This is only correct when glDepthRange(0.0, 1.0)
      windowCoordinate[2]=(1.0f+fTempo[6])*0.5f;	//Between 0 and 1
      //return 1;
  }
inline void EasyOrtho(float left, float right, float bottom, float top, float n, float f, float * Matrix)
{
	Matrix[0] = 2 / (right - left);	Matrix[4] = 0;						Matrix[8] = 0;					Matrix[12] = -(right + left) / (right - left);
	Matrix[1] = 0;						Matrix[5] = 2 / (top - bottom);	Matrix[9] = 0;					Matrix[13] = -(top + bottom) / (top - bottom);
	Matrix[2] = 0;						Matrix[6] = 0;						Matrix[10] = -2 / (f - n);		Matrix[14] = -(f + n) / (f - n);
	Matrix[3] = 0;						Matrix[7] = 0;						Matrix[11] = 0;				Matrix[15] = 1;
}
inline void EasyOrtho(double left, double right, double bottom, double top, double n, double f, double * Matrix)
{
	Matrix[0] = 2 / (right - left);	Matrix[4] = 0;						Matrix[8] = 0;					Matrix[12] = -(right + left) / (right - left);
	Matrix[1] = 0;						Matrix[5] = 2 / (top - bottom);	Matrix[9] = 0;					Matrix[13] = -(top + bottom) / (top - bottom);
	Matrix[2] = 0;						Matrix[6] = 0;						Matrix[10] = -2 / (f - n);		Matrix[14] = -(f + n) / (f - n);
	Matrix[3] = 0;						Matrix[7] = 0;						Matrix[11] = 0;				Matrix[15] = 1;
}
inline void EastPerspective(float fovyInDegrees, float aspectRatio,
                      float znear, float zfar,float * Matrix)
{
    float ymax, xmax;
    ymax = znear * tan(fovyInDegrees * 3.14159265358979323846f / 360.0f);
    xmax = ymax * aspectRatio;

	Matrix[0] = znear / xmax;
    Matrix[1] = 0.0;
    Matrix[2] = 0.0;
    Matrix[3] = 0.0;
    Matrix[4] = 0.0;
    Matrix[5] = znear / ymax;
    Matrix[6] = 0.0;
    Matrix[7] = 0.0;
    Matrix[8] = 0.0;
    Matrix[9] = 0.0;
    Matrix[10] = (-zfar - znear) / (zfar - znear);
    Matrix[11] = -1.0;
    Matrix[12] = 0.0;
    Matrix[13] = 0.0;
    Matrix[14] = (-2.0f*znear * zfar) /  (zfar - znear);
    Matrix[15] = 0.0;
}
inline void EastPerspective(double fovyInDegrees, double aspectRatio,
                      double znear, double zfar,double * Matrix)
{
    double ymax, xmax;
    ymax = znear * tan(fovyInDegrees * 3.14159265358979323846 / 360.0);
    xmax = ymax * aspectRatio;

	Matrix[0] = znear / xmax;
    Matrix[1] = 0.0;
    Matrix[2] = 0.0;
    Matrix[3] = 0.0;
    Matrix[4] = 0.0;
    Matrix[5] = znear / ymax;
    Matrix[6] = 0.0;
    Matrix[7] = 0.0;
    Matrix[8] = 0.0;
    Matrix[9] = 0.0;
    Matrix[10] = (-zfar - znear) / (zfar - znear);
    Matrix[11] = -1.0;
    Matrix[12] = 0.0;
    Matrix[13] = 0.0;
    Matrix[14] = (-2.0f*znear * zfar) /  (zfar - znear);
    Matrix[15] = 0.0;
}

inline void QuatSlerp(const __m128 from, const __m128 to, float frac, __m128 * out)
{
	static double           cosom, absCosom, sinom, sinSqr, omega, scale0, scale1;
	cosom = from.m128_f32[0] * to.m128_f32[0] + from.m128_f32[1] * to.m128_f32[1] + from.m128_f32[2] * to.m128_f32[2] + from.m128_f32[3] * to.m128_f32[3];
	absCosom = fabs(cosom);

	if((1.0 - absCosom) > 1e-6f)
	{
		sinSqr = 1.0 - absCosom * absCosom;
		sinom = 1.0 / sqrt(sinSqr);
		omega = atan2(sinSqr * sinom, absCosom);

		scale0 = sin((1.0f - frac) * omega) * sinom;
		scale1 = sin(frac * omega) * sinom;
	}
	else
	{
		scale0 = 1.0 - frac;
		scale1 = frac;
	}

	scale1 = (cosom >= 0.0) ? scale1 : -scale1;

	out->m128_f32[0] = float(scale0 * from.m128_f32[0] + scale1 * to.m128_f32[0]);
	out->m128_f32[1] = float(scale0 * from.m128_f32[1] + scale1 * to.m128_f32[1]);
	out->m128_f32[2] = float(scale0 * from.m128_f32[2] + scale1 * to.m128_f32[2]);
	out->m128_f32[3] = float(scale0 * from.m128_f32[3] + scale1 * to.m128_f32[3]);
}
inline void CreateTangent(float * VerticesInToTBN ,float * NormalsInToTBN,float * TexCoordsInToTBN,float * TBNout)
{
	__m128 T;
	
	float x1 = VerticesInToTBN[1*3+0] - VerticesInToTBN[0*3+0];
	float x2 = VerticesInToTBN[2*3+0] - VerticesInToTBN[0*3+0];
	float y1 = VerticesInToTBN[1*3+1] - VerticesInToTBN[0*3+1];
	float y2 = VerticesInToTBN[2*3+1] - VerticesInToTBN[0*3+1];
	float z1 = VerticesInToTBN[1*3+2] - VerticesInToTBN[0*3+2];
	float z2 = VerticesInToTBN[2*3+2] - VerticesInToTBN[0*3+2];
        
	float s1 = TexCoordsInToTBN[1*2+0] - TexCoordsInToTBN[0*2+0];
	float s2 = TexCoordsInToTBN[2*2+0] - TexCoordsInToTBN[0*2+0];
	float t1 = TexCoordsInToTBN[1*2+1] - TexCoordsInToTBN[0*2+1];
	float t2 = TexCoordsInToTBN[2*2+1] - TexCoordsInToTBN[0*2+1];
	if(abs(s1 * t2 - s2 * t1)<0.0000001f)
	{
		for(int i=0;i<3;i++)
		{
			TBNout[i*3+0]=1.0f;
			TBNout[i*3+1]=0.0f;
			TBNout[i*3+2]=0.0f;
		}
		return;
	}
	float r = 1.0F / (s1 * t2 - s2 * t1);
	__m128 sdir;
	sdir.m128_f32[0]=(t2 * x1 - t1 * x2) * r;
	sdir.m128_f32[1]=(t2 * y1 - t1 * y2) * r;
	sdir.m128_f32[2]=(t2 * z1 - t1 * z2) * r;
	sdir.m128_f32[3]=0.0f;
	__m128 tdir;
	tdir.m128_f32[0]=(s1 * x2 - s2 * x1) * r;
	tdir.m128_f32[1]=(s1 * y2 - s2 * y1) * r;
	tdir.m128_f32[2]=(s1 * z2 - s2 * z1) * r;
	tdir.m128_f32[3]=0.0f;
	T=sdir;
	Easy_vector_normalize(&T,T);
	__m128 ToutTMP;
	__m128 ONormal;
	for(int i=0;i<3;i++)
	{
		ONormal=_mm_set_ps(0.0f,NormalsInToTBN[i*3+2],NormalsInToTBN[i*3+1],NormalsInToTBN[i*3+0]);
		Easy_vector_normalize(&ONormal,ONormal);
		Easy_vector_scalar_mul(&ToutTMP,ONormal,Easy_vector_dot(T,ONormal));
		Easy_vector_sub(&ToutTMP,T,ToutTMP);
		TBNout[i*3+0]=ToutTMP.m128_f32[0];
		TBNout[i*3+1]=ToutTMP.m128_f32[1];
		TBNout[i*3+2]=ToutTMP.m128_f32[2];
	}
	
	return;
}

inline void Easy_GetAngle(float * Angles, __m128 * Matrix)
{
	__m128 Tmp=Matrix[0];Tmp.m128_f32[2]=0.0f;::Easy_vector_normalize(&Tmp,Tmp);
	Angles[0]=acos( Easy_vector_dot(_mm_set_ps(1.0f,0.0f,0.0f,1.0f),Tmp))*180.0f/3.1415926f;

	Angles[0]=acos( Easy_vector_dot(_mm_set_ps(1.0f,0.0f,0.0f,1.0f),Matrix[0]))*180.0f/3.1415926f;
	Angles[1]=acos( Easy_vector_dot(_mm_set_ps(1.0f,0.0f,1.0f,0.0f),Matrix[1]))*180.0f/3.1415926f;
	Angles[2]=acos( Easy_vector_dot(_mm_set_ps(1.0f,1.0f,0.0f,0.0f),Matrix[2]))*180.0f/3.1415926f;
}
inline void Easy_PosTo(__m128 * MatrixOut ,__m128 TgtDir)
{
	if(Easy_vector_Getlenth_2(TgtDir,_mm_set_ps(1.0f,0.0f,-1.0f,0.0f))<1e-5)
	{
		MatrixOut[0]=_mm_set_ps(0.0f,0.0f,0.0f,1.0f);
		MatrixOut[1]=_mm_set_ps(0.0f,1.0f,0.0f,0.0f);
		MatrixOut[2]=_mm_set_ps(0.0f,0.0f,-1.0f,0.0f);
	//	Easy_vector_cross(&MatrixOut[1],MatrixOut[2],MatrixOut[0]);
	}
	else
	if(Easy_vector_Getlenth_2(TgtDir,_mm_set_ps(1.0f,0.0f,1.0f,0.0f))<1e-5)
	{
		MatrixOut[0]=_mm_set_ps(0.0f,0.0f,0.0f,1.0f);
		MatrixOut[1]=_mm_set_ps(0.0f,-1.0f,0.0f,0.0f);
		MatrixOut[2]=_mm_set_ps(0.0f,0.0f,1.0f,0.0f);
	//	Easy_vector_cross(&MatrixOut[1],MatrixOut[2],MatrixOut[0]);
	/*	MatrixOut[2]=TgtDir;
		MatrixOut[2].m128_f32[0]+=1e-5*3.0f;
		Easy_vector_normalize(&MatrixOut[2],MatrixOut[2]);*/
	}
	else
	{
		MatrixOut[2]=TgtDir;
	
		MatrixOut[2].m128_f32[3]=0.0f;
		Easy_vector_cross(&MatrixOut[0],_mm_set_ps(1.0f,0.0f,1.0f,0.0f),MatrixOut[2]);
		Easy_vector_normalize(&MatrixOut[0],MatrixOut[0]);
		MatrixOut[0].m128_f32[3]=0.0f;
		Easy_vector_cross(&MatrixOut[1],MatrixOut[2],MatrixOut[0]);
		Easy_vector_normalize(&MatrixOut[1],MatrixOut[1]);
		MatrixOut[1].m128_f32[3]=0.0f;
	}
}

#endif
