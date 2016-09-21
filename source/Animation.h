#pragma once

#include "DxLib.h"

// �A�j���[�V�������X�g
struct AnimBox{
	char name[64];
	float time;
};

//	���f���̃A�j���[�V�����N���X
class Animation{
private:
	AnimBox list[64];
	int amount;			// �A�j���[�V�����̐�
	int index;			// ���ݍĐ����Ă���A�j���[�V�����ԍ�
	int index_old;		// �O��Đ����Ă����A�j���[�V�����ԍ�
	int Handle[64];		// �A�^�b�`�n���h���A�u�����h���̑���Ɏg�p
	float Time;			// �A�j���[�V�����̍Đ�����
	LONGLONG PrevTime;	// �O��̌����̎���
	LONGLONG NowTime;	// ����̌����̎���
	float blending;		// �u�����h��
public:
	void Initialize(int modelhandle);	// �\�t�g�N�����ɌĂ΂��
	void Finalize(int modelhandle);		// �\�t�g�I�����ɌĂ΂��
	void Update(int modelhandle);		// ���t���[���̍X�V
	void Draw();						// �`�揈��
	void Play(int num, int modelhandle);// �w�肵���ԍ��̃A�j���[�V�������Đ�����
	void PlayNext();					// ���̔ԍ��̃A�j���[�V�������Đ�����
	void PlayPrev();					// �O�̔ԍ��̃A�j���[�V�������Đ�����
	void TimeReset();					// �Đ����Ԃ�����������
	int GetAmount();					// �A�j���[�V�����̑�����Ԃ�
};