#include <math.h>
#include "DxLib.h"
#include "..\Common.h"
#include "Framerate.h"

Framerate* Framerate::mInstance = 0;

Framerate::Framerate() : mStartTime(0), mCnt(0) {}

Framerate::~Framerate() {}

void Framerate::create() {
	if(!mInstance) {
		mInstance = new Framerate();
	}
}

void Framerate::destroy() {
	if( mInstance ) {
		delete mInstance;
		mInstance = 0;
	}
}

Framerate* Framerate::instance() {
	return mInstance;
}

//�t���[����i�߂�
void Framerate::tick() {
	if( ( mCnt % FPS ) == 0 ) {
		mStartTime = GetNowCount();
		mCnt = 0;
	} else {
		int expectedElapsedTime = mCnt * ( 1000 / FPS );
		int elapsedTime = GetNowCount() - mStartTime;
		int restTime = expectedElapsedTime - elapsedTime;
		//�K��̃t���[�����[�g���i��ł���̂Ȃ�A���̕��������Ԃ�҂�
		if( restTime > 0 ) {
			Sleep( restTime );
		}
	}
	mCnt++;
}
