#include "Camera.h"
#include "Key.h"
#include "Mouse.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "colorname.h"
#include "QuaternionHelper.h"

VECTOR Camera::Pos;
VECTOR Camera::Target;
VECTOR Camera::Move;
float Camera::vnear,Camera::vfar;
float Camera::ortho;

void Camera::Initialize()
{
	// �E�B���h�E�T�C�Y�擾
	int WindowX,WindowY;
	GetWindowSize( &WindowX , &WindowY ) ;

	// �N���b�v�����ݒ�
	vnear = 0.1f;
	vfar = 600.0f;
    SetCameraNearFar( vnear, vfar );
	
	// �����ړ��ʐݒ�i�E�B���h�E�����j
	Move.x = ( WindowX - 10 ) / 2.0f;
	Move.y = ( WindowY - 5 ) / 1.0f;
	Move.z = 0;
	// �J�����ʒu�ݒ�
	Pos.x = 0;
	Pos.y = 0;
	Pos.z = -50;
	// �����_�ݒ�
	Target.x = 0;
	Target.y = 0;
	Target.z = 0;
	// �ݒ肵���l��K�p
	SetCameraPosition();

	// ���ˉe�J�������Z�b�g�A�b�v
	ortho = 26.0f;
	SetupCamera_Ortho( ortho ) ;

	// �ݒ�t�@�C������J���������擾����
	int datafilep = FileRead_open( "default.ini" );
	int inputi[256];
	char inputc[256];
	int i = 0;
	for( i = 0; i < 4; i++ )
		while( ( FileRead_getc(datafilep) ) != '\n' );
	//�g�嗦�i�\���͈́j�擾
	i = 0;
	while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
	while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
		i++;
	inputc[i - 1] = '\0';
	ortho = (float)atoi( inputc );
	//�ړ��ʎ擾
	i = 0;
	while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
	while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
		i++;
	inputc[i - 1] = '\0';
	Move.x = (float)atoi( inputc );
	i = 0;
	while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
	while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
		i++;
	inputc[i - 1] = '\0';
	Move.y = (float)atoi( inputc );
	// �g�嗦�i�\���͈́j�̓K�p
	SetupCamera_Ortho( ortho ) ;

	FileRead_close( datafilep );
	
	// �����̐ݒ�
	distance = 10.0f;
	
	// ���f���ړ��n�̏�����
	moving = false;
	moving_x = 0;
	moving_y = 0;

	// ��]�n�̏�����
	rotate = false;
	rotate_xp = false;
	rotate_xm = false;
	rotate_yp = false;
	rotate_ym = false;
	rotate_count = 0;
	rotate_count_max = 1;
	rotate_amount = 1;

	// �J��������\�����Ȃ��i�f�t�H���g�j
	viewdatas = false;
}

void Camera::Init_Pos()
{
	// �ݒ�t�@�C������E�B���h�E�ʒu���擾����
	int datafilep = FileRead_open( "default.ini" );
	int inputi[256];
	char inputc[256];
	int i = 0;
	for( i = 0; i < 7; i++ )
		while( ( FileRead_getc(datafilep) ) != '\n' );
	// �E�B���h�E�ʒu
	int winpos_x, winpos_y;
	i = 0;
	while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
	while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
		i++;
	inputc[i - 1] = '\0';
	winpos_x = atoi( inputc );
	i = 0;
	while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
	while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
		i++;
	inputc[i - 1] = '\0';
	winpos_y = atoi( inputc );
	// �E�B���h�E�ʒu��K�p����
	SetWindowPosition( winpos_x, winpos_y );
	FileRead_close( datafilep );
}

void Camera::Finalize()
{
	// �J�����̏���ݒ�t�@�C���ɋL�^����
	TCHAR change_input[256];	// �������ޕ������ۑ�����ϐ�
	// �f�t�H���g�p�X���w��
	TCHAR path[MAX_PATH];
	// ���s�t�@�C���̃p�X��path��
	GetModuleFileName( NULL, path, MAX_PATH );
	// \�̍Ō�̏o���ʒu���擾
	TCHAR* ptmp = _tcsrchr( path, _T( '\\' ) );
	if ( ptmp != NULL )
	{
		ptmp = _tcsinc( ptmp );   // �ꕶ���i�߂�
		*ptmp = _T( '\0' );	// NULL��}��
	}
	else
	{
		// �G���[����
	}
	// �ݒ�t�@�C���̃p�X
	strcat_s( path, "default.ini" );
	
	// �g�嗦�i�\���͈́j
	wsprintf( change_input, "%d", (int)ortho );
	WritePrivateProfileString( "default", "modelfocus", change_input, path );
	// �J�����ʒu
	wsprintf( change_input, "%d", (int)Pos.x );
	WritePrivateProfileString( "default", "modelpadding_x", change_input, path );
	wsprintf( change_input, "%d", (int)Pos.y );
	WritePrivateProfileString( "default", "modelpadding_y", change_input, path );
	// �E�B���h�E�ʒu
	int winpos_x, winpos_y;
	GetWindowPosition( &winpos_x, &winpos_y );
	wsprintf( change_input, "%d", winpos_x );
	WritePrivateProfileString( "default", "winpos_x", change_input, path );
	wsprintf( change_input, "%d", winpos_y );
	WritePrivateProfileString( "default", "winpos_y", change_input, path );

}

void Camera::Update()
{
	// ��]�̍X�V
	Rotate_Update();
	// ���L�[�ŉ�]
	if ( Key::Hold(KEY_INPUT_LEFT) ) Rotate_Start( rotate_ym );
	if ( Key::Hold(KEY_INPUT_RIGHT) ) Rotate_Start( rotate_yp );
	if ( Key::Hold(KEY_INPUT_DOWN) ) Rotate_Start( rotate_xm );
	if ( Key::Hold(KEY_INPUT_UP) ) Rotate_Start( rotate_xp );

	//�}�E�X���N���b�N������Ă�����E�B���h�E�ړ�����
	if ( moving )
	{
		// �E�B���h�E�T�C�Y�擾
		int WindowX,WindowY;
		GetWindowSize( &WindowX , &WindowY ) ;
		int ScreenX = GetSystemMetrics( SM_CXVIRTUALSCREEN );
		int ScreenY = GetSystemMetrics( SM_CYVIRTUALSCREEN );
		// �V�����}�E�X�ʒu�擾
		int newmoving_x, newmoving_y;
		GetMousePoint( &newmoving_x, &newmoving_y );
		// �O��Ƃ̈ʒu�̍�
		int moving_x_dif, moving_y_dif;
		moving_x_dif = newmoving_x - moving_x;
		moving_y_dif = newmoving_y - moving_y;
		// �E�B���h�E�̈ʒu�擾
		int windowpos_x, windowpos_y;
		GetWindowPosition( &windowpos_x, &windowpos_y );
		// �V�����E�B���h�E�ʒu����
		int newwindow_x, newwindow_y;
		newwindow_x = windowpos_x + moving_x_dif;
		newwindow_y = windowpos_y + moving_y_dif;
		// ���[����
		if ( newwindow_x < 0 ) {
			// �E�B���h�E���[�ɓ��B�����ꍇ�̓J�������ړ�����
			newwindow_x = 0;
			Move.x += moving_x_dif;
			moving_x = newmoving_x;
		}
		else if ( Move.x < WindowX / 2 )
		{
			// �E�B���h�E���[���痣���ꍇ�A��ɃJ�������ړ�����
			newwindow_x = 0;
			Move.x += moving_x_dif;
			if ( Move.x > WindowX / 2 ) 
				Move.x = WindowX / 2.0f;
			moving_x = newmoving_x;
		}
		// �E�[����
		if ( newwindow_x > ScreenX - WindowX ) {
			// �E�B���h�E���[�ɓ��B�����ꍇ�̓J�������ړ�����
			newwindow_x = ScreenX - WindowX;
			Move.x += moving_x_dif;
			moving_x = newmoving_x;
		}
		else if ( Move.x > WindowX / 2 )
		{
			// �E�B���h�E���[���痣���ꍇ�A��ɃJ�������ړ�����
			newwindow_x = ScreenX - WindowX;
			Move.x += moving_x_dif;
			if ( Move.x < WindowX / 2 ) 
				Move.x = (float)(WindowX / 2);
			moving_x = newmoving_x;
		}
		// ��[����
		if ( newwindow_y < -26 ) {
			// �E�B���h�E���[�ɓ��B�����ꍇ�̓J�������ړ�����
			newwindow_y = -26;
			Move.y += moving_y_dif;
			moving_y = newmoving_y;
		}
		else if ( Move.y < WindowY )
		{
			// �E�B���h�E���[���痣���ꍇ�A��ɃJ�������ړ�����
			newwindow_y = -26;
			Move.y += moving_y_dif;
			if ( Move.y > WindowY ) 
				Move.y = (float)WindowY;
			moving_y = newmoving_y;
		}
		// ���[����
		if ( newwindow_y > ScreenY - WindowY ) {
			// �E�B���h�E���[�ɓ��B�����ꍇ�̓J�������ړ�����
			newwindow_y = ScreenY - WindowY;
			Move.y += moving_y_dif;
			moving_y = newmoving_y;
		}
		else if ( Move.y > WindowY )
		{
			// �E�B���h�E���[���痣���ꍇ�A��ɃJ�������ړ�����
			newwindow_y = ScreenY - WindowY;
			Move.y += moving_y_dif;
			if ( Move.y < WindowY ) 
				Move.y = (float)WindowY;
			moving_y = newmoving_y;
		}
		// �E�B���h�E�̈ʒu��ύX����
		SetWindowPosition( newwindow_x, newwindow_y );
	}
	
	// �}�E�X���N���b�N������E�B���h�E�ړ���ԂɈڍs
	if ( Mouse::Touch( 0 ) ){
		moving = true;
		GetMousePoint( &moving_x, &moving_y );
	}
	// �}�E�X�𗣂�����A�E�B���h�E����A�N�e�B�u�ɂȂ�����ړ���Ԃ𖳂���
	if ( Mouse::Out( 0 ) || !GetActiveFlag() )
		moving = false;

	//�J�����̈ʒu�̍X�V
	SetCameraPosition();
}

void Camera::Draw()
{
	// �J�������̕`��
	// �\�����Ȃ��ꍇ�͕Ԃ�
	if ( !viewdatas ) return;
	// �t�H���g�T�C�Y�w��
	SetFontSize( 15 );
	// �����̑����w��
	SetFontThickness( 3 );
	// �t�H���g��g�i�G�b�W�j�t����
	ChangeFontType( DX_FONTTYPE_EDGE ) ;
	//�����`��
	DrawFormatString( 15, 5, white, "camera(%.1f,%.1f,%.1f)", Pos.x, Pos.y, Pos.z );
	DrawFormatString( 15, 20, white, "target(%.1f,%.1f,%.1f)", Target.x, Target.y, Target.z );
	DrawFormatString( 15, 35, white, "move(%.1f,%.1f,%.1f)", Move.x, Move.y, Move.z );
	DrawFormatString( 15, 50, white, "%.1f", ortho );
	
	VECTOR m3dpos = Mouse::GetPos3D();
	DrawFormatString( 15, 65, white, "mouse(%.1f,%.1f,%.1f)", m3dpos.x, m3dpos.y, m3dpos.z );
}

void Camera::Rotate_Start(bool &dir)
{
	// ���ɉ�]���Ă���ꍇ�͉������Ȃ�
	if ( rotate ) return;
	// �w�肵�������̉�]���J�n����
	rotate = dir = true;
	// �J�E���g������
	rotate_count = 0;
	// �J�E���g�ő�l�ݒ�
	rotate_count_max = 10;
	// ����CTRL�L�[�������Ă�����A�ő�l��20�ɂ���i��]�ɂ����鎞�Ԃ��{�ɂȂ�j
	if ( Key::Hold(KEY_INPUT_LCONTROL) > 0 || Key::Hold(KEY_INPUT_RCONTROL) > 0 ) rotate_count_max = 20;
	// ��]�ʂ�ݒ�i1��10�x��]�j
	rotate_amount = 1;
	// ����Shift�L�[�������Ă�����A��]�ʂ�3�ɂ���i3�{��30�x��]�j
	if ( Key::Hold(KEY_INPUT_LSHIFT) > 0 || Key::Hold(KEY_INPUT_RSHIFT) > 0 ) rotate_amount = 3;
}

void Camera::Rotate_Update()
{
	// ������]���Ă��Ȃ��Ȃ牽�����Ȃ�
	if ( !rotate ) return;
	Quaternion Qua;
	Quaternion RotQua;
	Quaternion CQua;
	VECTOR Vx;
	// Y���ŉ�]���Ă�����Y���v���X�����Ƀx�N�g����ݒ�
	if ( rotate_ym || rotate_yp )
		Vx.y = 1.0f;
	else
		Vx.y = 0.0f;
	// X���ŉ�]���Ă�����X���v���X�����Ƀx�N�g����ݒ�
	if ( rotate_xm || rotate_xp )
		Vx.x = 1.0f;
	else
		Vx.x = 0.0f;
	// Z����]�͖���
	Vx.z = 0.0f;
	// ���K���������̂�Qua��
	Qua = QuaternionHelper::Normalization( Vx );
	// ��]�ʂ��擾
	float axis = rotate_amount * 1.0f;
	// �����}�C�i�X�����Ȃ��]���t�ɂ���
	if ( rotate_ym || rotate_xp )
		axis = rotate_amount * -1.0f;
	// ��]�p�̃N�H�[�^�j�I����RotQua��
	RotQua = QuaternionHelper::Rotation( (float)( axis * M_PI / 180.0 ), Qua.v );
	// �t�����̃N�H�[�^�j�I����CQua��
	CQua = RotQua;
	CQua.v.x *= -1;
	CQua.v.y *= -1;
	CQua.v.z *= -1;
	// ���݈ʒu��ݒ�
	Quaternion NowPos;
	NowPos.t = 0;
	NowPos.v = Pos;
	// ���̈ʒu��NextPos��
	Quaternion NextPos = QuaternionHelper::Multi( QuaternionHelper::Multi( CQua, NowPos ), RotQua );
	// �x�N�g��������Pos��
	Pos = NextPos.v;
	// �J�����̍X�V
	SetCameraPosition();
	//�J�E���g����
	rotate_count++;
	if ( rotate_count == rotate_count_max )
	{
		//�w��l�ɂȂ�����I������
		rotate = false;
		rotate_xp = false;
		rotate_xm = false;
		rotate_yp = false;
		rotate_ym = false;
		rotate_count = 0;
	}
}

void Camera::SetCameraPosition()
{
	// �J�����̐ݒ�����ɏ����X�V����
	// �g�嗦�K�p
	SetupCamera_Ortho( ortho ) ;
	// �N���b�v�����K�p
    SetCameraNearFar( vnear, vfar );
	// �J�����ʒu�ƒ����_�̓K�p
	SetCameraPositionAndTarget_UpVecY( Pos, Target );
	// �J�����̈ړ��ʓK�p
	SetCameraScreenCenter( Move.x, Move.y );
}

VECTOR Camera::CameraPos()
{
	// �J�����̈ʒu���擾
	return VGet( Pos.x, Pos.y, Pos.z );
}

void Camera::ResetPos()
{
	// �J�����̐ݒ������������
	rotate = false;
	rotate_xp = false;
	rotate_xm = false;
	rotate_yp = false;
	rotate_ym = false;
	Pos.x = 0;
	Pos.y = 0;
	Pos.z = -50;
	Target.x = 0;
	Target.y = 0;
	Target.z = 0;
	// �J�����̏����X�V
	SetCameraPosition();
}

void Camera::ResetMove()
{
	// �E�B���h�E�T�C�Y�擾
	int WindowX,WindowY;
	GetWindowSize( &WindowX , &WindowY ) ;
	// �X�N���[���T�C�Y�擾
	int ScreenX,ScreenY,ScreenCol;
	GetDefaultState( &ScreenX , &ScreenY , &ScreenCol ) ;
	// �X�N���[�������ɃE�B���h�E��ݒ�
	SetWindowPosition( ScreenX / 2 - WindowX / 2, ScreenY / 2 - WindowY / 2 );
	// �J�����̈ړ��ʂ��E�B���h�E�T�C�Y�̒�����
	Move.x = WindowX / 2.0f;
	Move.y = WindowY / 1.0f;
	Move.z = 0;
	// �J�����̏����X�V
	SetCameraPosition();
}

bool Camera::ChengeViewDatas()
{
	// �f�[�^�̕\���ؑ�
	viewdatas = !viewdatas;
	return viewdatas;
}

void Camera::ChengeFocus( int num )
{
	ortho = (float)num;
	if ( ortho > 128.0f ) ortho = 128.0f;
	if ( ortho < 2.0f ) ortho = 2.0f;
	SetupCamera_Ortho( ortho ) ;
}