#ifndef INCLUDED_GAME_STATICOBJECT_H
#define INCLUDED_GAME_STATICOBJECT_H

#include "Game/Object.h"

class Character;

class StaticObject : public Object
{
public:
	StaticObject();
	~StaticObject();

	//マスの種類
	enum Mas
	{
		FLAG_NONE		= 0,
		FLAG_WALL		= ( 1 << 0 ),
		FLAG_FEED		= ( 1 << 1 ),
		FLAG_INVINCIBLE = ( 1 << 2 )
	};

	bool checkFlag( unsigned ) const;
	void setFlag( unsigned );
	void resetFlag( unsigned );
	unsigned flag() const;

	void setStaticObject( int, int, unsigned );

	void draw( const Image* ) const;
		
private:
	unsigned mFlag;
	//int mX;
	//int mY;
};

#endif