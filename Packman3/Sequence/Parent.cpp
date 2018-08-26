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

void Parent::update()
{
	mChild->update( this );

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

	//処理をしておかないと、次へ進めない
	mNextSequence = NEXT_NONE;
}

//画面遷移を更新
void Parent::moveToNextSequence( NextSequence next )
{
	mNextSequence = next;
}

//画面遷移する際に、今の画面を破棄する
void Parent::deleteChild()
{
	if( mChild )
	{
		delete mChild;
		mChild = 0;
	}
}

}