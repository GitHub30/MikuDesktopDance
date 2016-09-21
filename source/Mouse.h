#pragma once

#include "DxLib.h"

// �}�E�X�p�N���X
// ��Ɉʒu�A�h���b�O���ԁA�������^�C�~���O���Ď����Ă���
class Mouse{
private:
	static int left;			// ���{�^������
	static int right;			// �E�{�^������
	static int wheel;			// �z�C�[����]��
	static bool lefttouch;		// ���{�^���𗣂����u��
	static bool righttouch;		// �E�{�^���𗣂����u��
public:
	Mouse();
	void Update();				// ���t���[���Ăяo�����
	static void Reset();		// �L�^�����Z�b�g����
	void Draw();				// �`��
	static bool Touch(int n);	// �w�肵���{�^���������ꂽ�u�Ԃ���Ԃ�
	static bool Out(int n);		// �w�肵���{�^���������ꂽ�u�Ԃ���Ԃ�
	static int Hold(int n);		// �w�肵���{�^���̉����Ă��鎞�Ԃ�Ԃ�
	static int Wheel();			// �z�C�[����]�ʂ�Ԃ�
	static VECTOR GetPos2D();	// �X�N���[���ʒu��VECTOR�ŕԂ�
	static VECTOR GetPos3D();	// 3D���W��VECTOR�ŕԂ�
};