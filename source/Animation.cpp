#include "Animation.h"

void Animation::Initialize( int modelhandle )
{
	// �\�t�g�N�����ɌĂ΂��
	// �ǂ݂��܂ꂽ���f���̃A�j���[�V�����̐��𓾂�
	// ���f����+������vmd�t�@�C����000,001,002...�ƌ�����Ȃ��Ȃ�܂œǂݍ���ł���B
	amount = MV1GetAnimNum(modelhandle);

	// �����񏉊���
	for( int i = 0; i < 64; i++ )
		strcpy_s( list[i].name, "" );

	// �e�A�j���[�V�������ƂɃ��[�v
	for( int i = 0; i < amount; i++ )
	{
		// �A�^�b�`����
		Handle[i] = MV1AttachAnim( modelhandle, i, -1, FALSE );
		// �A�j���[�V��������o�^����
		char istr[4];
		sprintf_s( istr, "%d", i + 1 );
		strcpy_s( list[i].name, "�A�j���[�V����" );
		strcat_s( list[i].name, istr );
		// �A�j���[�V�����̎��Ԃ�o�^����
		list[i].time = MV1GetAttachAnimTotalTime( modelhandle, Handle[i] );
		// �A�^�b�`�̃u�����h��0�ɂ���
		// �u�����h����0.0f�`1.0f�܂ŁA0.0f�Ŋ��S�����A1.0f�Ŋ��S�K�p�B
		// �A�^�b�`���Ă��镡���̃A�j���[�V�����ɑ΂��u�����h���s����B
		MV1SetAttachAnimBlendRate( modelhandle, Handle[i], 0.0f );
	}
	// ��ԍŏ��̃A�j���[�V�����̃u�����h��1�ɂ���
	MV1SetAttachAnimBlendRate( modelhandle, Handle[0], 1.0f );

	// ��ԍŏ��̃A�j���[�V�������Đ����Ă��鎖���L�^
    index = 0;
    index_old = 0;

    // �Đ����Ԃ̏�����
	Time = 0.0f;

	// ���݂̎��Ԃ��L�^
	PrevTime = GetNowHiPerformanceCount();
	NowTime = PrevTime;

	// ���݂̃t�F�[�h��0�ɂ���
	blending = 0.0f;
}

void Animation::Finalize( int modelhandle )
{
	// �\�t�g�I�����ɓǂݍ��܂��
	// ���f��������������폜����΂����̂ŁA�f�^�b�`���Ȃ��Ă����͂Ȃ�
	for(int i = 0; i < amount; i++)
		MV1DetachAnim( modelhandle, Handle[i] );
}

void Animation::Update(int modelhandle)
{
	// ���t���[���̍X�V
	// �O��̎��Ԃ��L�^
	PrevTime = NowTime;
	// ����̎��Ԃ��L�^
	NowTime = GetNowHiPerformanceCount();
	
	if ( blending == 0.0f )
	{
		// ��t�F�[�h���̓A�j���\�V�����̎��Ԃ�i�߂�
		Time += ( NowTime - PrevTime ) / 1000000.0f * 30.0f;
	}
	else
	{
		// �t�F�[�h����
		blending -= 0.02f;
		if ( blending < 0.0f) blending = 0.0f;//�덷�p
		// �O��̃A�j���[�V�����̃u�����h���������Ă���
		MV1SetAttachAnimBlendRate( modelhandle, Handle[index_old], blending );
		// ����̃A�j���[�V�����̃u�����h�����グ�Ă���
		MV1SetAttachAnimBlendRate( modelhandle, Handle[index], 1.0f - blending );
	}

	// �A�j���[�V�������Ō�܂ōs�����玞�Ԃ�0�ɂ���i���[�v�����j
	// ���[�v���K�v�����A�j���[�V�����̏ꍇ�͂��̏����������Ȃ��K�v������
	if( Time >= list[index].time ){
		Time = 0.0f ;
	}
	
	// �A�j���[�V�����̎��Ԃ����݂̃A�j���[�V�����ɓK�p����
	MV1SetAttachAnimTime( modelhandle, Handle[index], Time );

	/**
		�t�F�[�h���͑O�̃t�F�[�h���n�߂��^�C�~���O�̑O�̃��f���ƁA
		���̃��f���̍ŏ��̃|�[�Y�Ńt�F�[�h����B
		��͑��ʂő̂͂܂����������Ă��鎖��z�肵�Ă���B
	**/
}

void Animation::Draw()
{
	// �`�揈��
}

void Animation::Play( int num, int modelhandle )
{
	if ( blending != 0.0f )
	{
		// �O��̃A�j���[�V�����̃u�����h����0�ɂ���
		MV1SetAttachAnimBlendRate( modelhandle, Handle[index_old], 0.0f );
		// ����̃A�j���[�V�����̃u�����h����1�ɂ���
		MV1SetAttachAnimBlendRate( modelhandle, Handle[index], 1.0f );
	}
	// �w�肵���ԍ��̃A�j���[�V�������Đ�����
	// �t�F�[�h�J�n
	blending = 1.0f;
	// �Đ����Ԃ�0��
	Time = 0.0f ;
	//�O��̔ԍ���index_old�ɁA�w�肵���ԍ���index��
    index_old = index;
    index = num;
	if ( index == index_old ) blending = 0.0f;
}

void Animation::PlayNext()
{
	// ���̔ԍ��̃A�j���[�V�������Đ�����
	if ( index == amount - 1 ) return;
	blending = 1.0f;
	Time = 0.0f ;
    index_old = index;
    index++;
	if ( index == index_old ) blending = 0.0f;
}

void Animation::PlayPrev()
{
	// �O�̔ԍ��̃A�j���[�V�������Đ�����
	if ( index == 0 ) return;
	blending = 1.0f;
	Time = 0.0f ;
    index_old = index;
    index--;
	if ( index == index_old ) blending = 0.0f;
}

void Animation::TimeReset()
{
	// �Đ����Ԃ�����������
	Time = 0.0f ;
}

int Animation::GetAmount()
{
	return amount;
}