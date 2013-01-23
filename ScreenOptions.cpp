#include "ScreenOptions.h"

ScreenOptions::ScreenOptions(Screen* parent) :
	sParent(parent), done(false) {

	newLangId = Lang::getCurrLangId();
	newStyleId = Styler::getCurrStyleId();

	pmOptions = new PopupMenu(this);
	createUI();
}

ScreenOptions::~ScreenOptions() {
}

bool ScreenOptions::isDone() {
	return done;
}

void ScreenOptions::reset() {
	done = false;
}

void ScreenOptions::buttonClicked(Widget* button) {
	if(button == btnCancel){
		done = true;
		sParent->show();
	}else if(button == btnAccept){
		Lang::setCurrLangId(newLangId);
		Styler::setCurrStyleId(newStyleId);
		done = true;
		sParent->show();
	}else if (button == btnChangeLang){
		mMode = MM_LANG;
		pmOptions->setMenuTitle(Lang::getString(GS_LANGUAGESELECTTITLE));
		pmOptions->setMenuHelpMessage(Lang::getString(GS_LANGUAGESELECTMESSAGE));
		pmOptions->clearMenuItems();
		for(int ki = 0; ki < Lang::getLangsCount(); ki++){
			pmOptions->addMenuItem(Lang::getLangName(ki));
		}
		pmOptions->show();
		Environment::getEnvironment().addTimer(this, 1000, 0);
	}else if( button == btnChangeStyle){
		mMode = MM_STYLE;
		pmOptions->setMenuTitle(Lang::getString(GS_STYLESELECTTITLE));
		pmOptions->setMenuHelpMessage(Lang::getString(GS_STYLESELECTMESSAGE));
		pmOptions->clearMenuItems();
		for(int ki = 0; ki < Styles::getItemsCount(); ki++){
			pmOptions->addMenuItem(Styles::items[ki].name);
		}
		pmOptions->show();
		Environment::getEnvironment().addTimer(this, 1000, 0);
	}
}

void ScreenOptions::createUI() {
		//main layout
	vlMain = new VerticalLayout();
	vlMain->setScrollable(true);
	vlMain->setBackgroundColor(Styler::getClBgMessage());
	vlMain->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

		//title
	lbScreenTitle = new Label(Lang::getString(GS_OPTIONS));
	Styler::setLabelFont(lbScreenTitle, Styler::fontnameScreenTitle);
	Styler::setLabelStyle(lbScreenTitle, LSLevel1);
	vlMain->addChild(lbScreenTitle);
	Styler::addSeparator(vlMain, Styler::getSzPadding());

		//caption Language
	lbLanguage = new Label(Lang::getString(GS_LANGUAGE));
	lbLanguage->fillSpaceHorizontally();
	lbLanguage->wrapContentHorizontally();
	Styler::subLabel(lbLanguage);
	vlMain->addChild(lbLanguage);

		//current language
	lbCurrLang  = new Label(Lang::getCurrLangName());
	lbCurrLang->setFontSize(Styler::getSzFontSize1());
	lbCurrLang->fillSpaceHorizontally();
	lbCurrLang->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	lbCurrLang->wrapContentHorizontally();
	vlMain->addChild(lbCurrLang);

		//lang change button
	btnChangeLang = new Button();
	btnChangeLang->setText("    " + Lang::getString(GS_CHANGE) + "    ");
	btnChangeLang->addButtonListener(this);
	vlMain->addChild(btnChangeLang);

		//caption Style
	lbStyle = new Label(Lang::getString(GS_STYLE));
	lbStyle->fillSpaceHorizontally();
	lbStyle->wrapContentHorizontally();
	Styler::subLabel(lbStyle);
	vlMain->addChild(lbStyle);

		//current Style
	lbCurrStyle  = new Label(Styles::items[Styler::getCurrStyleId()].name);
	lbCurrStyle->setFontSize(Styler::getSzFontSize1());
	lbCurrStyle->fillSpaceHorizontally();
	lbCurrStyle->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	lbCurrStyle->wrapContentHorizontally();
	vlMain->addChild(lbCurrStyle);

	//lang change button
	btnChangeStyle = new Button();
	btnChangeStyle->setText("    " + Lang::getString(GS_CHANGE) + "    ");
	btnChangeStyle->addButtonListener(this);
	vlMain->addChild(btnChangeStyle);

		//controls at bottom
	hlButtons = new HorizontalLayout();
	Styler::setBottomCtrlLayoutStyle(hlButtons);

	btnAccept = new Button();
	btnAccept->setText(Lang::getString(GS_OK));
	btnAccept->addButtonListener(this);
	btnAccept->fillSpaceHorizontally();
	hlButtons->addChild(btnAccept);

	btnCancel = new Button();
	btnCancel->setText(Lang::getString(GS_CANCEL));
	btnCancel->addButtonListener(this);
	btnCancel->fillSpaceHorizontally();
	hlButtons->addChild(btnCancel);

	vlMain->addChild(hlButtons);

	setMainWidget(vlMain);
}

void ScreenOptions::runTimerEvent() {
	if(pmOptions->result != -1){
		switch (mMode){
		case MM_LANG:
			newLangId = pmOptions->result;
			lbCurrLang->setText(Lang::getLangName(newLangId));
			break;
		case MM_STYLE:
			newStyleId = pmOptions->result;
			lbCurrStyle->setText(Styles::items[newStyleId].name);
			break;
		}
		Environment::getEnvironment().removeTimer(this);
		pmOptions->reset();
	}
}
