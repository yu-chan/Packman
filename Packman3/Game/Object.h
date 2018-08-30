#ifndef INCLUDED_GAME_OBJECT_H
#define INCLUDED_GAME_OBJECT_H

#include "Common.h"

class Image;

/*
** �p���p�N���X
** �L�����N�^�[��A�ǂȂǂ̕��̂ɗp����
*/
class Object
{
public:
	virtual ~Object() {}
	virtual void draw( const Image* ) const = 0;

	enum ObjectType
	{
		STATIC,
		DYANAMIC,
	};

	void setObjectType( const ObjectType objTyp )
	{
		mObjectType = objTyp;
	}

	void getPosition( int* x, int* y ) const
	{
		*x = mX;
		*y = mY;
	}

	int convertPixelToInner( const int pos ) const
	{
		return pos + OBJECT_HALF_SIZE;
	}
	int convertInnerToPixel( const int pos ) const
	{
		return pos - OBJECT_HALF_SIZE;
	}

protected:
	Image* mImage;
	ObjectType mObjectType;
	int mX;
	int mY;
};

#endif