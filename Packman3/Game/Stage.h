#ifndef INCLUDED_GAME_STGE_H
#define INCLUDED_GAME_STGE_H

class Image;
class Character;

class Stage
{
public:
	Stage( const char* stageData, const int size );
	~Stage();

	void reset();
	void setSize();

	void update();

	void draw() const;

	bool clear();
	bool gameover();

private:
	Image* mImage;
	char* mData;
	int mSize;
	int mWidth;
	int mHeight;
	Character* mCharacters;
	int mCharactersNumber;
	bool isClear;
	bool isGameover;
};

#endif