#include "DxLib.h"
#include "Image.h"
#include "Game/Character.h"
#include "Game/StaticObject.h"

StaticObject::StaticObject() :
mFlag( 0 ),
mX( 0 ),
mY( 0 )
{
}

StaticObject::~StaticObject() {}

//マスの種類をチェック
bool StaticObject::checkFlag( unsigned flag ) const
{
	return ( mFlag & flag ) ? true : false;
}

//マスをセット
void StaticObject::setFlag( unsigned flag )
{
	mFlag |= flag;
}

//マスをリセット
void StaticObject::resetFlag( unsigned flag )
{
	mFlag &= ~flag;
}

unsigned StaticObject::flag() const
{
	return mFlag;
}

void StaticObject::set( int x, int y, unsigned flag )
{
	setPosition( x, y );
	setFlag( flag );
}

void StaticObject::setPosition( int x, int y )
{
	//左端から中心座標へ変換
	mX = convertPixelToInner( x );
	mY = convertPixelToInner( y );
}

void StaticObject::draw( const Image* image ) const
{
	//画像の左上を基準に描画するので、中心から左上に変換
	int detX = convertInnerToPixel( mX );
	int detY = convertInnerToPixel( mY );

	int srcX = -1;
	int srcY = -1;
	switch( mFlag )
	{
		case FLAG_WALL :
			//ToDo : 画像を用意する
			break;
		case FLAG_FEED :
			//ToDo : 画像を用意する
			break;
		case FLAG_INVINCIBLE :
			//ToDo : 画像を用意する
			break;
	}

	if( srcX != -1 && srcY != -1 && mFlag != FLAG_NONE )
	{
		if( !(detX + OBJECT_SIZE < 0 || WINDOW_WIDTH < detX) )
		{
			image->draw( detX, detY, srcX, srcY, OBJECT_SIZE, OBJECT_SIZE );
		}
	}
}