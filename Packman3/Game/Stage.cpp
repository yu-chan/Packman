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
	delete[] mData;
	mData = 0;
	delete[] mCharacters;
	mCharacters = 0;
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
				x++;
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

	// プレイヤーの方向スピードをセット
	setPlayerDet();

	// コリジョン判定
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		int charaX, charaY;			// キャラ座標
		mCharacters[ i ].getPosition( &charaX, &charaY );
		int detX, detY;				// キャラの方向スピード
		mCharacters[ i ].getDet( &detX, &detY );
		int detMasX, detMasY;		// キャラのいるマスから1マス先にあるマス
		detMasX = detMasY = 0;
		if( detY == 0 )
		{
			if( detX > 0 )
			{
				detMasX = 1;		// 右マス
			}
			else if( detX < 0 )
			{
				detMasX = -1;		// 左マス
			}
		}
		else if( detY > 0 )
		{
			detMasY = 1;			// 下マス
		}
		else if( detY < 0 )
		{
			detMasY = -1;			// 上マス
		}

		int charaMasX = charaX / OBJECT_SIZE;
		int charaMasY = charaY / OBJECT_SIZE;
		int charaDetMasX = charaMasX + detMasX;
		int charaDetMasY = charaMasY + detMasY;
		int movedX = charaX + detX;	// 移動後のX座標
		int movedY = charaY + detY;	// 移動後のY座標

		bool hitWall = false;
		StaticObject* sObj = &mStaticObjects[ charaDetMasY ][ charaDetMasX ]; // 移動後のStaticObject
		// StaticObjectとのコリジョン判定
		if( sObj->flag() != StaticObject::FLAG_NONE ) // 移動先にStaticObjectがある
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
					// ToDo : 敵は方向転換
				}
			}
			else
			{
				//mCharacters[ i ].update();
			}
		}
		else // 移動先にStaticObjectがない
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

		// プレイヤーは常にスクリーンにいる必要がある
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
	Character同士のコリジョン判定のために、引数を渡す
	*/
	for( int i = 0; i < mCharactersNumber; i++ )
	{
		for( int j = i + 1; j < mCharactersNumber; j++ )
		{
			Character* chara = &mCharacters[ j ];

			// ToDo : キャラの更新
			//mCharacters[ i ].update( &mCharacters[ j ] );
			//mCharacters[ i ].update();
		}
	}
}

/*
キーボードの矢印キーの入力状態により、
プレイヤーの方向スピードを決める
*/
void Stage::setPlayerDet()
{
	int detX = 0;
	int detY = 0;
	// 押したキーにより動く方向を決める
	if( KeyboardManager::instance()->isOn( KEY_INPUT_RIGHT ) )
	{ // 右矢印キーを押している
		detX = 1;
		detY = 0;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_LEFT ) )
	{ // 左矢印キーを押している
		detX = -1;
		detY = 0;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_UP ) )
	{ // 上矢印キーを押している
		detX = 0;
		detY = -1;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_DOWN ) )
	{ // 下矢印キーを押している
		detX = 0;
		detY = 1;
	}

	mCharacters[ 0 ].setDet( detX, detY );
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