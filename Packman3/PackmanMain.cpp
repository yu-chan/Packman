#include <time.h>
#include "Common.h"
#include "DxLib.h"
#include "File.h"
#include "Singleton\Framerate.h"
#include "Singleton\KeyboardManager.h"
#include "Singleton\SoundManager.h"
#include "Sequence/Parent.h"


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	//�E�B���h�E���[�h�ɂ���
	ChangeWindowMode( TRUE );

	SetWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );

	//DX���C�u�������g�p�\�ȏ�Ԃɂ���
	if( DxLib_Init() == -1 ) {
		OutputDebugString( "DxLib_Init()�̎��s\n" );
		return 1;
	}

	/*
	** ����ʂɕ`�悷��
	** �����ݒ肷�邱�ƂŁA�`�揈���ŉ�ʂ̂�����������Ȃ��悤�ɂ���
	*/
	SetDrawScreen( DX_SCREEN_BACK );

	srand( static_cast< unsigned >( time( NULL ) ) );

	//�V���O���g���̍쐬
	if( !KeyboardManager::instance() ) {
		KeyboardManager::create();
	}
	if( !Framerate::instance() ) {
		Framerate::create();
	}
	if( !SoundManager::instance() ) {
		SoundManager::create();
	}

	//�V�[�P���X���䂷��C���X�^���X�쐬
	Sequence::Parent* parent = new Sequence::Parent();

	while( !KeyboardManager::instance()->isOn( KEY_INPUT_Q ) ) { //Q����������I��
		if( ProcessMessage() != 0 ) {
			OutputDebugString( "ProcessMessage�ŃG���[���N����\n" );
			break;
		}
		KeyboardManager::instance()->updateKey();

		//��ʂɕ`�悳��Ă�����̂����ׂăN���A�ɂ���
		ClearDrawScreen();

		//�Q�[�����C��
		parent->update();

		/*
		** ����ʂɕ`�悵�����e��\��ʂɔ��f
		** ����ŁA�摜�������Ă���悤�Ɍ�����悤�ɂȂ�
		*/
		ScreenFlip();

		Framerate::instance()->tick();
	}

	//Sequence::Parent::destroy();
	//�V���O���g���̔j��
	SoundManager::destroy();
	Framerate::destroy();
	KeyboardManager::destroy();

	//DX���C�u�����̎g�p���I������
	DxLib_End();

	return 0;
}