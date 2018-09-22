#ifndef INCLUDED_GAME_CHARACTER_H
#define INCLUDED_GAME_CHARACTER_H

#include "Game/Object.h"

class StaticObject;

class Character : public Object
{
public:
	Character();
	~Character();

	enum CharacterType {
		CHARACTERTYPE_PLAYER,
		CHARACTERTYPE_ENEMY,
		
		CHARACTERTYPE_NONE,
	};

	void setCharacter( int, int , CharacterType );
	void setDet( int, int );
	void setRandomDet();
	void getDet( int*, int* );

	unsigned type() const;
	void count();
	
	void update();
	void move();
	
	bool dead() const;
	bool clear() const;
	bool isPlayer() const;
	bool isEnemy() const;

	void draw( const Image* ) const;

	bool collisionDetectionToObject( int, int, Object* ) const;

	void dieCharacter();

private:
	CharacterType mCharacterType;
	int mDetX;
	int mDetY;
	int mCnt;
	int mImageSrc;
	bool isClear;
};

#endif