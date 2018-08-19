#ifndef INCLUDED_GAME_STGE_H
#define INCLUDED_GAME_STGE_H

class Image;

class Stage {
public:
	Stage( const char* stageData, const int size );
	~Stage();

	void reset();
	void setSize( const char* stageData, const int size );

	void update();

	void draw() const;

	bool clear();
	bool gameover();

private:
	Image* mImage;
	char* mData;
	int mWidth;
	int mHeight;
	bool isClear;
	bool isGameover;
};

#endif