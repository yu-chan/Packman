#include "DxLib.h"
#include "SoundManager.h"

SoundManager* SoundManager::mInstance = 0;

SoundManager::SoundManager() : mBgm( 0 ), mSe( 0 ) {}

SoundManager::~SoundManager() {}

// �C���X�^���X�쐬
void SoundManager::create()
{
	if( !mInstance )
	{
		mInstance = new SoundManager();
	}
}

// �C���X�^���X�j��
void SoundManager::destroy()
{
	if( mInstance )
	{
		delete mInstance;
		mInstance = 0;
	}
}

// �C���X�^���X�擾
SoundManager* SoundManager::instance()
{
	return mInstance;
}

// BGM�����[�h
void SoundManager::loadBgm( const char* filename )
{
	mBgm = LoadSoundMem( filename );
}

// BGM�𗬂�
void SoundManager::playBgm()
{
	PlaySoundMem( mBgm, DX_PLAYTYPE_LOOP );
}

// BGM���~�߂�
void SoundManager::stopBgm()
{
	StopSoundMem( mBgm );
}

// BGM���폜
void SoundManager::deleteBgm()
{
	DeleteSoundMem( mBgm );
}

// BGM���`�F�b�N����
bool SoundManager::checkBgm() const
{
	return ( CheckSoundMem( mBgm ) == 1 ) ? true : false;
}