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

void Character::setRandomDet()
	//ToDo : 動きを決める
{
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

//キャラクターをカウントする
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
	
	//画像の左上を基準に描画するので、中心から左上に変換
	int detX = convertInnerToPixel( mX );
	int detY = convertInnerToPixel( mY );

	/*
	一枚の画像にたくさんの絵があるので、どれを描くか決める必要がある
	10カウントごとにアニメーション
	*/
	int srcX = -1;
	int srcY = -1;
	int tmpIndex = mCnt / ANIMATION_INTERVAL;
	switch ( mCharacterType )
	{
		case CHARACTERTYPE_PLAYER :
			//ToDo : 画像を用意する
			break;
		case CHARACTERTYPE_ENEMY :
			//ToDo : 画像を用意する
			break;
	}

	if( srcX != -1 && srcY != -1)
	{
		image->draw( detX, detY, srcX, srcY, OBJECT_SIZE, OBJECT_SIZE );
	}
}