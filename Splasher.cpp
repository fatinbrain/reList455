#include "Splasher.h"

Splasher::Splasher() {
	createUI();
}

Splasher::~Splasher() {
}

void Splasher::createUI() {
	vlMain = new VerticalLayout;
	vlMain->setBackgroundColor(0xcccccc);
	vlMain->fillSpaceHorizontally();
	vlMain->fillSpaceVertically();

	imgSplash = new Image();
	imgSplash->setScaleMode(IMAGE_SCALE_PRESERVE_ASPECT);
	imgSplash->fillSpaceHorizontally();
	imgSplash->fillSpaceVertically();
	imgSplash->setImage(LOGO);
	vlMain->addChild(imgSplash);

	setMainWidget(vlMain);
}
