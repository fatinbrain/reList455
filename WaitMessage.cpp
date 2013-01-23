#include "WaitMessage.h"

WaitMessage::WaitMessage(String title, String message) :
		message_(message), title_(title) {
	isVisible_ = false;

	dia_ = new Dialog();
	lbMessage_ = new Label();
	lbMessage_->setText(message);
	ai_ = new ActivityIndicator();

	createLayout();
	dia_->hide();
}

WaitMessage::~WaitMessage() {
	delete dia_;
	dia_ = NULL;

	delete lbMessage_;
	lbMessage_ = NULL;

	delete ai_;
	ai_ = NULL;
}

void WaitMessage::show() {
	dia_->show();
	ai_->show();
}

void WaitMessage::hide() {
	dia_->hide();
	ai_->hide();
}

void WaitMessage::setMessage(String message) {
	message_ = message;
	lbMessage_->setText(message);
}

void WaitMessage::setTitle(String title)
{
	title_ = title;
	dia_->setTitle(title_);
}

void WaitMessage::createLayout()
{
	dia_->setTitle(title_);

	VerticalLayout* vl = new VerticalLayout();
	vl->setScrollable(true);
	vl->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	Styler::setLayoutPadding(vl);

	lbMessage_->setText(message_);
	Styler::setLabelStyle(lbMessage_, LSPopupMessage);

	HorizontalLayout* vlAi = new HorizontalLayout();
	Styler::setLayoutPadding(vlAi);
	vlAi->setScrollable(true);
	vlAi->fillSpaceHorizontally();
	vlAi->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	vlAi->addChild(ai_);

	vl->addChild(vlAi);
	vl->addChild(lbMessage_);

	dia_->addChild(vl);
}



