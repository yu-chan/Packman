#include "DxLib.h"
#include "Image.h"
#include "Game/Character.h"
#include "Game/StaticObject.h"
#include "Singleton/SoundManager.h"
#include "Singleton/KeyboardManager.h"

Character::Character() : 
mCharacterType( CHARACTERTYPE_NONE ),
mDetX( 0 ),
mDetY( 0 ),
mCnt( 0 ),
mStaticCollisionCnt( 0 ),
isClear( false ),
isDetRight( true ),
isDetUp( false )
{
}

Character::~Character() {}

// �L�����N�^�[��������
void Character::setCharacter( int x, int y, CharacterType characterTyp )
{
	set( x, y,  DYNAMIC );
	mCharacterType = characterTyp;
}

/*
�v���C���[��p
*/
void Character::setDet( int detX, int detY )
{
	mDetX = detX;
	mDetY = detY;
}

/*
�G��p
�������������߂�
*/
void Character::setRandomDet()
{
	double rnd = rand();
	//X���������߂�
	if( rnd < 0.5 )
	{
		mDetX = -1;
	}
	else
	{
		mDetX = 1;
	}

	rnd = rand();
	//Y���������߂�
	if( rnd < 0.5 )
	{
		mDetY = -1;
	}
	else
	{
		mDetY = 1;
	}
}

//�L�����̕����X�s�[�h���擾
void Character::getDet( int* detX, int* detY )
{
	*detX = mDetX;
	*detY = mDetY;
}

// �L�����̃^�C�v���擾
unsigned Character::type() const
{
	return mCharacterType;
}

//�L�����N�^�[���J�E���g����
void Character::count()
{
	if( mCnt == FPS )
	{
		mCnt = 0;
	}
	mCnt++;
}

// �L�����̓������X�V
void Character::update( Object* obj )
{
	if( !dead() ) {
		if( isPlayer() ) {
			playerMove( obj );
		} else if( isEnemy() ) {
			enemyMove( obj );
		}
		mCnt++;
	}
}

void Character::update()
{
	if( !dead() ) {
		move();
		mCnt++;
	}
}

/*
�v���C���[��p
�v���C���[�𑀍삷��
*/
void Character::playerMove( Object* obj )
{
	// �������L�[�ɂ�蓮�����������߂�
	if( KeyboardManager::instance()->isOn( KEY_INPUT_RIGHT ) )
	{ // �E���L�[�������Ă���
		isDetRight = true;
		mDetX = 1;
		mDetY = 0;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_LEFT ) )
	{ // �����L�[�������Ă���
		isDetRight = false;
		mDetX = -1;
		mDetY = 0;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_UP ) )
	{ // ����L�[�������Ă���
		isDetUp = true;
		mDetX = 0;
		mDetY = -1;
	}
	else if( KeyboardManager::instance()->isOn( KEY_INPUT_DOWN ) )
	{ // �����L�[�������Ă���
		isDetUp = false;
		mDetX = 0;
		mDetY = 1;
	}

	//�ړ���̍��W
	int movedX = mX + mDetX;
	int movedY = mY + mDetY;
	//�ړ������ۂɃI�u�W�F�N�g�ɂ������Ă��邩�ǂ���
	bool hitX = false, hitY = false;
	if( obj->objectType() == STATIC )
	{
	}
	else if( obj->objectType() == DYNAMIC )
	{
		// X�����ɑ΂���
		if( collisionDetectionToObject( movedX, mY, obj ) )
		{
			hitX = true;
		}
		// Y�����ɑ΂���
		if( collisionDetectionToObject( mY, movedY, obj ) )
		{
			hitY = true;
		}
	}
	//�����Ȃ����̂Ƃ̏Փ˔���
	//for( int y = 0; y < 3; y++ )
	//{
	//	for( int x = 0; x < 3; x++ )
	//	{
	//		//�L����������}�X�Ȃ̂ŁA�������΂�
	//		if( x == 1 && y == 1 )
	//		{
	//			continue;
	//		}

	//		int tmpX = masX + mas[ y ][ x ][ 0 ];
	//		int tmpY = masY + mas[ y ][ x ][ 1 ];
	//		//X�����ɑ΂��āA���肷��
	//		if( collisionDetectionToObject( movedX, mY, obj ) )
	//		{
	//			hitX = true;

	//			//ObjectType��STATIC�̏ꍇ
	//			if( obj->objectType() == ObjectType::STATIC )
	//			{
	//				StaticObject* sObj = dynamic_cast< StaticObject* >( obj );

	//			}
	//			else if( obj->objectType() == ObjectType::DYANAMIC )
	//			{
	//			}
	//		}
	//		//Y�����ɑ΂��āA���肷��
	//		if( collisionDetectionToObject( mX, movedY, obj ) )
	//		{
	//			hitY = true;
	//		}
	//	}
	//}
	
	if( ( 0 < movedX && movedX < WINDOW_WIDTH ) && 
		( 0 < movedY && movedY < WINDOW_HEIGHT ) )
	{
			if( hitX && !hitY )
			{ //Y�����݈̂ړ��ł���
				mY = movedY;
			}
			else if( !hitX && hitY )
			{ //X�����݈̂ړ��ł���
				mX = movedX;
			}
			//else if(!hitX && !hitY) { //�������Ɉړ��ł���
			//	mX = movedX;
			//	mY = movedY;
			//}
	}
}

void Character::move()
{
	mX += mDetX;
	mY += mDetY;
}

/*
�G��p
�G�𓮂���
*/
void Character::enemyMove( Object* obj )
{
}

// �L����������ł��邩�ǂ�����Ԃ�
bool Character::dead() const
{
	return ( mCharacterType == CHARACTERTYPE_NONE );
}

// �N���A���Ă��邩�ǂ�����Ԃ�
bool Character::clear() const
{
	return isClear;
}

// �v���C���[�ł��邩��Ԃ�
bool Character::isPlayer() const
{
	return ( mCharacterType == CHARACTERTYPE_PLAYER );
}

// �I�ł��邩��Ԃ�
bool Character::isEnemy() const
{
	return ( mCharacterType == CHARACTERTYPE_ENEMY );
}

void Character::draw( const Image* image ) const
{
	if( dead() )
	{
		return;
	}
	
	//�摜�̍������ɕ`�悷��̂ŁA���S���獶��ɕϊ�
	int detX = convertInnerToPixel( mX );
	int detY = convertInnerToPixel( mY );

	/*
	�ꖇ�̉摜�ɂ�������̊G������̂ŁA�ǂ��`�������߂�K�v������
	10�J�E���g���ƂɃA�j���[�V����
	*/
	int srcX = -1;
	int srcY = -1;
	int tmpIndex = mCnt / ANIMATION_INTERVAL;
	switch ( mCharacterType )
	{
		case CHARACTERTYPE_PLAYER :
			if( tmpIndex % 2 == 0 )			// �ۂ��Ȃ�
			{
				srcX = 1;
				srcY = 0;
			}
			else							// �����J��
			{
				srcX = 0;
				if( mDetY == 0 )
				{
					if( mDetX > 0 )			// �E
					{
						srcY = 0;
					}
					else if( mDetX < 0 )	// ��
					{
						srcY = 1;
					}
				}
				else if( mDetY < 0 )
				{
					srcY = 2;				// ��
				}
				else
				{
					srcY = 3;				// ��
				}
			}
			break;
		case CHARACTERTYPE_ENEMY :
			srcY = 4;
			srcX = 0; // ToDo : ���Ƃŏ���
			if( mDetY == 0 )
			{
				if( mDetX < 0 )			// ��
				{
					srcX = 0;
				}
				else if( mDetX > 0 )	// �E
				{
					srcX = 1;
				}
			}
			else if( mDetY < 0 )
			{
				srcX = 2;				// ��
			}
			else
			{
				srcX = 3;				// ��
			}
			break;
	}

	if( srcX != -1 && srcY != -1)
	{
		image->draw( detX, detY, srcX, srcY, OBJECT_SIZE, OBJECT_SIZE );
	}
}

// �R���W��������
bool Character::collisionDetectionToObject( int movedX, int movedY, Object* obj ) const
{
	int objX, objY;
	obj->getPosition( &objX, &objY );

	
	int aLeft  = movedX - OBJECT_HALF_SIZE;
	int aRight = movedX + OBJECT_HALF_SIZE;
	int bLeft  =   objX - OBJECT_HALF_SIZE;
	int bRight =   objX + OBJECT_HALF_SIZE;
	if( ( aLeft < bRight ) && ( aRight > bLeft ) ) {
		int aTop    = movedY - OBJECT_HALF_SIZE;
		int aBottom = movedY + OBJECT_HALF_SIZE;
		int bTop    =   objY - OBJECT_HALF_SIZE;
		int bBottom =   objY + OBJECT_HALF_SIZE;
		if( ( aTop < bBottom ) && ( aBottom > bTop ) ) {
			return true;
		}
	}

	return false;
}

void Character::dieCharacter()
{
	mCharacterType = CHARACTERTYPE_NONE;
}