#ifndef INCLUDED_KEYBOARDMANAGER_H
#define INCLUDED_KEYBOARDMANAGER_H

class KeyboardManager
{
public:
	static void create();
	static void destroy();
	static KeyboardManager* instance();
	bool isOn( int inputId );
	void updateKey();

private:
	KeyboardManager();
	~KeyboardManager();
	static KeyboardManager* mInstance;

	int key[ 256 ]; // ÉLÅ[ÇÃéÌóﬁ
};

#endif