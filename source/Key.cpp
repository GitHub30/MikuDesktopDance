#include "DxLib.h"
#include "Key.h"
#include <math.h>

int Key::key[256];
bool Key::lasttouch[256];

Key::Key()
{
	// ������
	for ( int i = 0; i < 256; i++ )
	{
		key[i] = 0;
		lasttouch[i] = false;
	}
}

void Key::Update()
{
	// �O�񉟂���Ă����L�[�͗������u�Ԃɂ���
	for ( int i = 0; i < 256; i++ )
	{
		if ( key[i] != 0 )
		{
			lasttouch[i] = true;
		}
	}

	// �L�[�̏󋵂�tmpkey��
	char tmpkey[256];
	GetHitKeyStateAll(tmpkey);

	for ( int i = 0; i < 256; i++ )
	{
		// �E�B���h�E���A�N�e�B�u�ŃL�[��������Ă���ꍇ
		if ( GetActiveFlag() && tmpkey[i] != 0 )
		{
			// ������Ă���L�[�̃J�E���g�𑝂₵�Alasttouch��false�ɂ���i�����Ă��Ȃ��j
			key[i]++;
			lasttouch[i] = false;
		}
		else
		{
			// ������Ă��Ȃ��ꍇ�A�J�E���g��0��
			// �O�񉟂���Ă����L�[�͗������u�Ԃ̂܂�
			key[i] = 0;
		}
	}
}

void Key::Reset()
{
	// ������
	for ( int i = 0; i < 256; i++ )
	{
		key[i] = 0;
		lasttouch[i] = false;
	}
}

void Key::Draw()
{
}

bool Key::Touch( int n )
{
	// �J�E���g��1�Ȃ牟�����u��
	return key[n] == 1;
}

bool Key::Out( int n )
{
	// �������u�Ԃ̕ϐ��𗘗p
	return lasttouch[n];
}

int Key::Hold( int n )
{
	// �J�E���g�����̂܂ܕԂ�
	return key[n];
}