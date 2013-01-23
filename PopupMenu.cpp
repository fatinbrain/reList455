#include "PopupMenu.h"

PopupMenu::PopupMenu(Screen* screen, String helpMessage, String menuTitle) :
		parentScreen(screen), result(-1) {
	createUI();
	dlg->setTitle(menuTitle);
	lb->setText(helpMessage);
}

PopupMenu::~PopupMenu() {
}

void PopupMenu::show() {
	createMenuButtons();
	result = -1;
	dlg->show();
}

void PopupMenu::hide() {
	dlg->hide();
}

void PopupMenu::addMenuItem(String menuItemName) {
	menuItemNames.add(menuItemName);
}

void PopupMenu::createUI() {
	dlg = new Dialog();
	dlg->setTitle("popup menu");
	vl = new VerticalLayout();
	vl->fillSpaceHorizontally();
	vl->fillSpaceVertically();
	vl->setScrollable(true);
	Styler::setLayoutPadding(vl);

	lb = new Label("lb");
	lb->setFontSize(Styler::getSzFontSize2());
	lb->fillSpaceHorizontally();
	lb->wrapContentHorizontally();
	vl->addChild(lb);

	vlButt = new VerticalLayout();
	Styler::setLayoutPadding(vlButt, 10);
	vl->addChild(vlButt);

	dlg->setMainWidget(vl);
}

void PopupMenu::setMenuHelpMessage(String helpMessage, int justification) {
	lb->setText(helpMessage);
	switch (justification) {
	case 1:
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_RIGHT);
		break;
	case 0:
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		break;
	default:
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
		break;
	}
}

void PopupMenu::setMenuTitle(String menuTitle) {
	dlg->setTitle(menuTitle);
}

void PopupMenu::clearMenuItems() {
	menuItemNames.clear();
}

void PopupMenu::reset() {
	result = -1;
}

void PopupMenu::buttonClicked(Widget *button) {
	Button* b = static_cast<Button*>(button);
	result = getButtonIndexByName(b);

	ASSERT_MSG(parentScreen != NULL, "menu's parent screen is NULL");
	this->hide();
	parentScreen->show();
}

void PopupMenu::createMenuButtons() {
	Button* b;
	while (vlButt->countChildWidgets() != 0) {
		b = static_cast<Button*>(vlButt->getChild(0));vlButt->removeChild(vlButt->getChild(0));
		if(b != NULL){
			delete b;
		}
	}

	for (int i = 0; i < menuItemNames.size(); i++) {
		Button* b = new Button();
		b->setText(menuItemNames[i]);
		b->fillSpaceHorizontally();
		b->addButtonListener(this);
		if(menuItemNames[i].length() == 0){
			b->setVisible(false);
		}
		vlButt->addChild(b);
	}
}

int PopupMenu::getButtonIndexByName(Button *button) {
	int ret = -1;
	String buttonText = button->getText();

	for (int i = 0; i < menuItemNames.size(); i++) {
		if (buttonText == menuItemNames[i]) {
			return i;
		}
	}

	return ret;
}
