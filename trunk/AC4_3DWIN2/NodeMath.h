#pragma once
__declspec(align(16)) union _NodeMatrix4f
{
	float F[16];
	float F4X4[4][4];
};
__declspec(align(16)) union _NodeQuat
{
	float Q[4];
};
class NodeMath
{
public:
	NodeMath(void);
	~NodeMath(void);
	_NodeMatrix4f * Mat;
	_NodeQuat * Quat;
	_NodeQuat * Pos;
	void Move(float x, float y, float z);
	void Turn(float a, float x, float y, float z);
	void Inv(void);
	void Clear(void);
};

