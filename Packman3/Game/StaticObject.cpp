#include "DxLib.h"
#include "Image.h"
#include "Game/Character.h"
#include "Game/StaticObject.h"

StaticObject::StaticObject() :
mFlag( 0 ),
mX( 0 ),
mY( 0 )
{
}

StaticObject::~StaticObject() {}

// �}�X�̎�ނ��`�F�b�N
bool StaticObject::checkFlag( unsigned flag ) const
{
	return ( mFlag & flag ) ? true : false;
}

// �}�X���Z�b�g
void StaticObject::setFlag( unsigned flag )
{
	mFlag |= flag;
}

// �}�X�����Z�b�g
void StaticObject::resetFlag( unsigned flag )
{
	mFlag &= ~flag;
}

// �}�X�̃t���O��Ԃ�
unsigned StaticObject::flag() const
{
	return mFlag;
}

// �}�X��������
void StaticObject::setStaticObject( int x, int y, unsigned flag )
{
	set( x, y, STATIC );
	setFlag( flag );
}

void StaticObject::draw( const Image* image ) const
{
	//�摜�̍������ɕ`�悷��̂ŁA���S���獶��ɕϊ�
	int detX = convertInnerToPixel( mX );
	int detY = convertInnerToPixel( mY );

	int srcX = -1;
	int srcY = -1;
	switch( mFlag )
	{
		case FLAG_WALL :
			//ToDo : �摜��p�ӂ���
			break;
		case FLAG_FEED :
			//ToDo : �摜��p�ӂ���
			break;
		case FLAG_INVINCIBLE :
			//ToDo : �摜��p�ӂ���
			break;
	}

	if( srcX != -1 && srcY != -1 && mFlag != FLAG_NONE )
	{
		if( !(detX + OBJECT_SIZE < 0 || WINDOW_WIDTH < detX) )
		{
			image->draw( detX, detY, srcX, srcY, OBJECT_SIZE, OBJECT_SIZE );
		}
	}
}