#include "PopupMessage.h"

PopupMessage::PopupMessage(String title, String message) :
		message_(message), title_(title) {
	isVisible_ = false;

	dia_ = new Dialog();
	lbMessage_ = new Label();
	lbMessage_->setText(message);

	createLayout();
	dia_->hide();
}

PopupMessage::~PopupMessage() {
	delete dia_;
	dia_ = NULL;

	delete lbMessage_;
	lbMessage_ = NULL;
}

void PopupMessage::show() {
	dia_->show();
}

void PopupMessage::hide() {
	dia_->hide();
}

void PopupMessage::setMessage(String message) {
	message_ = message;
	lbMessage_->setText(message);
}

void PopupMessage::setTitle(String title)
{
	title_ = title;
	dia_->setTitle(title_);
}

void PopupMessage::createLayout()
{
	dia_->setTitle(title_);

	VerticalLayout* vl = new VerticalLayout();
	vl->setScrollable(true);
	vl->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	Styler::setLayoutPadding(vl);

	lbMessage_->setText(message_);
	Styler::setLabelStyle(lbMessage_, LSPopupMessage);

	vl->addChild(lbMessage_);

	dia_->addChild(vl);
}



