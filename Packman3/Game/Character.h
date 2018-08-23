#ifndef INCLUDED_GAME_CHARACTER_H
#define INCLUDED_GAME_CHARACTER_H

#include "Game/Object.h"

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
	void setRandomDet();
	void update( const Object* );

	
	void playerMove( const Object* );
	void enemyMove( const Object* );
	
	bool isDead() const;
	bool isPlayer() const;
	bool isEnemy() const;

	void draw( const Image* ) const;

private:
	CharacterType mCharacterType;
	int mDetX;
	int mDetY;
	int mCnt;
	bool isClear;
};

#endif