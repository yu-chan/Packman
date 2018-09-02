#include "DxLib.h"
#include "Common.h"
#include "Image.h"
#include "Game/Stage.h"
#include "Game/Character.h"
#include "Game/StaticObject.h"

/*
stageData : ステージ情報
size      : ステージサイズ 
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
	// ステージ情報
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

// ステージを初期化
void Stage::reset()
{
	// ステージのサイズを取得
	setSize();
	mStaticObjects = new StaticObject*[ mHeight ];
	for( int i = 0; i < mHeight; i++ )
	{
		mStaticObjects[ i ] = new StaticObject[ mWidth ];
	}


	// 一文字ずつ読み込み、その種類より配置するものを決めていく
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

	// キャラの初期化
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
読み込んだステージ情報の幅と高さを求める
stageData : ステージ情報
size      : ステージサイズ 
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
ステージ更新
*/
void Stage::update()
{
	// プレイヤーが死んでるなら、処理しない
	if( mCharacters[ 0 ].dead() )
	{
		isGameover = true;
		return;
	}

	// クリアしているなら、処理しない
	if( mCharacters[ 0 ].clear() )
	{
		isClear = true;
		return;
	}

	// キャラクタの更新
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		for( int j = i + 1; j < mCharactersNumber; j++ )
		{
			mCharacters[ i ].update( &mCharacters[ j ] );
		}
	}
}

/*
描画関数
*/
void Stage::draw() const
{
	// 動かない物体
	for( int y = 0; y < mHeight; y++ )
	{
		for( int x = 0; x < mWidth; x++ )
		{
			mStaticObjects[ y ][ x ].draw( mImage );
		}
	}

	// キャラ
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		mCharacters[ i ].draw( mImage );
	}
}

// クリアしてるかどうかを返す
bool Stage::clear()
{
	return isClear;
}

// ゲームオーバかどうかを返す
bool Stage::gameover()
{
	return isGameover;
}