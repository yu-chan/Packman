#include "DxLib.h"
#include "Common.h"
#include "Image.h"
#include "Game/Stage.h"
#include "Game/Character.h"
#include "Game/StaticObject.h"

/*
stageData : �X�e�[�W���
size      : �X�e�[�W�T�C�Y 
*/
Stage::Stage( const char* stageData, const int size ) :
mImage( 0 ),
mData( 0 ),
mSize( size ),
mWidth( 0 ),
mHeight( 0 ),
mCharacters( 0 ),
mCharactersNumber( 0 ),
isClear( false ),
isGameover( false )
{
	//�X�e�[�W���
	mData = new char[size];
	for( int i = 0; i < mSize; i++ )
	{
		mData[ i ] = stageData[ i ];
	}

	//ToDo : �����f�B���N�g����ς��邩��
	mImage = new Image( "data/image/object.png" );

	reset();
}

Stage::~Stage()
{
	delete mImage;
	mImage = 0;
}

//�X�e�[�W��������
void Stage::reset()
{
	setSize();

	//ToDo : StaticObject�̃Z�b�g
	//staticobject.set

	//�ꕶ�����ǂݍ��݁A���̎�ނ��z�u������̂����߂Ă���
	int x = 0, y = 0;
	for( int i = 0; i < mSize; i++ )
	{
		switch( mData[ i ] )
		{
			case '0' :
				//ToDo : staticobject�ɃZ�b�g
				x++;
				break;
			case '1' :
				//ToDo : staticobject�ɃZ�b�g
				x++;
				break;
			case '2' :
				//ToDo : staticobject�ɃZ�b�g
				x++;
				break;
			case 'P' :
			case 'E' :
				mCharactersNumber++;
				x++;
				break;
			case '\n' :
				x = 0;
				y++;
				break;
			default :
				break;
		}
	}

	//ToDo : �ύX���邩��
	//�L�����̏�����
	if( mCharacters )
	{
		delete[] mCharacters;
		mCharacters = 0;
	}
	mCharacters = new Character[ mCharactersNumber ];
	
	int j = 1;
	x = y = 0;
	for( int i = 0; i < mSize; i++ )
	{
		switch( mData[ i ] )
		{
			case 'P' :
				mCharacters[0].setCharacter( x * OBJECT_SIZE , y * OBJECT_SIZE, Character::CHARACTERTYPE_PLAYER );
				x++;
				break;
			case 'E' :
				mCharacters[0].setCharacter( x * OBJECT_SIZE , y * OBJECT_SIZE, Character::CHARACTERTYPE_ENEMY );
				x++;
				break;
			case '\n' :
				x = 0;
				y++;
				break;
			default :
				x++;
				break;
		}
	}
}

/*
�ǂݍ��񂾃X�e�[�W���̕��ƍ��������߂�
stageData : �X�e�[�W���
size      : �X�e�[�W�T�C�Y 
*/
void Stage::setSize()
{
	mWidth = mHeight = 0;
	int x = 0, y = 0;
	for( int i = 0; i < mSize; i++ )
	{
		switch( mData[ i ] )
		{
			case '0' :
			case '1' :
			case '2' :
				x++;
			case '\n' :
				y++;
				mWidth = ( mWidth < x ) ? x : mWidth;
				mHeight++;
				x = 0;
				break;
			default :
				break;
		}
	}
}

/*
�X�e�[�W�X�V
*/
void Stage::update()
{
	//�v���C���[������ł�Ȃ�A�������Ȃ�
	if( mCharacters[ 0 ].dead() )
	{
		isGameover = true;
		return;
	}

	//�N���A���Ă���Ȃ�A�������Ȃ�
	if( mCharacters[ 0 ].clear() )
	{
		isClear = true;
		return;
	}

	int preX, preY;	//�v���C���[�������O�̈ʒu
	mCharacters[ 0 ].getPosition( &preX, &preY );

	//�L�����N�^�̍X�V
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		for( int j = i + 1; j < mCharactersNumber; j++ )
		{
			mCharacters[ i ].update( &mCharacters[ j ] );
		}
	}
}

/*
�`��֐�
*/
void Stage::draw() const
{
	//�����Ȃ�����
	for( int y = 0; y < mHeight; y++ )
	{
		for( int x = 0; x < mWidth; x++ )
		{
			//ToDo : �`��
		}
	}

	//�L����
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		//ToDo : �`��
	}
}