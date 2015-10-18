#ifndef _EASYQUAT_H
#define _EASYQUAT_H
#include "Def.h"	
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>
#include "EasyVector.h"
struct _QuatFloat4{
	float x;
	float y;
	float z;
	float w;
};
struct _QuatColor4{
	float R;
	float G;
	float B;
	float A;
};
struct _QuatPos3{
	_Vec3 P;
	float w;
};
typedef union  _Quat {
     float               f[4];
     _QuatFloat4		 Q;
	 _QuatColor4		 C;
	 _QuatPos3			 P;
}_Quat,_Float4,_Vec4;
inline void Easy_quat_axis_angle(float c[4], float axis[3], float angle) 
{
    double omega, s;
    double l;

    l = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
    if (l < 1e-5) {
        c[0] = c[1] = c[2] = 0.0f;
        c[3] = 1.0f;
    } else {
        omega = -0.5 * angle;
        s = sin(omega) / l;
        c[0] = (float)s * axis[0];
        c[1] = (float)s * axis[1];
        c[2] = (float)s * axis[2];
        c[3] = (float)cos(omega);
    }
}
inline void Easy_quat_axis_angle(double c[4], double axis[3], double angle) 
{
    double omega, s;
    double l;

    l = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
    if (l < 1e-5) {
        c[0] = c[1] = c[2] = 0.0f;
        c[3] = 1.0f;
    } else {
        omega = -0.5 * angle;
        s = sin(omega) / l;
        c[0] = s * axis[0];
        c[1] = s * axis[1];
        c[2] = s * axis[2];
        c[3] = cos(omega);
    }
}
inline void Easy_quat_axis_angle(__m128 * c, float axisX, float axisY, float axisZ, float angle) 
{
	double omega, s;
    double l;

    l = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
    if (l < 1e-5) {
        c[0] =_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
    } else {
        omega = -0.5 * angle;
        s = sin(omega) / l;
        c->m128_f32[0] = (float)s * axisX;
        c->m128_f32[1] = (float)s * axisY;
        c->m128_f32[2] = (float)s * axisZ;
        c->m128_f32[3] = (float)cos(omega);
    }
}
inline void Easy_quat_axis_angle(__m128 * c, const __m128 axis_angle) 
{
    double omega, s;
    double l;

	l = sqrt(axis_angle.m128_f32[0] * axis_angle.m128_f32[0] + axis_angle.m128_f32[1] * axis_angle.m128_f32[1] + axis_angle.m128_f32[2] * axis_angle.m128_f32[2]);
    if (l < 1e-5) {
		c->m128_f32[0] = c->m128_f32[1] = c->m128_f32[2] = 0.0f;
        c->m128_f32[3] = 1.0f;
    } else {
        omega = -0.5 * axis_angle.m128_f32[3];
        s = sin(omega) / l;
        c->m128_f32[0] = (float)s * axis_angle.m128_f32[0];
        c->m128_f32[1] = (float)s * axis_angle.m128_f32[1];
        c->m128_f32[2] = (float)s * axis_angle.m128_f32[2];
        c->m128_f32[3] = (float)cos(omega);
    }
}
inline void Easy_quat_normalize(float c[4]) {
    double l, m;

    l = sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2] + c[3] * c[3]);
    if (fabs(l) < LIB3DS_EPSILON) {
        c[0] = c[1] = c[2] = 0.0f;
        c[3] = 1.0f;
    } else {
        int i;
        m = 1.0f / l;
        for (i = 0; i < 4; ++i) {
            c[i] = (float)(c[i] * m);
        }
    }
}
inline void Easy_quat_normalize(double c[4]) {
    double l, m;

    l = sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2] + c[3] * c[3]);
    if (fabs(l) < LIB3DS_EPSILON) {
        c[0] = c[1] = c[2] = 0.0f;
        c[3] = 1.0f;
    } else {
        int i;
        m = 1.0f / l;
        for (i = 0; i < 4; ++i) {
            c[i] = (c[i] * m);
        }
    }
}
inline void Easy_quat_normalize(__m128 * QuatOut,const __m128 QuatIn)
{
	_asm   
	{    
	movaps   xmm1,   QuatIn
	movaps   xmm0,   xmm1   
	mulps	 xmm1,   xmm1   
    
	  
	movaps   xmm2,   xmm1   
	movaps   xmm3,   xmm1   
	movaps   xmm4,   xmm1   

	shufps   xmm1,   xmm1,   0x00 
	shufps   xmm2,   xmm2,   0x55   
	shufps   xmm3,   xmm3,   0xaa   
	shufps   xmm4,   xmm4,   0xff  

	addps	 xmm1,   xmm2   
	addps    xmm1,   xmm3  
	addps    xmm1,   xmm4
    
	sqrtps   xmm1,   xmm1   
	divps    xmm0,   xmm1   

	mov		 ecx,    QuatOut
	movups	 [ecx],  xmm0  
  } 
}
/*
#define assert_16_byte_aligned( pointer ) assert( (((UINT_PTR)(pointer))&15) == 0 ); 
 */
#define ALIGN16( x ) __declspec(align(16)) x 

#define ALIGN4_INIT1( X, I ) ALIGN16( static X[4] = { I, I, I, I } ) 
#define ALIGN4_INIT4( X, I0,I1,I2,I3 ) ALIGN16( static X[4] = { I0,I1,I2,I3 } ) 
#define R_SHUFFLE_PS( x, y, z, w ) (( (w) & 3 ) << 6 | ( (z) & 3 ) << 4 | ( (y) & 3 ) << 2 | ( (x) & 3 )) 
#define R_SHUFFLE_D R_SHUFFLE_PS


#define IEEE_SP_ZERO 0 

#define IEEE_SP_SIGN ((unsigned long) ( 1 << 31 )) 

 

//ALIGN4_INIT4( unsigned long SIMD_SP_quat2mat_x0, IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN ); 

//ALIGN4_INIT4( unsigned long SIMD_SP_quat2mat_x1, IEEE_SP_SIGN, IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN ); 

//ALIGN4_INIT4( unsigned long SIMD_SP_quat2mat_x2, IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN ); 
//static const __m128 SIMD_SP_quat2mat_x0={IEEE_SP_ZERO,IEEE_SP_SIGN,IEEE_SP_SIGN,IEEE_SP_SIGN};
//static const __m128 SIMD_SP_quat2mat_x1={IEEE_SP_SIGN,IEEE_SP_ZERO,IEEE_SP_SIGN,IEEE_SP_SIGN};
//static const __m128 SIMD_SP_quat2mat_x2={IEEE_SP_ZERO,IEEE_SP_SIGN,IEEE_SP_SIGN,IEEE_SP_SIGN};
__declspec(align(16)) static const unsigned long SIMD_SP_quat2mat_x0[4] ={IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN};
__declspec(align(16)) static const unsigned long SIMD_SP_quat2mat_x1[4] ={IEEE_SP_SIGN, IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN};
__declspec(align(16)) static const unsigned long SIMD_SP_quat2mat_x2[4] ={IEEE_SP_ZERO, IEEE_SP_SIGN, IEEE_SP_SIGN, IEEE_SP_SIGN};
static const __m128 SIMD_SP_one = _mm_set_ps(0.0f,0.0f,0.0f,1.0f);
static const __m128 SIMD_SP_one1 = _mm_set_ps(1.0f,1.0f,1.0f,1.0f);
static const __m128 SIMD_SP_one3 = _mm_set_ps(1.0f,0.0f,0.0f,0.0f);
static const __m128 SSE_ONE = _mm_set_ps(1.0f,1.0f,1.0f,1.0f);
inline void Easy_quat_to_matrix(__m128 MatrixOut[4],const __m128 QuatIn)
{
	_asm   
	{
	//	PUSHAD
			mov eax,MatrixOut
			movaps xmm0,QuatIn
			movaps xmm6,SIMD_SP_one3

			movaps xmm1, xmm0 // xmm1 = x, y, z, w 
			addps xmm1, xmm1 // xmm1 = x2, y2, z2, w2 

			pshufd xmm2, xmm0, R_SHUFFLE_D( 1, 0, 0, 1 ) // xmm2 = y, x, x, y 
			pshufd xmm3, xmm1, R_SHUFFLE_D( 1, 1, 2, 2 ) // xmm3 = y2, y2, z2, z2 
			mulps xmm2, xmm3 // xmm2 = yy2, xy2, xz2, yz2 

			pshufd xmm4, xmm0, R_SHUFFLE_D( 2, 3, 3, 3 ) // xmm4 = z, w, w, w 
			pshufd xmm5, xmm1, R_SHUFFLE_D( 2, 2, 1, 0 ) // xmm5 = z2, z2, y2, x2 
			mulps xmm4, xmm5 // xmm4 = zz2, wz2, wy2, wx2 

			mulss xmm0, xmm1 // xmm0 = xx2, y2, z2, w2 

			
 // calculate the last two elements of the third row 

			movss xmm7, SIMD_SP_one1 // xmm7 = 1, 0, 0, 0 
			subss xmm7, xmm0 // xmm7 = -xx2+1, 0, 0, 0 
			subss xmm7, xmm2 // xmm7 = -xx2-yy2+1, 0, 0, 0 
			shufps xmm7, xmm6, R_SHUFFLE_PS( 0, 1, 2, 3 ) // xmm7 = -xx2-yy2+1, 0, t.z, t.w 

 // calcluate first row 

			xorps xmm2, SIMD_SP_quat2mat_x0 // xmm2 = yy2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x1 // xmm4 = -zz2, wz2, -wy2, -wx2 
			addss xmm4, SIMD_SP_one1 // xmm4 = -zz2+1, wz2, -wy2, -wx2 
			movaps xmm3, xmm4 // xmm3 = -zz2+1, wz2, -wy2, -wx2 
			subps xmm3, xmm2 // xmm3 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movaps [eax+0*16+0*4], xmm3 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movss [eax+0*16+3*4], xmm6 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, t.x 

 // calculate second row 

			movss xmm2, xmm0 // xmm2 = xx2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x2 // xmm4 = -zz2+1, -wz2, wy2, wx2 
			subps xmm4, xmm2 // xmm4 = -xx2-zz2+1, xy2-wz2, xz2+wy2, yz2+wx2 
			shufps xmm6, xmm6, R_SHUFFLE_PS( 1, 2, 3, 0 ) // xmm6 = t.y, t.z, t.w, t.x 
			shufps xmm4, xmm4, R_SHUFFLE_PS( 1, 0, 3, 2 ) // xmm4 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movaps [eax+1*16+0*4], xmm4 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movss [eax+1*16+3*4], xmm6 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, t.y 

 // calculate third row 

			movhlps xmm3, xmm4 // xmm3 = yz2+wx2, xz2+wy2, xz2-wy2, yz2-wx2 
			shufps xmm3, xmm7, R_SHUFFLE_PS( 1, 3, 0, 2 ) // xmm3 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps [eax+2*16+0*4], xmm3 // row2 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps xmm6,SIMD_SP_one3
			movaps [eax+3*16+0*4], xmm6

	//	POPAD
	}
}
inline void QuatFromMatrix(float q[4], const float m[16])
{
	float           t, s;

	if(m[0] + m[5] + m[10] > 0.0f)
	{
		t = m[0] + m[5] + m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[3] = s * t;
		q[2] = (m[1] - m[4]) * s;
		q[1] = (m[8] - m[2]) * s;
		q[0] = (m[6] - m[9]) * s;
	}
	else if(m[0] > m[5] && m[0] > m[10])
	{
		t = m[0] - m[5] - m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[0] = s * t;
		q[1] = (m[1] + m[4]) * s;
		q[2] = (m[8] + m[2]) * s;
		q[3] = (m[6] - m[9]) * s;
	}
	else if(m[5] > m[10])
	{
		t = -m[0] + m[5] - m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[1] = s * t;
		q[0] = (m[1] + m[4]) * s;
		q[3] = (m[8] - m[2]) * s;
		q[2] = (m[6] + m[9]) * s;
	}
	else
	{
		t = -m[0] - m[5] + m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[2] = s * t;
		q[3] = (m[1] - m[4]) * s;
		q[0] = (m[8] + m[2]) * s;
		q[1] = (m[6] + m[9]) * s;
	}


}
inline void QuatFromMatrix(double q[4], const double m[16])
{
	double           t, s;

	if(m[0] + m[5] + m[10] > 0.0f)
	{
		t = m[0] + m[5] + m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[3] = s * t;
		q[2] = (m[1] - m[4]) * s;
		q[1] = (m[8] - m[2]) * s;
		q[0] = (m[6] - m[9]) * s;
	}
	else if(m[0] > m[5] && m[0] > m[10])
	{
		t = m[0] - m[5] - m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[0] = s * t;
		q[1] = (m[1] + m[4]) * s;
		q[2] = (m[8] + m[2]) * s;
		q[3] = (m[6] - m[9]) * s;
	}
	else if(m[5] > m[10])
	{
		t = -m[0] + m[5] - m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[1] = s * t;
		q[0] = (m[1] + m[4]) * s;
		q[3] = (m[8] - m[2]) * s;
		q[2] = (m[6] + m[9]) * s;
	}
	else
	{
		t = -m[0] - m[5] + m[10] + 1.0f;
		s = 0.5f / sqrt(t);

		q[2] = s * t;
		q[3] = (m[1] - m[4]) * s;
		q[0] = (m[8] + m[2]) * s;
		q[1] = (m[6] + m[9]) * s;
	}


}
inline void Easy_matrix_to_quat(__m128 * QuatOut,__m128 MatrixIn[4])
{
	/*QuatOut->m128_f32[3]=sqrt(max(0.0000001f,1+MatrixIn[0].m128_f32[0]+MatrixIn[1].m128_f32[1]+MatrixIn[2].m128_f32[2]))/2.0f;
	QuatOut->m128_f32[0]=(MatrixIn[2].m128_f32[1]-MatrixIn[1].m128_f32[2])/(4*QuatOut->m128_f32[3]);
	QuatOut->m128_f32[1]=(MatrixIn[0].m128_f32[2]-MatrixIn[2].m128_f32[0])/(4*QuatOut->m128_f32[3]);
	QuatOut->m128_f32[2]=(MatrixIn[1].m128_f32[0]-MatrixIn[0].m128_f32[1])/(4*QuatOut->m128_f32[3]);*/

	QuatFromMatrix(QuatOut->m128_f32,&(MatrixIn[0].m128_f32[0]));
}
inline void Easy_Joint_to_matrix(__m128 MatrixOut[4],const __m128 QuatIn,const __m128 PosIn)
{
	_asm   
	{
	//	PUSHAD
			mov eax,MatrixOut
			movaps xmm0,QuatIn
			movaps xmm6,PosIn

			movaps xmm1, xmm0 // xmm1 = x, y, z, w 
			addps xmm1, xmm1 // xmm1 = x2, y2, z2, w2 

			pshufd xmm2, xmm0, R_SHUFFLE_D( 1, 0, 0, 1 ) // xmm2 = y, x, x, y 
			pshufd xmm3, xmm1, R_SHUFFLE_D( 1, 1, 2, 2 ) // xmm3 = y2, y2, z2, z2 
			mulps xmm2, xmm3 // xmm2 = yy2, xy2, xz2, yz2 

			pshufd xmm4, xmm0, R_SHUFFLE_D( 2, 3, 3, 3 ) // xmm4 = z, w, w, w 
			pshufd xmm5, xmm1, R_SHUFFLE_D( 2, 2, 1, 0 ) // xmm5 = z2, z2, y2, x2 
			mulps xmm4, xmm5 // xmm4 = zz2, wz2, wy2, wx2 

			mulss xmm0, xmm1 // xmm0 = xx2, y2, z2, w2 

			
 // calculate the last two elements of the third row 

			movss xmm7, SIMD_SP_one1 // xmm7 = 1, 0, 0, 0 
			subss xmm7, xmm0 // xmm7 = -xx2+1, 0, 0, 0 
			subss xmm7, xmm2 // xmm7 = -xx2-yy2+1, 0, 0, 0 
			shufps xmm7, xmm6, R_SHUFFLE_PS( 0, 1, 2, 3 ) // xmm7 = -xx2-yy2+1, 0, t.z, t.w 

 // calcluate first row 

			xorps xmm2, SIMD_SP_quat2mat_x0 // xmm2 = yy2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x1 // xmm4 = -zz2, wz2, -wy2, -wx2 
			addss xmm4, SIMD_SP_one1 // xmm4 = -zz2+1, wz2, -wy2, -wx2 
			movaps xmm3, xmm4 // xmm3 = -zz2+1, wz2, -wy2, -wx2 
			subps xmm3, xmm2 // xmm3 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movaps [eax+0*16+0*4], xmm3 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movss [eax+0*16+3*4], xmm6 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, t.x 

 // calculate second row 

			movss xmm2, xmm0 // xmm2 = xx2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x2 // xmm4 = -zz2+1, -wz2, wy2, wx2 
			subps xmm4, xmm2 // xmm4 = -xx2-zz2+1, xy2-wz2, xz2+wy2, yz2+wx2 
			shufps xmm6, xmm6, R_SHUFFLE_PS( 1, 2, 3, 0 ) // xmm6 = t.y, t.z, t.w, t.x 
			shufps xmm4, xmm4, R_SHUFFLE_PS( 1, 0, 3, 2 ) // xmm4 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movaps [eax+1*16+0*4], xmm4 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movss [eax+1*16+3*4], xmm6 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, t.y 

 // calculate third row 

			movhlps xmm3, xmm4 // xmm3 = yz2+wx2, xz2+wy2, xz2-wy2, yz2-wx2 
			shufps xmm3, xmm7, R_SHUFFLE_PS( 1, 3, 0, 2 ) // xmm3 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps [eax+2*16+0*4], xmm3 // row2 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps xmm6,SIMD_SP_one3
			movaps [eax+3*16+0*4], xmm6

	//	POPAD
	}
}

inline void Easy_Joint_to_matrix(__m128 * MatrixOut,const __m128 * JointIn,const int JointNumIn)
{
	_asm   
	{
	//	PUSHAD
			mov eax,MatrixOut
			mov ebx,JointIn
			mov ecx,JointNumIn

sse_Loop:
			movaps xmm0,[ebx]
			movaps xmm6,[ebx+16]

			movaps xmm1, xmm0 // xmm1 = x, y, z, w 
			addps xmm1, xmm1 // xmm1 = x2, y2, z2, w2 

			pshufd xmm2, xmm0, R_SHUFFLE_D( 1, 0, 0, 1 ) // xmm2 = y, x, x, y 
			pshufd xmm3, xmm1, R_SHUFFLE_D( 1, 1, 2, 2 ) // xmm3 = y2, y2, z2, z2 
			mulps xmm2, xmm3 // xmm2 = yy2, xy2, xz2, yz2 

			pshufd xmm4, xmm0, R_SHUFFLE_D( 2, 3, 3, 3 ) // xmm4 = z, w, w, w 
			pshufd xmm5, xmm1, R_SHUFFLE_D( 2, 2, 1, 0 ) // xmm5 = z2, z2, y2, x2 
			mulps xmm4, xmm5 // xmm4 = zz2, wz2, wy2, wx2 

			mulss xmm0, xmm1 // xmm0 = xx2, y2, z2, w2 

			
 // calculate the last two elements of the third row 

			movss xmm7, SIMD_SP_one1 // xmm7 = 1, 0, 0, 0 
			subss xmm7, xmm0 // xmm7 = -xx2+1, 0, 0, 0 
			subss xmm7, xmm2 // xmm7 = -xx2-yy2+1, 0, 0, 0 
			shufps xmm7, xmm6, R_SHUFFLE_PS( 0, 1, 2, 3 ) // xmm7 = -xx2-yy2+1, 0, t.z, t.w 

 // calcluate first row 

			xorps xmm2, SIMD_SP_quat2mat_x0 // xmm2 = yy2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x1 // xmm4 = -zz2, wz2, -wy2, -wx2 
			addss xmm4, SIMD_SP_one1 // xmm4 = -zz2+1, wz2, -wy2, -wx2 
			movaps xmm3, xmm4 // xmm3 = -zz2+1, wz2, -wy2, -wx2 
			subps xmm3, xmm2 // xmm3 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movaps [eax+0*16+0*4], xmm3 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2 
			movss [eax+0*16+3*4], xmm6 // row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, t.x 

 // calculate second row 

			movss xmm2, xmm0 // xmm2 = xx2, -xy2, -xz2, -yz2 
			xorps xmm4, SIMD_SP_quat2mat_x2 // xmm4 = -zz2+1, -wz2, wy2, wx2 
			subps xmm4, xmm2 // xmm4 = -xx2-zz2+1, xy2-wz2, xz2+wy2, yz2+wx2 
			shufps xmm6, xmm6, R_SHUFFLE_PS( 1, 2, 3, 0 ) // xmm6 = t.y, t.z, t.w, t.x 
			shufps xmm4, xmm4, R_SHUFFLE_PS( 1, 0, 3, 2 ) // xmm4 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movaps [eax+1*16+0*4], xmm4 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2 
			movss [eax+1*16+3*4], xmm6 // row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, t.y 

 // calculate third row 

			movhlps xmm3, xmm4 // xmm3 = yz2+wx2, xz2+wy2, xz2-wy2, yz2-wx2 
			shufps xmm3, xmm7, R_SHUFFLE_PS( 1, 3, 0, 2 ) // xmm3 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps [eax+2*16+0*4], xmm3 // row2 = xz2+wy2, yz2-wx2, -xx2-yy2+1, t.z 
			movaps xmm6,SIMD_SP_one3
			movaps [eax+3*16+0*4], xmm6
			add eax,64
			add ebx,32
			dec ecx
			jnz sse_Loop
	//	POPAD
	}
}
//QuatOut=QuatIn1*Weight+QuatIn2*(1-Weight);
inline void Easy_quat_Mix(__m128 * QuatOut,const __m128 QuatIn1,const __m128 QuatIn2,const float Weight)
{
	_asm   
	{
		movaps xmm1 , SSE_ONE
		movaps xmm2 , QuatIn1
		movaps xmm3 , QuatIn2
		mov eax ,Weight
		mov ecx ,QuatOut
		mov [ecx],eax
		mov [ecx+4],eax
		mov [ecx+8],eax
		mov [ecx+12],eax
		movaps xmm0 , [ecx]
		subps  xmm1 , xmm0
		mulps  xmm0 , xmm2
		mulps  xmm1 , xmm3
		addps  xmm0 , xmm1
		movaps [ecx] , xmm0
	}
}
#define vec4f_swizzleM(p,q,r,s) ((s)<<6|(r)<<4|(q)<<2|(p))
#define swiz1m vec4f_swizzleM(3,3,3,3)
#define swiz2m vec4f_swizzleM(2,0,1,0)
#define swiz3m vec4f_swizzleM(1,2,0,0)
#define swiz4m vec4f_swizzleM(3,3,3,1)
#define swiz5m vec4f_swizzleM(0,1,2,1)
#define swiz6m vec4f_swizzleM(1,2,0,2)
#define swiz7m vec4f_swizzleM(2,0,1,2)
static const int zero=0;
static const int flipSign=0x80000000;
static const __m128 quat_mask=_mm_setr_ps( *(float*)&zero,
*(float*)&zero,
*(float*)&zero,
*(float*)&flipSign);
inline void Easy_quat_Mult(__m128 * QuatOut,const __m128 QuatIn1,const __m128 QuatIn2)
{
	_asm   
	{
		movaps xmm6,QuatIn1
		movaps xmm7,QuatIn2

		movaps xmm4,xmm6
		movaps xmm0,xmm7
		shufps xmm0,xmm0,swiz1m
		mulps  xmm4,xmm0//__m128 mul1=_mm_mul_ps(a,swiz1);
		movaps xmm5,xmm6
		movaps xmm0,xmm7
		shufps xmm5,xmm5,swiz2m
		shufps xmm0,xmm0,swiz3m
		mulps  xmm5,xmm0//__m128 mul2=_mm_mul_ps(swiz2,swiz3);
		subps  xmm4,xmm5//__m128 retVal=_mm_sub_ps(mul1,mul2);

		movaps xmm5,xmm6
		movaps xmm0,xmm7
		shufps xmm5,xmm5,swiz6m
		shufps xmm0,xmm0,swiz7m
		mulps  xmm5,xmm0//__m128 mul4=_mm_mul_ps(swiz6,swiz7);
		shufps xmm6,xmm6,swiz4m
		shufps xmm7,xmm7,swiz5m
		mulps  xmm6,xmm7//__m128 mul3=_mm_mul_ps(swiz4,swiz5);
		xorps  xmm5,quat_mask//__m128 flip1=_mm_xor_ps(mul4,quat_mask);
		xorps  xmm6,quat_mask//__m128 flip2=_mm_xor_ps(mul3,quat_mask);
		addps  xmm5,xmm6//__m128 retVal2=_mm_add_ps(flip1,flip2);

		addps  xmm4,xmm5
		mov eax,QuatOut
		movaps [eax] , xmm4
	}
}
#define vec4f_swizzle(v,p,q,r,s) (_mm_shuffle_ps( (v),(v), ((s)<<6|(r)<<4|(q)<<2|(p))))
inline void  quat_mul(__m128 * QuatOut,__m128 a, __m128 b)
{
	__m128 swiz1=vec4f_swizzle(b,3,3,3,3);
	__m128 swiz2=vec4f_swizzle(a,2,0,1,0);
	__m128 swiz3=vec4f_swizzle(b,1,2,0,0);
	__m128 swiz4=vec4f_swizzle(a,3,3,3,1);
	__m128 swiz5=vec4f_swizzle(b,0,1,2,1);
	__m128 swiz6=vec4f_swizzle(a,1,2,0,2);
	__m128 swiz7=vec4f_swizzle(b,2,0,1,2);
	__m128 mul4=_mm_mul_ps(swiz6,swiz7);
	__m128 mul3=_mm_mul_ps(swiz4,swiz5);
	__m128 mul2=_mm_mul_ps(swiz2,swiz3);
	__m128 mul1=_mm_mul_ps(a,swiz1);
	__m128 flip1=_mm_xor_ps(mul4,quat_mask);
	__m128 flip2=_mm_xor_ps(mul3,quat_mask);
	__m128 retVal=_mm_sub_ps(mul1,mul2);
	__m128 retVal2=_mm_add_ps(flip1,flip2);
	QuatOut[0]= _mm_add_ps(retVal,retVal2);
}
#endif