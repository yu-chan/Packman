#include "DxLib.h"
#include "Singleton/SoundManager.h"
#include "Sequence/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/GameOver.h"
#include "Sequence/Ending.h"
#include "Sequence/Game/Parent.h"

namespace Sequence {
	
Parent::Parent() :
mNextSequence( NEXT_NONE ),
mChild( 0 )
{
	mChild = new Title();
}

Parent::~Parent()
{
	deleteChild();
}

// �J�ڐ�̌��肷��
void Parent::update()
{
	mChild->update( this );

	// ���̉�ʂɑJ�ڂ���
	switch( mNextSequence )
	{
		case NEXT_TITLE:
			deleteChild();
			mChild = new Title();
			break;
		case NEXT_GAMEOVER:
			deleteChild();
			mChild = new GameOver();
			break;
		case NEXT_ENDING:
			deleteChild();
			mChild = new Ending();
			break;
		case NEXT_GAME:
			deleteChild();
			mChild = new Game::Parent();
			break;
	}

	//���������Ă����Ȃ��ƁA���֐i�߂Ȃ�
	mNextSequence = NEXT_NONE;
}

//��ʑJ�ڂ��X�V
void Parent::moveToNextSequence( NextSequence next )
{
	mNextSequence = next;
}

//��ʑJ�ڂ���ۂɁA���̉�ʂ�j������
void Parent::deleteChild()
{
	if( mChild )
	{
		delete mChild;
		mChild = 0;
	}
}

}