#ifndef INCLUDED_GAME_STGE_H
#define INCLUDED_GAME_STGE_H

class Image;
class StaticObject;
class Character;

class Stage
{
public:
	Stage( const char* stageData, const int size );
	~Stage();

	void reset();
	void setSize();

	void update();
	void setPlayerDet();

	void draw() const;

	bool clear();
	bool gameover();

private:
	Image* mImage;
	char* mData;
	int mSize;
	int mWidth;
	int mHeight;
	StaticObject** mStaticObjects;
	Character* mCharacters;
	int mCharactersNumber;
	bool isClear;
	bool isGameover;
};

#endif