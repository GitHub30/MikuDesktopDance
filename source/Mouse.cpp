#include "Mouse.h"
#include "Camera.h"
#include <math.h>

int Mouse::left;		// ���{�^������
int Mouse::right;		// �E�{�^������
int Mouse::wheel;		// �z�C�[����]��
bool Mouse::lefttouch;	// ���{�^���𗣂����u��
bool Mouse::righttouch;	// �E�{�^���𗣂����u��

Mouse::Mouse()
{
	left = 0;
	right = 0;
	wheel = 0;
	lefttouch = false;
	righttouch = false;
}

void Mouse::Update()
{
	//�O�ɃN���b�N����Ă����touch��true�ɂ���
	//���̌㍡��N���b�N����Ă��Ȃ��ꍇ�͂��̂܂�true�ƂȂ�
	//�������u�Ԃ�1�t���[���̂ݕۑ�����
	if (left != 0)
		lefttouch = true;
	else
		lefttouch = false;

	if (right != 0)
		righttouch = true;
	else
		righttouch = false;
	
	//�}�E�X�̃N���b�N��Ԃ��擾
	if ( GetActiveFlag() && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//������Ă����ꍇ���ԑ���
		left++;
		//�������u�Ԃł͂Ȃ��̂�touch��false
		lefttouch = false;
	}
	else{
		//�����Ă���̂Ŏ��Ԃ�s0�ɂ���
		left = 0;
	}
	
	if ( GetActiveFlag() && (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		right++;
		righttouch = false;
	}
	else{
		right = 0;
	}

	//�z�C�[����]�ʎ擾
	wheel = GetMouseWheelRotVol();
}

void Mouse::Reset()
{
	left = 0;
	right = 0;
	wheel = 0;
	lefttouch = false;
	righttouch = false;
}

void Mouse::Draw()
{
}

bool Mouse::Touch(int n)
{
	//������0�Ȃ獶�A����ȊO�Ȃ�E�N���b�N�������ꂽ�u�Ԃ���Ԃ�
	bool ret = false;
	if (n == 0) ret = left == 1;
	else ret = right == 1;
	return ret;
}

bool Mouse::Out(int n)
{
	//������0�Ȃ獶�A����ȊO�Ȃ�E�N���b�N���������u�Ԃ���Ԃ�
	bool ret = false;
	if (n == 0) ret = lefttouch;
	else ret = righttouch;
	return ret;
}

int Mouse::Hold(int n)
{
	//������0�Ȃ獶�A����ȊO�Ȃ�E�N���b�N�������ꂽ���Ԃ�Ԃ�
	int ret = 0;
	if (n == 0) ret = left;
	else ret = right;
	return ret;
}

int Mouse::Wheel()
{
	return wheel;
}

VECTOR Mouse::GetPos2D()
{
	//2D��̃}�E�X���W��VECTOR�\���̂ŕԂ�
	int mx, my;
	GetMousePoint(&mx, &my);
	VECTOR mpos;
	mpos.x = (float)mx;
	mpos.y = (float)my;
	mpos.z = 0.0f;
	return mpos;
}

VECTOR Mouse::GetPos3D()
{
	//3D��̃}�E�X���W��VECTOR�\���̂ŕԂ�
	int mx, my;
	GetMousePoint(&mx, &my);
	return ConvScreenPosToWorldPos( VGet( (float)mx, (float)my, 0.0f ) ) ;
}