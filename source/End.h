#pragma once

// �I���p�̊֐�
// �I���O�ɉ������鎖������ꍇ�ɗ��p�ł������Ȃ̂łƂ肠�����i\e�Ƃ��j

class End{
private:
	static bool end;
public:
	static void Die();		// �G���[���������ꍇ�̏I��
	static void SubEnd();	// �ʏ�̏I��
	static bool Get();		// �I����Ԃ̎擾
};