#pragma once

#include "DxLib.h"
#include "Animation.h"

//	���f���Ǘ��N���X
class Model{
private:
    char FileName[256];		// ���f���t�@�C���̃p�X
    int ModelHandle;		// ���f���̃n���h��
	int FrameNum;			// ���f���t���[����
	int MeshNum;			// ���f�����b�V����
	bool drawframe;			// �t���[���̕`��I���I�t
	bool drawwireframe;		// ���C���[�t���[���̕`��I���I�t
	// �����蔻��\����
	struct{
		char name[64];		// �����蔻�薼��
		int number;			// ����ԍ�
		VECTOR point;		// �ʒu�i3D���W�j
		int size;			// �傫���i�f�B�X�v���C�T�C�Y�j
	}hit[256];
	VECTOR ScreenHitPoint[256];		// �X�N���[���㓖���蔻��ʒu�iZ���W�͎g��Ȃ��j
	VECTOR ScreenFramePoint[256];	// �X�N���[����t���[���ʒu
	Animation animation;			// �A�j���[�V����
	void LoadModel();				// ���f���̓ǂݍ���
	void UpdateFP();				// ScreenHitPoint,ScreenFramePoint�̍X�V
	void DrawPolyModel();
	void DrawFrameModel();
	void DrawNamingFrameModel();
	void DrawFrameCrossModel();
public:
	void Initialize();		// �\�t�g�J�n���ɌĂ΂��
	void Finalize();		// �\�t�g�I�����ɌĂ΂��
	void Update();			// ���t���[���̍X�V
	void Draw();			// �`�揈��
	int GetHandle();		// ���f���n���h���̎擾
	int LoadNewModel(const char* fileFilter);		// �V�������f����ǂ݂���
	int GetAnimAmount();	// �A�j���[�V�����̐����擾
	void Play(int num);					// �w�肵���ԍ��̃A�j���[�V�������Đ�����
};