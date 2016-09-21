#pragma once

#include <windows.h>
#include "BGM.h"

enum COMMAND_MESSAGE{
	CME_NONE,
	CME_ANIMATION,
	CME_FOCUS
};

//	����p�l���N���X
class CommandPanel{
private:
	MSG msg;				//	�X���b�h����̃��b�Z�[�W���
	char szTitle[64];		//	�E�B���h�E�^�C�g��
	char szWindowClass[64];	//	�E�B���h�E�N���X
	HINSTANCE GethInstance;	//	�C���X�^���X
	int GetnCmdShow;		//	�E�B���h�E�\�����

	static BGM bgm;			//	BGM�Ǘ�

	static int light;		//	���f���ɓ�������̗�
	static int volume;		//	����
	static int anim;		//	�A�j���[�V�����ԍ�
	static int focus;		//	�t�H�[�J�X��
	static char bgmname[256];	//	BGM�̃p�X

	static int animation_amount[8];	//	�A�j���[�V�����̗ʕۑ��i�z��Ȃ͕̂������f���Ή��̂��߁j

	static COMMAND_MESSAGE message;	//	���b�Z�[�W
	static int param;		//	�p�����[�^�ۑ�

	ATOM MyRegisterClass( HINSTANCE hInstance );	// �N���X�o�^
	BOOL InitInstance( HINSTANCE, int );			// �C���X�^���X�쐬
	static LRESULT CALLBACK CommandPanel::WndProc(HWND hWnd, UINT uint_message, WPARAM wParam, LPARAM lParam);	//	�E�B���h�E�v���V�[�W��
public:
	void Initialize( HINSTANCE hInstance, int nCmdShow );	//	�N���X������
	bool Update();									//	���t���[���Ă΂��
	void Open();									//	����p�l�����J�����ɌĂ΂��
	void AnimResist(int person_number, int amount);	//	�A�j���[�V������o�^����i��2�F���f���ԍ��A��2�F���[�V������
	COMMAND_MESSAGE Message();						//	���b�Z�[�W�𑗂�i���C���֐��ł���ė~�������F��ɑ��N���X�̑���j
	int GetParam();									//	�p�����[�^�𑗂�i���b�Z�[�W�ɉ������l��K�v�Ƃ���ꍇ�Ɏg�p�j
};