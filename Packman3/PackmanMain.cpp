#include <time.h>
#include "Common.h"
#include "DxLib.h"
#include "File.h"
#include "Singleton\Framerate.h"
#include "Singleton\KeyboardManager.h"
#include "Singleton\SoundManager.h"
#include "Sequence/Parent.h"


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	//ウィンドウモードにする
	ChangeWindowMode( TRUE );

	SetWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );

	//DXライブラリを使用可能な状態にする
	if( DxLib_Init() == -1 ) {
		OutputDebugString( "DxLib_Init()の失敗\n" );
		return 1;
	}

	/*
	** 裏画面に描画する
	** これを設定することで、描画処理で画面のちらつきが見えないようにする
	*/
	SetDrawScreen( DX_SCREEN_BACK );

	srand( static_cast< unsigned >( time( NULL ) ) );

	//シングルトンの作成
	if( !KeyboardManager::instance() ) {
		KeyboardManager::create();
	}
	if( !Framerate::instance() ) {
		Framerate::create();
	}
	if( !SoundManager::instance() ) {
		SoundManager::create();
	}

	//シーケンス制御するインスタンス作成
	Sequence::Parent* parent = new Sequence::Parent();

	while( !KeyboardManager::instance()->isOn( KEY_INPUT_Q ) ) { //Qを押したら終了
		if( ProcessMessage() != 0 ) {
			OutputDebugString( "ProcessMessageでエラーが起きた\n" );
			break;
		}
		KeyboardManager::instance()->updateKey();

		//画面に描画されているものをすべてクリアにする
		ClearDrawScreen();

		//ゲームメイン
		parent->update();

		/*
		** 裏画面に描画した内容を表画面に反映
		** これで、画像が動いているように見えるようになる
		*/
		ScreenFlip();

		Framerate::instance()->tick();
	}

	//Sequence::Parent::destroy();
	//シングルトンの破棄
	SoundManager::destroy();
	Framerate::destroy();
	KeyboardManager::destroy();

	//DXライブラリの使用を終了する
	DxLib_End();

	return 0;
}