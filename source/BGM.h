#pragma once

//	BGM�Ǘ��N���X
class BGM{
private:
    static char FileName[256];	// BGM�̃t�@�C���܂ł̃p�X
	static int Handle;			// BGM�̃n���h��
	long CalcDB( int sound_val );		// ���ʒ����p�̊֐�
public:
	BGM();						// �R���X�g���N�^
	int Load();					// ���y�t�@�C���̓ǂݍ���
	void Start(int vol);		// ���y�̍Đ�
	void Stop();				// ���y�̒�~
	void Volume(int vol);		// ���ʂ̕ύX
};