#include "DxLib.h"
#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::mInstance = 0;

KeyboardManager::KeyboardManager() {}

KeyboardManager::~KeyboardManager() {}

// インスタンス作成
void KeyboardManager::create()
{
	if( !mInstance )
	{
		mInstance = new KeyboardManager();
	}
}

// インスタンス破棄
void KeyboardManager::destroy()
{
	if( mInstance )
	{
		delete mInstance;
		mInstance = 0;
	}
}

// インスタンス取得
KeyboardManager* KeyboardManager::instance()
{
	return mInstance;
}

// キーが押されているかをチェックする
bool KeyboardManager::isOn( int inputid )
{
	bool flag = false;
	updateKey();
	if( key[ inputid ] )
	{
		flag = true;
	}
	return flag;
}

// キーの更新
void KeyboardManager::updateKey()
{
	char stateKey[ 256 ];
	// キーの状態を取得
	GetHitKeyStateAll( stateKey );
	for( int i = 0; i < 256; i++ )
	{
		if( stateKey[ i ] != 0 )
		{ // キーが押されている
			key[ i ]++;
		}
		else
		{ // キーが押されていない
			key[ i ] = 0;
		}
	}
}