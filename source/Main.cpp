#include "DxLib.h"
#include "Mouse.h"
#include "Camera.h"
#include "Model.h"
#include "End.h"
#include "Key.h"
#include "BGM.h"
#include "CommandPanel.h"
#include "colorname.h"

//���j���[�p
HMENU hMenu;
WNDPROC dxWndProc;

Model model;
Camera camera;
BGM bgm;
CommandPanel commandpanel;

bool framedraw;	// �E�B���h�E�O�g�`��
bool controck;	// ���샍�b�N
int light;		// ���C�g�l

#define IDR_RMENU		1100 // ���j���[
#define IDM_NEWMODEL	1102 // ���f���V�K�ǂݍ���
#define IDM_TOP			1120 // ��Ɏ�O/�ʏ�؂�ւ�
#define IDM_FRAMEDRAW	1121 // �E�B���h�E�t���[���`��
#define IDM_ROCK		1122 // ���샍�b�N
#define IDM_MDROTRESET	1200 // ���f����]���Z�b�g
#define IDM_CAMERARESET	1201 // �J�����ʒu���Z�b�g
#define IDM_CAMERAINFO	1202 // �J�������\��
#define IDM_CTPANEL		1300 // ����p�l���\��
#define IDM_CLOSE		1990 // ����
#define IDM_QUIT		1991 // �I��

void CMenu();					// �|�b�v�A�b�v���j���[�쐬
LRESULT CALLBACK MyProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);	// �|�b�v�A�b�v���j���[�̓���
void Finalize();				// �\�t�g�I�������i��Ԃ̃Z�[�u�j

// ���C���֐�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	int SoftImageHandle;
	int MSAAScreenHandle;
	int ScreenHandle;
	
	SetOutApplicationLogValidFlag(FALSE);

	int ScreenW, ScreenH, ScreenCol;

	framedraw = false;
	controck = false;

	//��d�N���\
	SetDoubleStartValidFlag( true );
	//���C���E�B���h�E��`�悵�Ȃ��i�N���r���͕`�悵�Ȃ��j
	SetWindowVisibleFlag( false );
	//��A�N�e�B�u�ł�����
	SetAlwaysRunFlag( true );
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode( true );
	//�E�B���h�E�T�C�Y�ݒ�
	GetDefaultState( &ScreenW, &ScreenH, &ScreenCol ) ;
	//������ݒ�t�@�C���ŕύX�\�ɂ���
	{
		int datafilep = FileRead_open( "default.ini" );
		int inputi[256];
		char inputc[256];
		int i = 0;
		while( ( FileRead_getc(datafilep)) != '\n' );
		while( ( FileRead_getc(datafilep)) != '\n' );
		while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
		while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
			i++;
		inputc[i - 1] = '\0';
		ScreenW = atoi(inputc);
		i = 0;
		while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
		while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
			i++;
		inputc[i - 1] = '\0';
		ScreenH = atoi(inputc);

		light = 0;
		for( i = 0; i < 5; i++ )
			while( ( FileRead_getc(datafilep) ) != '\n' );
		//���ʎ擾
		i = 0;
		while( ( inputi[0] = FileRead_getc(datafilep) ) != '=');
		while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
			i++;
		inputc[i - 1] = '\0';
		light = atoi(inputc);

		FileRead_close( datafilep );
	}
	SetWindowSize( ScreenW, ScreenH );
	SetGraphMode( ScreenW, ScreenH, 32 ); 

	// �E�C���h�E�̓��ߐF���[�h�n�m
	SetUseBackBufferTransColorFlag( true );
	SetUseUpdateLayerdWindowFlag( true );

	SetWindowStyleMode(2);

	// �c�w���C�u�����̏�����
	if( DxLib_Init() < 0 ) return -1;
	
	// �A���`�G�C���A�X�t���X�N���[���쐬
	SetCreateDrawValidGraphMultiSample( 8, 4 );
	MSAAScreenHandle = MakeScreen( ScreenW, ScreenH, true );;
	SetCreateDrawValidGraphMultiSample( 0, 0 );
	// �A���`�G�C���A�X�����X�N���[���쐬
	ScreenHandle = MakeScreen( ScreenW, ScreenH, true );
	// ��ʎ�荞�ݗp�̃\�t�g�E�G�A�p�摜���쐬
	SoftImageHandle = MakeARGB8ColorSoftImage( ScreenW, ScreenH ); 

	Mouse mouse;
	Key key;

	commandpanel.Initialize( hInstance, nCmdShow );
	model.Initialize();
	camera.Initialize();

	commandpanel.AnimResist( 0, model.GetAnimAmount() );
	
	CMenu();
	HWND hMainWnd;
    hMainWnd = GetMainWindowHandle();
    //���C���E�B���h�E�̃E�B���h�E�v���V�[�W���̃A�h���X���i�[
    dxWndProc = (WNDPROC)GetWindowLong( hMainWnd, GWL_WNDPROC );
    //����E�B���h�E�v���V�[�W���̃A�h���X��ݒ�
    SetWindowLong( hMainWnd, GWL_WNDPROC, (LONG)MyProc );
	
	SetLightAmbColor( GetColorF( light * 0.01f, light * 0.01f, light * 0.01f, 0.0f ) ) ;
	
	//�������烁�C���E�B���h�E��`�悷��i�N���r���͕`�悵�Ȃ��j
	SetWindowVisibleFlag( true );
	
	// ���ߐF��ݒ�i���j
	SetTransColor( 255, 0, 255 ) ;

	camera.ResetMove();

	camera.Init_Pos();

	while( ProcessMessage() == 0 && !End::Get() )
	{
		// �`�����A���`�G�C���A�X�t���X�N���[���ɂ���
		SetDrawScreen( MSAAScreenHandle );

		// ��ʂ��N���A
		ClearDrawScreen();

		//�e��@�\�X�V
		if ( !controck )
		{
			mouse.Update();
			key.Update();
		}

		if ( ( key.Hold(KEY_INPUT_LSHIFT) || key.Hold(KEY_INPUT_RSHIFT) ) && ( key.Hold(KEY_INPUT_LCONTROL) || key.Hold(KEY_INPUT_RCONTROL) ) && key.Hold(KEY_INPUT_F12) )
		{
			camera.ResetMove();
		}

		commandpanel.Update();
		switch ( commandpanel.Message() )
		{
		case CME_NONE:
			break;
		case CME_ANIMATION:
			model.Play( commandpanel.GetParam() );
			break;
		case CME_FOCUS:
			camera.ChengeFocus( commandpanel.GetParam() );
			break;
		default:
			break;
		}

		model.Update();
		camera.Update();

		//�e��@�\�`��
		if ( framedraw )
		{
			DrawBox( 0, 0, ScreenW, ScreenH, dblue, false );
			DrawBox( 1, 1, ScreenW - 1, ScreenH - 1, dblue, false );
			DrawBox( 2, 2, 62, 17, wblue, true );
			DrawBox( ScreenW - 62, ScreenH - 17, ScreenW - 2, ScreenH - 2, wblue, true );
		}
		model.Draw();
		camera.Draw();

		// �`�����A���`�G�C���A�X�����X�N���[���ɂ���
		SetDrawScreen( ScreenHandle );

		// �A���t�@�l���܂߂Ă��̂܂ܕ`�悷��u�����h���[�h�ɃZ�b�g���ĕ`��
		SetDrawBlendMode( DX_BLENDMODE_SRCCOLOR, 255 );
		DrawGraph( 0, 0, MSAAScreenHandle, true );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
		 
		// �`���̉摜���\�t�g�C���[�W�Ɏ擾����
		GetDrawScreenSoftImage( 0, 0, ScreenW, ScreenH, SoftImageHandle );

		// ��荞�񂾃\�t�g�C���[�W���g�p���ē��߃E�C���h�E�̏�Ԃ��X�V����
		UpdateLayerdWindowForPremultipliedAlphaSoftImage( SoftImageHandle );
	}
	
	model.Finalize();
	camera.Finalize();
	Finalize();

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}

// �|�b�v�A�b�v���j���[�쐬
void CMenu()
{
	int id = 0;
	hMenu = CreatePopupMenu();
	HMENU hAnimMenu = CreatePopupMenu();
	HMENU hLightMenu = CreatePopupMenu();
	HMENU hBGMVolumeMenu = CreatePopupMenu();
	MENUITEMINFO mii;

	ZeroMemory( &mii, sizeof(MENUITEMINFO) );	// ������
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fType = MFT_SEPARATOR;
	 
	// ���f���V�K�ǂݍ���
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_NEWMODEL;
	mii.dwTypeData = TEXT( "���f���V�K�ǂݍ���" );
    
	// ���j���[���ڒǉ�
	InsertMenuItem( hMenu, id++, TRUE, &mii );

	// �Z�p���[�^�[
	mii.fMask = MIIM_FTYPE;

	InsertMenuItem( hMenu, id++, TRUE, &mii );

	// ��Ɏ�O/�ʏ�؂�ւ�
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_TOP;
	mii.dwTypeData = TEXT( "��Ɏ�O/�ʏ�؂�ւ�" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );
	
	// �E�B���h�E�t���[���`��
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_FRAMEDRAW;
	mii.dwTypeData = TEXT( "�E�B���h�E�t���[���`��" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );
	
	// ���샍�b�N
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_ROCK;
	mii.dwTypeData = TEXT( "���샍�b�N" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );

	// �Z�p���[�^�[
	mii.fMask = MIIM_FTYPE;
	
	InsertMenuItem( hMenu, id++, TRUE, &mii );
	 
	// ���f����]���Z�b�g
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_MDROTRESET;
	mii.dwTypeData = TEXT( "���f����]���Z�b�g" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );
	 
	// �J�����ʒu���Z�b�g
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_CAMERARESET;
	mii.dwTypeData = TEXT( "�J�����ʒu���Z�b�g" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );
	 
	// �J�������\��
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_CAMERAINFO;
	mii.dwTypeData = TEXT( "�J�������\��" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );

	// ����p�l���\��
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_CTPANEL;
	mii.dwTypeData = TEXT( "����p�l���\��" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );
	 
	// ����
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_CLOSE;
	mii.dwTypeData = TEXT( "����" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );

	// �Z�p���[�^�[
	mii.fMask = MIIM_FTYPE;
	
	InsertMenuItem( hMenu, id++, TRUE, &mii );

	// �I��
	mii.fMask = MIIM_ID | MIIM_STRING;
	mii.wID = IDM_QUIT;
	mii.dwTypeData = TEXT( "�I��" );
     
	InsertMenuItem( hMenu, id++, TRUE, &mii );
}

// �|�b�v�A�b�v���j���[�̓���
LRESULT CALLBACK MyProc( HWND hWnd, UINT msg, WPARAM wp, LPARAM lp )
{
	POINT pt;
	static bool top = false;

    switch (msg) {
	case WM_CREATE:
       break;
	case WM_RBUTTONDOWN:
		// �}�E�X�J�[�\�����W�擾
		pt.x = LOWORD( lp );
		pt.y = HIWORD( lp );
		// �X�N���[�����W�ɕϊ�
		ClientToScreen( hWnd, &pt );
		// �J�[�\���ʒu�Ƀ��j���[���o��
		TrackPopupMenu( hMenu, 0, pt.x, pt.y, 0, hWnd, NULL );
       break;
	case WM_COMMAND:
		{
			int lw = LOWORD( wp );
			switch ( lw ) {
			case IDM_NEWMODEL:
				{
					int ret = model.LoadNewModel( NULL );
					if ( ret )
					{
						CMenu();
					}
					controck = false;
				}
				break;
			case IDM_MDROTRESET:
				camera.ResetPos();
				break;
			case IDM_CAMERARESET:
				camera.ResetMove();
				break;
			case IDM_TOP:
				top = !top;
				if ( top )
				{
					SetWindowPos( GetMainWindowHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
					CheckMenuItem( hMenu, IDM_TOP, MFS_CHECKED );
				}
				else
				{
					SetWindowPos( GetMainWindowHandle(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
					CheckMenuItem( hMenu, IDM_TOP, MFS_UNCHECKED );
				}
				break;
			case IDM_FRAMEDRAW:
				framedraw = !framedraw;
				if ( framedraw )
					CheckMenuItem( hMenu, IDM_FRAMEDRAW, MFS_CHECKED );
				else
					CheckMenuItem( hMenu, IDM_FRAMEDRAW, MFS_UNCHECKED );
				break;
			case IDM_ROCK:
				controck = !controck;
				if ( controck )
				{
					Key::Reset();
					Mouse::Reset();
					CheckMenuItem( hMenu, IDM_ROCK, MFS_CHECKED );
				}
				else
				{
					CheckMenuItem( hMenu, IDM_ROCK, MFS_UNCHECKED );
				}
				break;
			case IDM_CAMERAINFO:
				if ( camera.ChengeViewDatas() )
					CheckMenuItem( hMenu, IDM_CAMERAINFO, MFS_CHECKED );
				else
					CheckMenuItem( hMenu, IDM_CAMERAINFO, MFS_UNCHECKED );
				break;
			case IDM_CTPANEL:
				commandpanel.Open();
				break;
			case IDM_CLOSE:
				break;
			case IDM_QUIT:
				End::SubEnd();
				break;
			default:
				break;
			}
		}
		break;
    case WM_LBUTTONDOWN:
        break;
	case WM_DESTROY : /* �I������ */
		DestroyMenu( hMenu );
		PostQuitMessage( 0 );
		break;
    }
    return CallWindowProc( dxWndProc, hWnd, msg, wp, lp );
}

void Finalize()
{
	TCHAR change_input[256];
	TCHAR path[MAX_PATH];
	AppLogAdd( "in camera finalize\n" );
	GetModuleFileName( NULL, path, MAX_PATH );
	TCHAR* ptmp = _tcsrchr( path, _T('\\') ); // \�̍Ō�̏o���ʒu���擾
	if ( ptmp != NULL )
	{   //�t�@�C�������폜
		ptmp = _tcsinc( ptmp );   //�ꕶ���i�߂�
		*ptmp = _T('\0');
	}
	else
	{
		//�G���[�F\������
		AppLogAdd( "error no save file\n" );
	}
	strcat_s( path, "default.ini" );

	wsprintf( change_input, "%d", light );
	WritePrivateProfileString( "default", "light", change_input, path );
}