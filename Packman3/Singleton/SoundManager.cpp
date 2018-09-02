#include "DxLib.h"
#include "SoundManager.h"

SoundManager* SoundManager::mInstance = 0;

SoundManager::SoundManager() : mBgm( 0 ), mSe( 0 ) {}

SoundManager::~SoundManager() {}

// インスタンス作成
void SoundManager::create()
{
	if( !mInstance )
	{
		mInstance = new SoundManager();
	}
}

// インスタンス破棄
void SoundManager::destroy()
{
	if( mInstance )
	{
		delete mInstance;
		mInstance = 0;
	}
}

// インスタンス取得
SoundManager* SoundManager::instance()
{
	return mInstance;
}

// BGMをロード
void SoundManager::loadBgm( const char* filename )
{
	mBgm = LoadSoundMem( filename );
}

// BGMを流す
void SoundManager::playBgm()
{
	PlaySoundMem( mBgm, DX_PLAYTYPE_LOOP );
}

// BGMを止める
void SoundManager::stopBgm()
{
	StopSoundMem( mBgm );
}

// BGMを削除
void SoundManager::deleteBgm()
{
	DeleteSoundMem( mBgm );
}

// BGMをチェックする
bool SoundManager::checkBgm() const
{
	return ( CheckSoundMem( mBgm ) == 1 ) ? true : false;
}