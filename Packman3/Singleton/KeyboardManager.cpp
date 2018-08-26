#include "DxLib.h"
#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::mInstance = 0;

KeyboardManager::KeyboardManager() {}

KeyboardManager::~KeyboardManager() {}

void KeyboardManager::create()
{
	if( !mInstance )
	{
		mInstance = new KeyboardManager();
	}
}

void KeyboardManager::destroy()
{
	if( mInstance )
	{
		delete mInstance;
		mInstance = 0;
	}
}

KeyboardManager* KeyboardManager::instance()
{
	return mInstance;
}

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

void KeyboardManager::updateKey()
{
	char stateKey[ 256 ];
	GetHitKeyStateAll( stateKey );
	for( int i = 0; i < 256; i++ )
	{
		if( stateKey[ i ] != 0 )
		{
			key[ i ]++;
		}
		else
		{
			key[ i ] = 0;
		}
	}
}