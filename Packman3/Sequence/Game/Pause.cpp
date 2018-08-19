#include "Image.h"
#include "Singleton/KeyboardManager.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Pause.h"

namespace Sequence {
namespace Game {

Pause::Pause() : mImage(0) {
}

Pause::~Pause() {
	delete mImage;
	mImage = 0;
}

void Pause::update(Parent* parent) {
}

}
}