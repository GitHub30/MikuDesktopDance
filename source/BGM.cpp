#include "BGM.h"
#include "DxLib.h"
#include <math.h>

char BGM::FileName[256];		// BGM�̃t�@�C���܂ł̃p�X
int BGM::Handle;				// BGM�̃n���h��

BGM::BGM()
{
	//�n���h������
	Handle = 0;
	//�t�@�C��������
	strcpy_s(FileName, "");
}

int BGM::Load()
{
	// ���ɉ��y�t�@�C�������[�h���Ă������~������������폜
	if ( CheckSoundMem(Handle) == 1 )
	{
		Stop();
		DeleteSoundMem(Handle);
	}

	// �ǂݍ��ޑO�Ƀf�t�H���g�p�X��I��
    OPENFILENAME ofn;
	TCHAR path[MAX_PATH];
	// ���s�t�@�C���̃p�X��path��
	GetModuleFileName(NULL, path, MAX_PATH);
	// \�̍Ō�̏o���ʒu���擾
	TCHAR* ptmp = _tcsrchr(path, _T('\\'));
	if (ptmp != NULL)
	{
		ptmp = _tcsinc(ptmp);   // �ꕶ���i�߂�
		*ptmp = _T('\0');	// NULL��}��
	}
	else
	{
		// �G���[����
	}

	// ofn�̏������Ɛݒ�
    ZeroMemory( &ofn,sizeof( ofn ) );
    ofn.lStructSize=sizeof( ofn );
    ofn.hwndOwner=GetMainWindowHandle();
    ofn.lpstrFilter=NULL;
    ofn.nFilterIndex=0;
	ofn.lpstrInitialDir = path;		// �ŏ��ɊJ���t�H���_
    ofn.lpstrFile=FileName;
    ofn.nMaxFile=sizeof( FileName );
    ofn.Flags=OFN_CREATEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
    //if(FileName == NULL) return 0;
	// wav�Amp3�Aogg�ɑΉ�
	ofn.lpstrFilter="���y�t�@�C��(*.wav;*.mp3;*.ogg)\0*.*wav;*.*mp3;*.*ogg\0";
    FileName[0]=0;
	int ret = GetOpenFileName( &ofn );
	// �擾�����p�X���特�y���������ɓǂݍ���
	Handle = LoadSoundMem(FileName);
    return ret;
}

void BGM::Start(int vol)
{
	// ���ɍĐ����Ă����ꍇ�͒�~����
	if ( CheckSoundMem(Handle) == 1 ) Stop();
	// ���ʂ�K�p����
	Volume( vol );
	// ���[�v�ōĐ��J�n
	PlaySoundMem( Handle, DX_PLAYTYPE_LOOP );
}

void BGM::Stop()
{
	// ���y���~
	StopSoundMem( Handle );
}

long BGM::CalcDB( int sound_val )
{
	// �p�[�Z���e�[�W�𒲐��p�̐��l�ɕϊ�
	int par;
	par = 100 * sound_val / 255;
	return ( par == 0 ) ? 0 : ( (int)( log10f( (float)par ) * 5000.0f ) );
}

void BGM::Volume(int vol)
{
	// ���ʂ�K�p����
	SetVolumeSoundMem( CalcDB( vol ), Handle );
}