#ifndef INCLUDED_FRAMERATE_H
#define INCLUDED_FRAMERATE_H

class Framerate {
public:
	static void create();
	static void destroy();
	static Framerate* instance();

	void tick();


private:
	Framerate();
	~Framerate();
	static Framerate* mInstance;
	
	int mStartTime;
	int mCnt;
};

#endif