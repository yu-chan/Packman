#ifndef INCLUDED_GAME_CHARACTER_H
#define INCLUDED_GAME_CHARACTER_H

#include "Object.h"

class StaticObject;

class Character : public Object {
public:
	Character();
	~Character();

	enum CharacterType {
		CHARACTERTYPE_PLAYER,
		CHARACTERTYPE_ENEMY,
		
		CHARACTERTYPE_NONE,
	};

	void set( int, int , CharacterType );
	void setRandomDetX();
	void update( const Object* );
	void getPosition( int*, int* ) const;

	
	void playerMove( const Object* );

	void enemyMove( const Object* );

	void draw( const Image* ) const;

private:
	CharacterType mCharacterType;
	int mDetX;
	int mDetY;
	int mCnt;
	bool isClear;
};

#endif