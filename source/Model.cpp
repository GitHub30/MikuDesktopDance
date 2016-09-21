#include "Model.h"
#include "Mouse.h"
#include "Key.h"
#include "Math.h"

void Model::Initialize()
{
	// �t�@�C�����J��
	int datafilep = FileRead_open( "default.ini" );
	// �ǂݍ��݂Ɏg���ϐ��i1�������ǂݍ��ݎw��ʒu�܂ł�ϐ��Ɂj
	int inputi[64];
	char inputc[64];
	// �ŏ���=�܂Ŕ�΂�
	while( ( inputi[0] = FileRead_getc(datafilep) ) != '=' );
	int i = 0;
	// =�̎�������s�܂ł���
	while( ( inputi[i] = inputc[i] = FileRead_getc(datafilep) ) != '\n' )
		i++;
	// NULL�ǉ�
	inputc[i - 1] = '\0';
	// �t�@�C�������
	FileRead_close(datafilep);
	
	// �ǂݍ��񂾕������Filename�ɃR�s�[
	strcpy_s( FileName, inputc );
	// ���f���̓ǂݍ���
	LoadModel();

	// �f�t�H���g�̒l�ݒ�
	drawframe = false;
	drawwireframe = false;

	// �����蔻�菉�����i-1�Ŗ��g�p�j
	for( int i = 0; i < 256; i++ )
		hit[i].number = -1;

	// �ڍs�����蔻��̓ǂݍ���
	/*
	// �����蔻��̃t�@�C�����J��
	datafilep = FileRead_open("media/model/data.txt");
	// �ǂݍ��݂̏I������
	bool end = false;
	// �s���A���ڐ�
	int n = 0, num = 0;
	// �z��̋L�^�ʒu�i�u(�v�������蔻��J�n�̂��߁A���̕�����ǂ݂��񂾏ꍇ�ɏ㏸�j
	int hitindex = -1;

	// �ǂݍ���
	while (!end){
		// �����ύX���Ȃ��i�f�t�H���g�j
		next = false;
		// �w��ʒu�܂ŕ����ǂݍ���
		for (int i = 0; i < 64; i++){
			// �ǂݍ��񂾈ꕶ����inputc��iinputi�ɑ��
			inputc[i] = inputi[i] = FileRead_getc(datafilep);
			// �����u=�v�������ꍇ
			if (inputi[i] == '=')
			{
				// ��U�ǂݍ��݂𒆎~���ĕ����̍ēǂݍ��݁inum=0 �� num=1�j
				inputc[i] = '\0';
				break;
			}
			// �����u,�v�������ꍇ
			if (inputi[i] == ',')
			{
				// �ǂݍ��݂𒆎~���Ēl�̋L�^�inum=2 �` num=7�j
				inputc[i] = '\0';
				break;
			}
			// �����u(�v�������ꍇ
			if (inputi[i] == '(')
			{
				// �ǂݍ��݂𒆎~���ē����蔻��̐��𑝂₵�����̍ēǂݍ��݁inum=1 �� num=2�j
				inputc[i] = '\0';
				hitindex++;
				break;
			}
			// �����u)�v�������ꍇ
			if (inputi[i] == ')')
			{
				// �ǂݍ��݂𒆎~���Ēl�̋L�^�inum=7 �� num=8�j
				inputc[i] = '\0';
				break;
			}
			// �������s�������ꍇ
			if (inputi[i] == '\n')
			{
				// ��U�ǂݍ��݂𒆎~���ĕ����̍ēǂݍ��݁inum=8�j
				inputc[i] = '\0';
				break;
			}
			// �����t�@�C���̏I���������ꍇ
			if (inputi[i] == EOF)
			{
				// �ǂݍ��݂��I������
				end = true;
				break;
			}
		}

		switch (num)
		{
		case 2:
			strcpy_s(hit[hitindex].name,inputc);
			break;
		case 3:
			hit[hitindex].number = atoi(inputc);
			break;
		case 4:
			hit[hitindex].point.x = (float)atof(inputc);
			break;
		case 5:
			hit[hitindex].point.y = (float)atof(inputc);
			break;
		case 6:
			hit[hitindex].point.z = (float)atof(inputc);
			break;
		case 7:
			hit[hitindex].size = atoi(inputc);
			break;
		default:
			break;
		}

		num++;
	}
	*/
	// �t�@�C�������
	FileRead_close(datafilep);

	// �A�j���[�V������Initialize�����s
	animation.Initialize(ModelHandle);
}

void Model::Finalize()
{
	// ���f��������������폜
	MV1DeleteModel(ModelHandle);
	// �A�j���[�V������Finalize�����s
	animation.Finalize(ModelHandle);
}

void Model::Update()
{
	//UpdateFP();
	// �A�j���[�V�����̍X�V
	animation.Update(ModelHandle);
}

void Model::Draw()
{
	// ���f�����A���t�@�摜�Ƃ��ĕ\��������
	MV1SetUseDrawMulAlphaColor( ModelHandle, true );
	// ���f���̕`��
	MV1DrawModel( ModelHandle );

	// �ȉ��f�o�b�O�p
	//DrawFrameModel();
	//DrawNamingFrameModel();
	//DrawFrameCrossModel();;
	//DrawPolyModel();

    /*for( int i = 0 ; i < MeshNum && i < 256; i ++ )
	{
		VECTOR point = MV1GetMeshMinPosition( ModelHandle, i );
		VECTOR screenpoint1 = ConvWorldPosToScreenPos( point ) ;
		VECTOR screenpoint2 = ConvWorldPosToScreenPos( point ) ;
		//screenpoint.x = ( screenpoint1.x + screenpoint2.x ) / 2;
		//screenpoint.y = ( screenpoint1.y + screenpoint2.y ) / 2 - 50.0f;
		screenpoint[i].x = screenpoint1.x;
		screenpoint[i].y = screenpoint1.y - 50.0f;
		float length_i = sqrt( pow( screenpoint[i].x - mpos.x, 2 ) + pow(screenpoint[i].y - mpos.y,2 ) );
		if ( length > length_i ) {
			length = length_i;
			memi = i;
		}
	}
	if ( length < 100.0f )
		MV1DrawMesh( ModelHandle, memi );*/
	//MV1DrawMesh( ModelHandle, 4 );

	/*int MeshNum;
	MeshNum = MV1GetMeshNum( ModelHandle );
	int memi = -1;
    for( int i = 0 ; i < MeshNum; i ++ )
	{
		VECTOR point = MV1GetMeshMaxPosition( ModelHandle, i );
		float length_i = sqrt( pow( point.x - mpos.x, 2 ) + pow( point.y - mpos.y, 2 ) + pow( point.z - mpos.z, 2 ) );
		if ( length > length_i ) {
			length = length_i;
			memi = i;
		}
	}*/

	// �A�j���[�V�����̕`��i���������A�A�j���[�V������񓙒ǉ��������ꍇ�Ɂj
	animation.Draw();
}

int Model::GetHandle()
{
	return ModelHandle;
}

int Model::LoadNewModel(const char* fileFilter)
{
	// �t�@�C���I���_�C�A���O�{�b�N�X�̍\����
    OPENFILENAME ofn;
	// �t�@�C���p�X
	TCHAR path[MAX_PATH];
	// ���s�t�@�C���܂ł̃t�@�C���p�X���擾
	GetModuleFileName( NULL, path, MAX_PATH );
	// \�̍Ō�̏o���ʒu���擾�i���s�t�@�C�����̒��O�j
	TCHAR* ptmp = _tcsrchr( path, _T('\\') );
	if ( ptmp != NULL )
	{
		// \������ꍇ
		// NULL��u���t�@�C��������������
		ptmp = _tcsinc( ptmp );
		*ptmp = _T( '\0' );
	}
	else
	{
		//�G���[
	}

	// ������
    ZeroMemory( &ofn,sizeof(ofn) );
    ofn.lStructSize=sizeof(ofn);
	// ���C���E�B���h�E���I�[�i�[�ɂ���
    ofn.hwndOwner=GetMainWindowHandle();
	// �t�B���^�̎w��i��{NULL�Ȃ̂ł����Ŏw��j
    ofn.lpstrFilter=fileFilter;
    if( fileFilter==NULL ) ofn.lpstrFilter="���f���f�[�^(*.pmd;*.pmx)\0*.*pmd;*.*pmx\0";
    ofn.nFilterIndex=0;
	// ���݂̃p�X�i���s�t�@�C���ʒu�j��\��
	ofn.lpstrInitialDir = path;
    ofn.lpstrFile=FileName;
    ofn.nMaxFile=sizeof(FileName);
	// �t���O�̐ݒ�
    ofn.Flags=OFN_CREATEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
    //if ( FileName==NULL ) return 0;
    FileName[0]=0;
	// ret=0�̎��G���[
	int ret = GetOpenFileName( &ofn );
	if ( ret != 0 )
	{
		// ���f��������������폜
		MV1DeleteModel(ModelHandle);
		// �A�j���[�V������Finalize�����s
		animation.Finalize(ModelHandle);
		// �V�����t�@�C���p�X�̃��f����ǂݍ���
		LoadModel();
		// �A�j���[�V�������ēǂݍ���
		animation.Finalize( ModelHandle );
		animation.Initialize( ModelHandle );
	}
    return ret;
}

void Model::LoadModel()
{
	//���C���E�B���h�E��`�悵�Ȃ��i���f���ǂݍ��ݒ��͕`�悵�Ȃ��j
	SetWindowVisibleFlag( false );

	// ���f���̓ǂݍ���
    ModelHandle = MV1LoadModel( FileName ) ;
	// �ʒu�ƃT�C�Y�̎w��
	MV1SetPosition(ModelHandle, VGet( 0.0f, 0.0f, 0.0f ));
	MV1SetScale(ModelHandle, VGet( 1.0f, 1.0f, 1.0f ));

	int MaterialNum, i;
	float DotWidth ;

	// �}�e���A���̐����擾
	MaterialNum = MV1GetMaterialNum( ModelHandle ) ;
	for( i = 0 ; i < MaterialNum ; i ++ )
	{
		// �}�e���A���̌��X�̗֊s���̑������擾
		DotWidth = MV1GetMaterialOutLineDotWidth( ModelHandle, i ) ;

		// �}�e���A���̗֊s���̑�����0�ɂ���
		//MV1SetMaterialOutLineDotWidth( ModelHandle, i, DotWidth / 50.0f ) ;
		MV1SetMaterialOutLineWidth( ModelHandle, i, 0.0f ) ;
		// �A���t�@�u�����h�ŕ`��
		MV1SetMaterialDrawBlendMode( ModelHandle, i, DX_BLENDMODE_ALPHA) ;
	}
	
	// ���b�V���ƃt���[���̐���ǂݍ��݁i�f�o�b�O�p�H�j
	MeshNum = MV1GetMeshNum(ModelHandle);
	FrameNum = MV1GetFrameNum(ModelHandle);
	//���C���E�B���h�E��`�悷��i���f���ǂݍ��ݒ��͕`�悵�Ȃ��j
	SetWindowVisibleFlag( true );
}

void Model::UpdateFP()
{
	// �t���[�������̃��[�v�i����256�j
    for(int i = 0 ; i < FrameNum && i < 256; i ++ )
	{
		// i�Ԗڂ̃t���[���̍��W���擾
		VECTOR point = MV1GetFramePosition( ModelHandle, i );
		// �X�N���[����̈ʒu���擾
		ScreenFramePoint[i] = ConvWorldPosToScreenPos( point ) ;
	}

	// �����l�܂Ń��[�v
    for( int i = 0 ; i < 256; i ++ )
	{
		// �����蔻�肪������΃��[�v�I��
		if ( hit[i].number == -1 )
		{
			i = 256;
			continue;
		}
		else
		{
			// �����蔻��̍��W�𓾂�
			// �����蔻��Ɋ֘A�t�����ꂽ�t���[�����W�𓾂�
			VECTOR point = MV1GetFramePosition( ModelHandle, hit[i].number );
			// �t���[�����W�ɓ����蔻��ʒu�����Z
			point.x += hit[i].point.x;
			point.y += hit[i].point.y;
			point.z += hit[i].point.z;
			// �����蔻����W���X�N���[����̈ʒu�ɕϊ����擾
			ScreenHitPoint[i] = ConvWorldPosToScreenPos( point ) ;
		}
	}
}

void Model::DrawPolyModel()
{
	// ��ԋ߂��t���[���Ƃ̋���
	float length = 100.0f;
	// �Q�Ɨp���b�V���̍X�V
	for(int i = 0; i < FrameNum; i ++)
		MV1RefreshReferenceMesh( ModelHandle, i, true );
	
	// �Q�Ɨp�|���S���f�[�^�\����
    MV1_REF_POLYGONLIST RefPoly;
    // �Q�Ɨp���b�V�����̎擾
	RefPoly = MV1GetReferenceMesh( ModelHandle, 0, TRUE );
	
	// �|���S���ԍ��L�^�i�����l-1 �L�^�����j
	int memi = -1;
	// ���_�L�^
	int memj;
	// �|���S���̐��������[�v�i�S�Ă��Ə������d���̂Œ��Ӂj
    for( int i = 0 ; i < RefPoly.PolygonNum; i += 50 )
	{
		//�|���S���̒��_�����[�v�i3�����d���̂�1�����j
		for(int j = 0 ; j < 1; j ++ )
		{
			// ���_�����[�v�̉񐔂ɂ���ăC���f�b�N�X�ݒ�
			int index1, index2;
			switch (j)
			{
			case 0:
				index1 = 0;
				index2 = 1;
				break;
			case 1:
				index1 = 1;
				index2 = 2;
				break;
			default:
				index1 = 2;
				index2 = 0;
				break;
			}

			// �|���S���ƃC���f�b�N�X�̒l����2�_�̍��W�i���j���擾
			VECTOR line1, line2;
			line1 = RefPoly.Vertexs[ RefPoly.Polygons[ i ].VIndex[ index1 ] ].Position;
			line2 = RefPoly.Vertexs[ RefPoly.Polygons[ i ].VIndex[ index2 ] ].Position;

			// ����̋���
			float length_i;
			// �}�E�X��3D���W��̈ʒu�擾
			VECTOR mpos = Mouse::GetPos3D();
			// �擾����2�_�̍��W������Ƃ��A�����ƃ}�E�X���W�̍ŒZ�������L�^
			length_i = Segment_Point_MinLength( line1, line2, mpos ) ;

			// ���񂪈�ԋ߂��ꍇ
			if (length > length_i) {
				// �������X�V������̃|���S���ԍ��ƒ��_�ʒu���L�^
				length = length_i;
				memi = i;
				memj = j;
			}
			
			// 3D��Ƀ|���S���̐���`��
			DrawLine3D(
					RefPoly.Vertexs[ RefPoly.Polygons[ i ].VIndex[ index1 ] ].Position,
					RefPoly.Vertexs[ RefPoly.Polygons[ i ].VIndex[ index2 ] ].Position,
					GetColor( 255,255,0 ) ) ;
		}
	}
	
	// ������ԋ߂����W���L�^����Ă����
	if (memi != -1)
	{
		// ���_�ɂ���ăC���f�b�N�X�ݒ�
		int index1, index2;
		switch (memj)
		{
		case 0:
			index1 = 0;
			index2 = 1;
			break;
		case 1:
			index1 = 1;
			index2 = 2;
			break;
		default:
			index1 = 2;
			index2 = 0;
			break;
		}
		
		// �Y���������Ԃŕ`��
		DrawLine3D(
				RefPoly.Vertexs[ RefPoly.Polygons[ memi ].VIndex[ index1 ] ].Position,
				RefPoly.Vertexs[ RefPoly.Polygons[ memi ].VIndex[ index2 ] ].Position,
				GetColor( 255,0,0 ) ) ;
	}
}

void Model::DrawFrameModel()
{
	// ��ԋ߂��t���[���Ƃ̋���
	float length = 100.0f;
	// �t���[���ԍ��L�^�i�����l-1 �L�^�����j
	int memi = -1;
	// �t���[���̐��������[�v�i�S�Ă��Ə������d���̂Œ��Ӂj
    for(int i = 0 ; i < FrameNum && i < 256; i ++ )
	{
		// �}�E�X�̃X�N���[���ʒu�擾
		VECTOR mpos = Mouse::GetPos2D();
		// i�Ԗڂ̃t���[���̃X�N���[���ʒu�ƃ}�E�X�ʒu�̋�������
		float length_i = sqrt(pow(ScreenFramePoint[i].x - mpos.x,2) + pow(ScreenFramePoint[i].y - mpos.y,2));
		
		// ���񂪈�ԋ߂��ꍇ
		if (length > length_i) {
			// �������X�V������̃t���[���ԍ����L�^
			length = length_i;
			memi = i;
		}
	}

	// ������ԋ߂����W���L�^����Ă����
	// ���̃t���[���̂ݕ`�悷��
	if (length < 100.0f)
		MV1DrawFrame(ModelHandle, memi);
	
	// �t���[���̐��������[�v�i�S�Ă��Ə������d���̂Œ��Ӂj
    for(int i = 0 ; i < FrameNum && i < 256; i ++ )
	{
		// ��{�̐F�i���j
		int color = GetColor(255,255,0);
		// �T�C�Y�w��
		int size = 3;
		// ������ԋ߂��t���[���ԍ��Ȃ�ԂɕύX
		if (i == memi) color = GetColor(255,0,0);
		// �����l�܂Ń��[�v
		for(int j = 0 ; j < 256; j ++ )
		{
			// �����蔻�肪������΃��[�v�I��
			if (hit[j].number == -1)
			{
				j = 256;
				continue;
			}
			else
			{
				// ���������蔻��Ɋ֘A����t���[���ԍ��ł����
				// �T�C�Y��ύX����
				if (hit[j].number == i) size = 5;
			}
		}
		// �t���[���ʒu���~�ŕ`��
		DrawCircle((int)ScreenFramePoint[i].x, (int)ScreenFramePoint[i].y, size, color, true);
	}

	// ������ԋ߂����W���L�^����Ă����
	// �֘A���������ʍ���ɕ`��
	if (memi != -1)
	{
		DrawFormatString(15, 180, GetColor(255, 255, 255), "%f", length);
		DrawFormatString(15, 195, GetColor(255, 255, 255), "%d", memi);
		DrawFormatString(15, 210, GetColor(255, 255, 255), "%s", MV1GetFrameName(ModelHandle, memi));
	}
}

void Model::DrawNamingFrameModel()
{
	// ��ԋ߂������蔻��Ƃ̋���
	float length = 100.0f;
	// �����蔻��ԍ��L�^�i�����l-1 �L�^�����j
	int memi = -1;
	// �����蔻��̐��������[�v�i�S�Ă��Ə������d���̂Œ��Ӂj
    for(int i = 0 ; i < 256; i ++ )
	{
		// �}�E�X�̃X�N���[���ʒu�擾
		VECTOR mpos = Mouse::GetPos2D();
		// i�Ԗڂ̓����蔻��̃X�N���[���ʒu�ƃ}�E�X�ʒu�̋�������
		float length_i = sqrt(pow(ScreenHitPoint[i].x - mpos.x,2) + pow(ScreenHitPoint[i].y - mpos.y,2));
		// ���񂪈�ԋ߂��ꍇ
		if (length > length_i) {
			// �������X�V������̓����蔻��ԍ����L�^
			length = length_i;
			memi = i;
		}
	}
	
	// �����l�܂Ń��[�v
    for(int i = 0 ; i < 256; i ++ )
	{
		// ��{�̐F�i�j
		int color = GetColor(0,0,255);
		// ���������蔻����ł���Η΂ɂ���
		if (hit[i].size > length) color = GetColor(0,255,0);
		// �����蔻��ʒu���~�ŕ`��
		DrawCircle((int)ScreenHitPoint[i].x, (int)ScreenHitPoint[i].y, hit[i].size, color, true);
	}

	// ������ԋ߂����W���L�^����Ă����
	// �֘A���������ʍ���ɕ`��
	if (memi != -1)
	{
		DrawFormatString(15, 360, GetColor(255, 255, 255), "%f", length);
		DrawFormatString(15, 375, GetColor(255, 255, 255), "%d", memi);
		DrawFormatString(15, 390, GetColor(255, 255, 255), "%s", hit[memi].name);
	}
}

void Model::DrawFrameCrossModel()
{
	// ��ԋ߂������蔻��Ƃ̋���
	float length = 100.0f;
	// �����蔻��ԍ��L�^�i�����l-1 �L�^�����j
	int memi = -1;
	// �����蔻��̐��������[�v�i�S�Ă��Ə������d���̂Œ��Ӂj
    for(int i = 0 ; i < FrameNum - 1 && i < 255; i ++ )
	{
		// �}�E�X�̃X�N���[���ʒu�擾
		VECTOR mpos = Mouse::GetPos2D();
		// i�ԖڂƎ��̃t���[��2�_�̃X�N���[���ʒu������Ƃ��A�����ƃ}�E�X���W�̍ŒZ�������L�^
		float length_i = Segment_Point_MinLength(ScreenFramePoint[i], ScreenFramePoint[i + 1], mpos);
		//float length_i = Segment_Point_MinLength(point1, point2, mpos);
		if (length > length_i) {
			length = length_i;
			memi = i;
		}
	}
	
	// �t���[��-1�̐��������[�v�i�S�Ă��Ə������d���̂Œ��Ӂj
    for(int i = 0 ; i < FrameNum - 1 && i < 255; i ++ )
	{
		// ��{�̐F�i���j
		int color = GetColor(255,255,0);
		// ������ԋ߂��t���[���ԍ��Ȃ�ԂɕύX
		if (i == memi) color = GetColor(255,0,0);
		// i�Ԗڂ�i+1�Ԗڂ̃t���[���Ԃ���ŕ`��
		DrawLine((int)ScreenFramePoint[i].x, (int)ScreenFramePoint[i].y, (int)ScreenFramePoint[i + 1].x, (int)ScreenFramePoint[i + 1].y, color);
	}

	// ������ԋ߂����W���L�^����Ă����
	// �֘A���������ʍ���ɕ`��
	if (memi != -1)
	{
		DrawFormatString(15, 270, GetColor(255, 255, 255), "%f", length);
		DrawFormatString(15, 285, GetColor(255, 255, 255), "%d", memi);
		//if (strcmp(meshname[memi],""))
		//	DrawFormatString(15, 210, GetColor(255, 255, 255), "%s", meshname[memi]);
	}
}

int Model::GetAnimAmount()
{
	return animation.GetAmount();
}

void Model::Play(int num)
{
	animation.Play( num, ModelHandle );
}