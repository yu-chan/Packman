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

// ‘JˆÚæ‚ÌŒˆ’è‚·‚é
void Parent::update()
{
	mChild->update( this );

	// Ÿ‚Ì‰æ–Ê‚É‘JˆÚ‚·‚é
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

	//ˆ—‚ğ‚µ‚Ä‚¨‚©‚È‚¢‚ÆAŸ‚Öi‚ß‚È‚¢
	mNextSequence = NEXT_NONE;
}

//‰æ–Ê‘JˆÚ‚ğXV
void Parent::moveToNextSequence( NextSequence next )
{
	mNextSequence = next;
}

//‰æ–Ê‘JˆÚ‚·‚éÛ‚ÉA¡‚Ì‰æ–Ê‚ğ”jŠü‚·‚é
void Parent::deleteChild()
{
	if( mChild )
	{
		delete mChild;
		mChild = 0;
	}
}

}