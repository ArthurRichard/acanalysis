#pragma once
#include "EasyMatrix.h"
class NodeMath
{
public:
	NodeMath(void);
	~NodeMath(void);
	__m128 * Mat;
	__m128 * Quat;
	__m128 * Pos;
	void Move(float x, float y, float z);
	void Turn(float a, float x, float y, float z);
	void Inv(void);
	void Clear(void);
};

