#include <math.h>
#include "DxLib.h"
#include "..\Common.h"
#include "Framerate.h"

Framerate* Framerate::mInstance = 0;

Framerate::Framerate() : mStartTime(0), mCnt(0) {}

Framerate::~Framerate() {}

// �C���X�^���X�쐬
void Framerate::create()
{
	if(!mInstance)
	{
		mInstance = new Framerate();
	}
}

// �C���X�^���X�j��
void Framerate::destroy()
{
	if( mInstance )
	{
		delete mInstance;
		mInstance = 0;
	}
}

// �C���X�^���X�擾
Framerate* Framerate::instance()
{
	return mInstance;
}

// �t���[���𐧌䂷��
void Framerate::tick()
{
	// ���߂�ꂽ�t���[���ɂȂ�����A0�ɖ߂�
	if( ( mCnt % FPS ) == 0 )
	{
		mStartTime = GetNowCount();
		mCnt = 0;
	}
	else
	{
		int expectedElapsedTime = mCnt * ( 1000 / FPS );
		int elapsedTime = GetNowCount() - mStartTime;
		int restTime = expectedElapsedTime - elapsedTime;
		//�K��̃t���[�����[�g���i��ł���̂Ȃ�A���̕��������Ԃ�҂�
		if( restTime > 0 )
		{
			Sleep( restTime );
		}
	}
	mCnt++;
}
