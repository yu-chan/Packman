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
mStaticObjects( 0 ),
mCharacters( 0 ),
mCharactersNumber( 0 ),
isClear( false ),
isGameover( false )
{
	// �X�e�[�W���
	mData = new char[size];
	for( int i = 0; i < mSize; i++ )
	{
		mData[ i ] = stageData[ i ];
	}

	mImage = new Image( "data/image/object.png" );

	reset();
}

Stage::~Stage()
{
	delete mImage;
	mImage = 0;
}

// �X�e�[�W��������
void Stage::reset()
{
	// �X�e�[�W�̃T�C�Y���擾
	setSize();
	mStaticObjects = new StaticObject*[ mHeight ];
	for( int i = 0; i < mHeight; i++ )
	{
		mStaticObjects[ i ] = new StaticObject[ mWidth ];
	}


	// �ꕶ�����ǂݍ��݁A���̎�ނ��z�u������̂����߂Ă���
	int x = 0, y = 0;
	for( int i = 0; i < mSize; i++ )
	{
		switch( mData[ i ] )
		{
			case '0' :
				mStaticObjects[ y ][ x ].setStaticObject( x * OBJECT_SIZE, y * OBJECT_SIZE, StaticObject::FLAG_WALL );
				x++;
				break;
			case '1' :
				mStaticObjects[ y ][ x ].setStaticObject( x * OBJECT_SIZE, y * OBJECT_SIZE, StaticObject::FLAG_FEED );
				x++;
				break;
			case '2' :
				mStaticObjects[ y ][ x ].setStaticObject( x * OBJECT_SIZE, y * OBJECT_SIZE, StaticObject::FLAG_INVINCIBLE );
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

	// �L�����̏�����
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
	// �v���C���[������ł�Ȃ�A�������Ȃ�
	if( mCharacters[ 0 ].dead() )
	{
		isGameover = true;
		return;
	}

	// �N���A���Ă���Ȃ�A�������Ȃ�
	if( mCharacters[ 0 ].clear() )
	{
		isClear = true;
		return;
	}

	// �L�����N�^�̍X�V
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
	// �����Ȃ�����
	for( int y = 0; y < mHeight; y++ )
	{
		for( int x = 0; x < mWidth; x++ )
		{
			mStaticObjects[ y ][ x ].draw( mImage );
		}
	}

	// �L����
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		mCharacters[ i ].draw( mImage );
	}
}

// �N���A���Ă邩�ǂ�����Ԃ�
bool Stage::clear()
{
	return isClear;
}

// �Q�[���I�[�o���ǂ�����Ԃ�
bool Stage::gameover()
{
	return isGameover;
}