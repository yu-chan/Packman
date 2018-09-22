#include "DxLib.h"
#include "Image.h"
#include "Game/Character.h"
#include "Game/StaticObject.h"
#include "Singleton/SoundManager.h"
#include "Singleton/KeyboardManager.h"

Character::Character() : 
mCharacterType( CHARACTERTYPE_NONE ),
mDetX( 0 ),
mDetY( 0 ),
mCnt( 0 ),
mImageSrc( 2 ),
isClear( false )
{
}

Character::~Character() {}

// �L�����N�^�[��������
void Character::setCharacter( int x, int y, CharacterType characterTyp )
{
	set( x, y,  DYNAMIC );
	mCharacterType = characterTyp;
}

/*
�v���C���[��p
���L�[�̓��͏�Ԃɂ��A�����X�s�[�h�����߂�
*/
void Character::setDet( int detX, int detY )
{
	mDetX = detX;
	mDetY = detY;

	/*
	draw�֐��Ō��̊J�̃A�j���[�V�������������Ă���
	�������A���L�[�������Ă��Ȃ��ꍇ�A�摜��������������
	�܂��A��~���Ă���Ԃ́A���O�̖��L�[�ɑΉ����������������K�v������
	���������āA������ێ�����ϐ���p�ӂ���K�v������
	*/
	if( mDetY == 0 )
	{
		if( mDetX > 0 )
		{
			mImageSrc = 0;	// �E
		}
		else if( mDetX < 0 )
		{
			mImageSrc = 1;	// ��
		}
	}
	else if( mDetY < 0 )
	{
		mImageSrc = 2;		// ��
	}
	else if( mDetY > 0 )
	{
		mImageSrc = 3;		// ��
	}
}

/*
�G��p
�������������߂�
*/
void Character::setRandomDet()
{
	int rnd = rand() % 100;
	//X���������߂�
	if( rnd < 25 )		// �E
	{
		mDetX = 1;
		mDetY = 0;
	}
	else if( 25 <= rnd && rnd < 50 )	// ��
	{
		mDetX = -1;
		mDetY = 0;
	}
	else if( 50 <= rnd && rnd < 75 )	// ��
	{
		mDetX = 0;
		mDetY = -1;
	}
	else if( 75 <= rnd )					// ��
	{
		mDetX = 0;
		mDetY = 1;
	}
}

//�L�����̕����X�s�[�h���擾
void Character::getDet( int* detX, int* detY )
{
	*detX = mDetX;
	*detY = mDetY;
}

// �L�����̃^�C�v���擾
unsigned Character::type() const
{
	return mCharacterType;
}

//�L�����N�^�[���J�E���g����
void Character::count()
{
	if( mCnt == FPS )
	{
		mCnt = 0;
	}
	mCnt++;
}

void Character::update()
{
	if( !dead() ) {
		move();
		mCnt++;
	}
}

void Character::move()
{
	mX += mDetX;
	mY += mDetY;
}

// �L����������ł��邩�ǂ�����Ԃ�
bool Character::dead() const
{
	return ( mCharacterType == CHARACTERTYPE_NONE );
}

// �N���A���Ă��邩�ǂ�����Ԃ�
bool Character::clear() const
{
	return isClear;
}

// �v���C���[�ł��邩��Ԃ�
bool Character::isPlayer() const
{
	return ( mCharacterType == CHARACTERTYPE_PLAYER );
}

// �I�ł��邩��Ԃ�
bool Character::isEnemy() const
{
	return ( mCharacterType == CHARACTERTYPE_ENEMY );
}

void Character::draw( const Image* image ) const
{
	if( dead() )
	{
		return;
	}
	
	//�摜�̍������ɕ`�悷��̂ŁA���S���獶��ɕϊ�
	int detX = convertInnerToPixel( mX );
	int detY = convertInnerToPixel( mY );

	/*
	�ꖇ�̉摜�ɂ�������̊G������̂ŁA�ǂ��`�������߂�K�v������
	10�J�E���g���ƂɃA�j���[�V����
	*/
	int srcX = -1;
	int srcY = -1;
	int tmpIndex = mCnt / ANIMATION_INTERVAL;
	switch ( mCharacterType )
	{
		case CHARACTERTYPE_PLAYER :
			if( ( mDetX != 0 || mDetY != 0 ) && tmpIndex % 2 == 0 )			// �ۂ��Ȃ�
			{
				srcX = 1;
				srcY = 0;
			}
			else							// �����J��
			{
				srcX = 0;
				srcY = mImageSrc;
			}
			break;
		case CHARACTERTYPE_ENEMY :
			srcY = 4;
			//srcX = 0; // ToDo : ���Ƃŏ���
			if( mDetY == 0 )
			{
				if( mDetX < 0 )			// ��
				{
					srcX = 0;
				}
				else if( mDetX > 0 )	// �E
				{
					srcX = 1;
				}
			}
			else if( mDetY < 0 )
			{
				srcX = 2;				// ��
			}
			else
			{
				srcX = 3;				// ��
			}
			break;
	}

	if( srcX != -1 && srcY != -1)
	{
		image->draw( detX, detY, srcX, srcY, OBJECT_SIZE, OBJECT_SIZE );
	}
}

// �R���W��������
bool Character::collisionDetectionToObject( int movedX, int movedY, Object* obj ) const
{
	int objX, objY;
	obj->getPosition( &objX, &objY );

	
	int aLeft  = movedX - OBJECT_HALF_SIZE;
	int aRight = movedX + OBJECT_HALF_SIZE;
	int bLeft  =   objX - OBJECT_HALF_SIZE;
	int bRight =   objX + OBJECT_HALF_SIZE;
	if( ( aLeft < bRight ) && ( aRight > bLeft ) )
	{
		int aTop    = movedY - OBJECT_HALF_SIZE;
		int aBottom = movedY + OBJECT_HALF_SIZE;
		int bTop    =   objY - OBJECT_HALF_SIZE;
		int bBottom =   objY + OBJECT_HALF_SIZE;
		if( ( aTop < bBottom ) && ( aBottom > bTop ) )
		{
			return true;
		}
	}

	return false;
}

void Character::dieCharacter()
{
	mCharacterType = CHARACTERTYPE_NONE;
}