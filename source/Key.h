#pragma once

// �L�[�̓��͊֘A���܂Ƃ߂�N���X
// DX���C�u�����̃L�[�擾�@�\�����ł͉����Ă��鎞�Ԃ����Ȃ�
// �L�[�̎g�p���������鎞�ɂ܂Ƃ߂ď����ł���

class Key{
private:
	static int key[256];				// �L�[�̉����Ă��鎞�ԋL�^
	static bool lasttouch[256];			// �L�[�𗣂����u�Ԃ�
public:
	Key();
	void Update();							// ���t���[���̍X�V
	static void Reset();							// �J�E���g�̃��Z�b�g
	void Draw();							// �`��
	static bool Touch(int n);				// �������u�Ԃ��ǂ���
	static bool Out(int n);					// �������u�Ԃ��ǂ���
	static int Hold(int n);					// �ǂꂮ�炢�����Ă��邩
};