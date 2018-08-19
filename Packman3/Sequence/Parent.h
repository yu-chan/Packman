#ifndef INCLUDED_SEQUENCE_PARENT_H
#define INCLUDED_SEQUENCE_PARENT_H

namespace Sequence {

class Child;

class Parent {
public:
	Parent();
	~Parent();

	enum NextSequence {
		NEXT_TITLE,
		NEXT_GAMEOVER,
		NEXT_ENDING,
		NEXT_GAME,

		NEXT_NONE
	};

	void update();	

	void moveToNextSequence(NextSequence);
	
	void deleteChild();

private:

	NextSequence mNextSequence;
	Child* mChild;
};

}

#endif