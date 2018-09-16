#include "DxLib.h"
#include "Common.h"
#include "Image.h"
#include "Singleton/KeyboardManager.h"
#include "Game/Stage.h"
#include "Game/Character.h"
#include "Game/StaticObject.h"
#include <sstream>
using namespace std;

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
	delete[] mData;
	mData = 0;
	delete[] mCharacters;
	mCharacters = 0;
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
				x++;
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
				mCharacters[ 0 ].setCharacter( x * OBJECT_SIZE , y * OBJECT_SIZE, Character::CHARACTERTYPE_PLAYER );
				x++;
				break;
			case 'E' :
				mCharacters[ j ].setCharacter( x * OBJECT_SIZE , y * OBJECT_SIZE, Character::CHARACTERTYPE_ENEMY );
				j++;
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
			case '\n' :
				y++;
				mWidth = ( mWidth < x ) ? x : mWidth;
				mHeight++;
				x = 0;
				break;
			default :
				x++;
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

	// �v���C���[�̕����X�s�[�h���Z�b�g
	setPlayerDet();

	// �R���W��������
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		int charaX, charaY;			// �L�������W
		mCharacters[ i ].getPosition( &charaX, &charaY );
		int detX, detY;				// �L�����̕����X�s�[�h
		mCharacters[ i ].getDet( &detX, &detY );
		int detMasX, detMasY;		// �L�����̂���}�X����1�}�X��ɂ���}�X
		detMasX = detMasY = 0;
		if( detY == 0 )
		{
			if( detX > 0 )
			{
				detMasX = 1;		// �E�}�X
			}
			else if( detX < 0 )
			{
				detMasX = -1;		// ���}�X
			}
		}
		else if( detY > 0 )
		{
			detMasY = 1;			// ���}�X
		}
		else if( detY < 0 )
		{
			detMasY = -1;			// ��}�X
		}

		int charaMasX = charaX / OBJECT_SIZE;
		int charaMasY = charaY / OBJECT_SIZE;
		int charaDetMasX = charaMasX + detMasX;
		int charaDetMasY = charaMasY + detMasY;
		int movedX = charaX + detX;	// �ړ����X���W
		int movedY = charaY + detY;	// �ړ����Y���W

		bool hitWall = false;
		StaticObject* sObj = &mStaticObjects[ charaDetMasY ][ charaDetMasX ]; // �ړ����StaticObject
		// StaticObject�Ƃ̃R���W��������
		if( sObj->flag() != StaticObject::FLAG_NONE ) // �ړ����StaticObject������
		{
			if( mCharacters[ i ].collisionDetectionToObject( movedX, movedY, sObj ) )
			{
				if( sObj->flag() != StaticObject::FLAG_WALL )
				{
					if( mCharacters[ i ].type() == Character::CHARACTERTYPE_PLAYER )
					{
						unsigned flag = sObj->flag();
						sObj->resetFlag( flag );
					}
					//mCharacters[ i ].update();
				}
				else
				{
					hitWall = true;
					// ToDo : �G�͕����]��
				}
			}
			else
			{
				//mCharacters[ i ].update();
			}
		}
		else // �ړ����StaticObject���Ȃ�
		{
			//mCharacters[ i ].update();
		}

		bool hitCharacter = false;
		for( int j = i + 1; j < mCharactersNumber; j++ )
		{
			Character* chara = &mCharacters[ j ];
			if( mCharacters[ i ].collisionDetectionToObject( movedX, movedY, chara ) )
			{
				hitCharacter = true;
				if( mCharacters[ i ].type() == Character::CHARACTERTYPE_PLAYER )
				{
					mCharacters[ i ].dieCharacter();
				}
			}
		}

		// �v���C���[�͏�ɃX�N���[���ɂ���K�v������
		if((OBJECT_HALF_SIZE < movedX && movedX < WINDOW_WIDTH  - OBJECT_HALF_SIZE) && 
		(OBJECT_HALF_SIZE < movedY && movedY < WINDOW_HEIGHT - OBJECT_HALF_SIZE))
		{
			if( !hitWall & !hitCharacter )
			{
				mCharacters[ i ].update();
			}
		}
	}

	/*
	Character���m�̃R���W��������̂��߂ɁA������n��
	*/
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		for( int j = i + 1; j < mCharactersNumber; j++ )
		{
			Character* chara = &mCharacters[ j ];

			// ToDo : �L�����̍X�V
			//mCharacters[ i ].update( &mCharacters[ j ] );
			//mCharacters[ i ].update();
		}
	}
}

/*
�L�[�{�[�h�̖��L�[�̓��͏�Ԃɂ��A
�v���C���[�̕����X�s�[�h�����߂�
*/
void Stage::setPlayerDet()
{
	int detX = 0;
	int detY = 0;
	// �������L�[�ɂ�蓮�����������߂�
	if( KeyboardManager::instance()->isOn( KEY_INPUT_RIGHT ) )
	{ // �E���L�[�������Ă���
		detX = 1;
		detY = 0;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_LEFT ) )
	{ // �����L�[�������Ă���
		detX = -1;
		detY = 0;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_UP ) )
	{ // ����L�[�������Ă���
		detX = 0;
		detY = -1;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_DOWN ) )
	{ // �����L�[�������Ă���
		detX = 0;
		detY = 1;
	}

	mCharacters[ 0 ].setDet( detX, detY );
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