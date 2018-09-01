#include "DxLib.h"
#include "Image.h"
#include "Game/Character.h"
#include "Singleton/SoundManager.h"
#include "Singleton/KeyboardManager.h"

Character::Character() : 
mCharacterType( CHARACTERTYPE_NONE ),
mDetX( 0 ),
mDetY( 0 ),
isClear( 0 )
{
}

Character::~Character() {}

void Character::setCharacter( int x, int y, CharacterType characterTyp )
{
	set( x, y,  DYANAMIC );
	mCharacterType = characterTyp;
}

/*
�G��p
�������������߂�
*/
void Character::setRandomDet()
{
	double rnd = rand();
	//X���������߂�
	if( rnd < 0.5 )
	{
		mDetX = -1;
	}
	else
	{
		mDetX = 1;
	}

	rnd = rand();
	//Y���������߂�
	if( rnd < 0.5 )
	{
		mDetY = -1;
	}
	else
	{
		mDetY = 1;
	}
}

void Character::update( const Object* obj )
{
	if( !dead() ) {
		if( isPlayer() ) {
			playerMove( obj );
		} else if( isEnemy() ) {
			enemyMove( obj );
		}
	}
}

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

bool Character::dead() const
{
	return ( mCharacterType == CHARACTERTYPE_NONE );
}

bool Character::clear() const
{
	return isClear;
}

bool Character::isPlayer() const
{
	return ( mCharacterType == CHARACTERTYPE_PLAYER );
}

bool Character::isEnemy() const
{
	return ( mCharacterType == CHARACTERTYPE_ENEMY );
}

void Character::playerMove( const Object* obj )
{
}

void Character::enemyMove( const Object* obj )
{
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
			//ToDo : �摜��p�ӂ���
			break;
		case CHARACTERTYPE_ENEMY :
			//ToDo : �摜��p�ӂ���
			break;
	}

	if( srcX != -1 && srcY != -1)
	{
		image->draw( detX, detY, srcX, srcY, OBJECT_SIZE, OBJECT_SIZE );
	}
}

bool Character::collisionDetectionToObject( int movedX, int movedY, Object* obj ) const
{
	int objX, objY;
	obj->getPosition( &objX, &objY );

	
	int aLeft  = movedX - OBJECT_HALF_SIZE;
	int aRight = movedX + OBJECT_HALF_SIZE;
	int bLeft  =   objX - OBJECT_HALF_SIZE;
	int bRight =   objX + OBJECT_HALF_SIZE;
	if( (aLeft < bRight) && (aRight > bLeft) ) {
		int aTop    = movedY - OBJECT_HALF_SIZE;
		int aBottom = movedY + OBJECT_HALF_SIZE;
		int bTop    =   objY - OBJECT_HALF_SIZE;
		int bBottom =   objY + OBJECT_HALF_SIZE;
		if( (aTop < bBottom) && (aBottom > bTop) ) {
			return true;
		}
	}

	return false;
}