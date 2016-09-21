#pragma once

#include "DxLib.h"

struct Quaternion{
	float t;
	VECTOR v;
};

//	���f����]�̃N�H�[�^�j�A�I���⏕�֐�
//	DX���C�u�����Ƃ��ɂ��⏕�֐��͂���炵���H
class QuaternionHelper{
private:
public:
	static Quaternion Multi(Quaternion q1, Quaternion q2);	//	�N�H�[�^�j�I�����m�̊|���Z
	static float Inner(VECTOR q1, VECTOR q2);				//	����
	static VECTOR Outer(VECTOR v1, VECTOR v2);				//	�O��
	static VECTOR Plus(VECTOR v1, VECTOR v2);				//	�����Z
	static VECTOR Minus(VECTOR v1, VECTOR v2);				//	�����Z
	static VECTOR Multi(float f, VECTOR v);					//	�|���Z
	static Quaternion Rotation(float t, VECTOR v);			//	��]
	static Quaternion Normalization(VECTOR v);				//	���K���i�����Ă邩�s���j
};