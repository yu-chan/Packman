#include "DxLib.h"
#include "Image.h"
#include "Singleton/KeyboardManager.h"
#include "Sequence/Parent.h"
#include "Sequence/Ending.h"

namespace Sequence {

Ending::Ending() : mImage(0) {
	mImage = new Image("data/image/ending.png");
}

Ending::~Ending() {
	delete mImage;
	mImage = 0;
}

void Ending::update(Parent* parent) {
	if(KeyboardManager::instance()->isOn(KEY_INPUT_SPACE)) {
		//TODO:���艹
		parent->moveToNextSequence(Parent::NEXT_TITLE);
	}

	mImage->draw();
}

}