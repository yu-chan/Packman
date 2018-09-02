#include "DxLib.h"
#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::mInstance = 0;

KeyboardManager::KeyboardManager() {}

KeyboardManager::~KeyboardManager() {}

// �C���X�^���X�쐬
void KeyboardManager::create()
{
	if( !mInstance )
	{
		mInstance = new KeyboardManager();
	}
}

// �C���X�^���X�j��
void KeyboardManager::destroy()
{
	if( mInstance )
	{
		delete mInstance;
		mInstance = 0;
	}
}

// �C���X�^���X�擾
KeyboardManager* KeyboardManager::instance()
{
	return mInstance;
}

// �L�[��������Ă��邩���`�F�b�N����
bool KeyboardManager::isOn( int inputid )
{
	bool flag = false;
	updateKey();
	if( key[ inputid ] )
	{
		flag = true;
	}
	return flag;
}

// �L�[�̍X�V
void KeyboardManager::updateKey()
{
	char stateKey[ 256 ];
	// �L�[�̏�Ԃ��擾
	GetHitKeyStateAll( stateKey );
	for( int i = 0; i < 256; i++ )
	{
		if( stateKey[ i ] != 0 )
		{ // �L�[��������Ă���
			key[ i ]++;
		}
		else
		{ // �L�[��������Ă��Ȃ�
			key[ i ] = 0;
		}
	}
}