#include <time.h>
#include "Common.h"
#include "DxLib.h"
#include "File.h"
#include "Singleton\Framerate.h"
#include "Singleton\KeyboardManager.h"
#include "Singleton\SoundManager.h"
//#include "Sequence/Parent.h"


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	ChangeWindowMode( TRUE );
	SetWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );

	if( DxLib_Init() == -1 ) {
		OutputDebugString( "DxLib_Init()‚ÌŽ¸”s\n" );
		return 1;
	}

	SetDrawScreen( DX_SCREEN_BACK );

	srand( ( unsigned )time( NULL ) );

	if( !KeyboardManager::instance() ) {
		KeyboardManager::create();
	}
	if( !Framerate::instance() ) {
		Framerate::create();
	}
	if( !SoundManager::instance() ) {
		SoundManager::create();
	}
	/*if(!Sequence::Parent::instance()) {
		Sequence::Parent::create();
	}*/

	while( !KeyboardManager::instance()->isOn( KEY_INPUT_Q ) ) { //Q‚ð‰Ÿ‚µ‚½‚çI—¹
		if( ProcessMessage() != 0 ) {
			break;
		}
		KeyboardManager::instance()->updateKey();
		ClearDrawScreen();

		//ƒQ[ƒ€ƒƒCƒ“
		//Sequence::Parent::instance()->update();

		ScreenFlip();
		Framerate::instance()->tick();
	}

	//Sequence::Parent::destroy();
	SoundManager::destroy();
	Framerate::destroy();
	KeyboardManager::destroy();
	DxLib_End();

	return 0;
}