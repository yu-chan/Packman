#include "DxLib.h"
#include "Image.h"
#include "Game/Character.h"
#include "Singleton/SoundManager.h"

Character::Character() :  mCharacterType( CHARACTERTYPE_NONE ), mDetX( 0 ), mDetY( 0 ), isClear( 0 ) {
}

Character::Character() {
	
}

void Character::draw( const Image* image ) const {
}

void Character::set( int x, int y, CharacterType ) {
	mX = x;
	mY = y;
}

void Character::setRandomDet() {
}

void Character::update( const Object* obj ) {
	if( !isDead() ) {
		if( isPlayer() ) {
			playerMove( obj );
		} else if( isEnemy() ) {
			enemyMove( obj );
		}
	}
}

bool Character::isDead() const {
	return ( mCharacterType == CHARACTERTYPE_NONE );
}

bool Character::isPlayer() const {
	return ( mCharacterType == CHARACTERTYPE_PLAYER );
}

bool Character::isEnemy() const {
	return ( mCharacterType == CHARACTERTYPE_ENEMY );
}

void Character::playerMove( const Object* obj ) {
}

void Character::enemyMove( const Object* obj ) {
}