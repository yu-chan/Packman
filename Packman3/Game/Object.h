#ifndef INCLUDED_GAME_OBJECT_H
#define INCLUDED_GAME_OBJECT_H

#include "Common.h"

class Image;

/*
** 継承用クラス
** キャラクターや、壁などの物体に用いる
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

	void set( int x, int y, const ObjectType objTyp )
	{
		setPosition( x, y );
		mObjectType = objTyp;
	}

	void setPosition( int x, int y )
	{
		mX = convertPixelToInner( x );
		mY = convertPixelToInner( y );
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