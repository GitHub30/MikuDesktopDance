#pragma once

#include "DxLib.h"

//	�J�����Ǘ��N���X
//	�i���f���\���ʒu�̊Ǘ����s���j
class Camera{
private:
	static VECTOR Pos;				// �J�������W
	static VECTOR Target;			// �J���������_
	static VECTOR Move;				// �J�����̈ړ�����
	static float vnear,vfar;		// ��O�E���N���b�v����
	static float ortho;				// �\���͈�
	float distance;					// �J�����ƑΏۂƂ̋���
	bool moving;					// �J�����ړ�
	int moving_x, moving_y;			// �O��̃}�E�X�ʒu�i�ړ��p�j
	bool rotate;					// ���f����]�i�J�����̈ʒu�ύX�j
	bool rotate_xp, rotate_xm;		// ��]��x���v���X�����E�}�C�i�X����
	bool rotate_yp, rotate_ym;		// ��]��y���v���X�����E�}�C�i�X����
	int rotate_count;				// ��]�̃J�E���g
	int rotate_count_max;			// ��]�̏I���J�E���g
	int rotate_amount;				// ��]��
	bool viewdatas;					// �J�������\���̉�
	void Rotate_Start(bool &dir);		// ��]�J�n ������rotate_xp���ŕ����w��
	void Rotate_Update();				// ��]�̍X�V
	void SetCameraPosition();			// �e�ϐ��ɂ��J�����ʒu�X�V
public:
	void Initialize();					// �\�t�g�N�����ɌĂ΂��
	void Init_Pos();					// ���[�v�J�n���O�ɌĂ΂��i�Ȃ���Initialize���ƃ��[�v���ŃE�B���h�E�T�C�Y�擾�l���ς�邽�߁j
	void Finalize();					// �\�t�g�I�����ɌĂ΂��
	void Update();						// ���t���[���̍X�V
	void Draw();						// �`�揈��
	static VECTOR CameraPos();			// �J�����̍��W�𓾂�
	void ResetPos();					// �J�����̍��W��������
	void ResetMove();					// �J�����̈ړ�����������
	bool ChengeViewDatas();				// �J�������\���̐؂�ւ�
	void ChengeFocus(int num);					// �J�����t�H�[�J�X�ݒ�i����p�l���p�j
};