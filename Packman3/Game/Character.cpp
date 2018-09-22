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

// キャラクターを初期化
void Character::setCharacter( int x, int y, CharacterType characterTyp )
{
	set( x, y,  DYNAMIC );
	mCharacterType = characterTyp;
}

/*
プレイヤー専用
矢印キーの入力状態により、方向スピードを決める
*/
void Character::setDet( int detX, int detY )
{
	mDetX = detX;
	mDetY = detY;

	/*
	draw関数で口の開閉のアニメーションを実装している
	しかし、矢印キーを押していない場合、画像がちかちかする
	また、停止している間は、直前の矢印キーに対応する方向を向ける必要がある
	したがって、向きを保持する変数を用意する必要がある
	*/
	if( mDetY == 0 )
	{
		if( mDetX > 0 )
		{
			mImageSrc = 0;	// 右
		}
		else if( mDetX < 0 )
		{
			mImageSrc = 1;	// 左
		}
	}
	else if( mDetY < 0 )
	{
		mImageSrc = 2;		// 上
	}
	else if( mDetY > 0 )
	{
		mImageSrc = 3;		// 下
	}
}

/*
敵専用
動く方向を決める
*/
void Character::setRandomDet()
{
	int rnd = rand() % 100;
	//X方向を決める
	if( rnd < 25 )		// 右
	{
		mDetX = 1;
		mDetY = 0;
	}
	else if( 25 <= rnd && rnd < 50 )	// 左
	{
		mDetX = -1;
		mDetY = 0;
	}
	else if( 50 <= rnd && rnd < 75 )	// 上
	{
		mDetX = 0;
		mDetY = -1;
	}
	else if( 75 <= rnd )					// 下
	{
		mDetX = 0;
		mDetY = 1;
	}
}

//キャラの方向スピードを取得
void Character::getDet( int* detX, int* detY )
{
	*detX = mDetX;
	*detY = mDetY;
}

// キャラのタイプを取得
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

// キャラが死んでいるかどうかを返す
bool Character::dead() const
{
	return ( mCharacterType == CHARACTERTYPE_NONE );
}

// クリアしているかどうかを返す
bool Character::clear() const
{
	return isClear;
}

// プレイヤーであるかを返す
bool Character::isPlayer() const
{
	return ( mCharacterType == CHARACTERTYPE_PLAYER );
}

// 的であるかを返す
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
			if( ( mDetX != 0 || mDetY != 0 ) && tmpIndex % 2 == 0 )			// 丸くなる
			{
				srcX = 1;
				srcY = 0;
			}
			else							// 口が開く
			{
				srcX = 0;
				srcY = mImageSrc;
			}
			break;
		case CHARACTERTYPE_ENEMY :
			srcY = 4;
			//srcX = 0; // ToDo : あとで消す
			if( mDetY == 0 )
			{
				if( mDetX < 0 )			// 左
				{
					srcX = 0;
				}
				else if( mDetX > 0 )	// 右
				{
					srcX = 1;
				}
			}
			else if( mDetY < 0 )
			{
				srcX = 2;				// 上
			}
			else
			{
				srcX = 3;				// 下
			}
			break;
	}

	if( srcX != -1 && srcY != -1)
	{
		image->draw( detX, detY, srcX, srcY, OBJECT_SIZE, OBJECT_SIZE );
	}
}

// コリジョン判定
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