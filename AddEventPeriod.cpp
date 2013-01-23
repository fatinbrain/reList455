#include "AddEventPeriod.h"

AddEventPeriod::AddEventPeriod(Screen *parent) :
		sParent(parent), done_(false) {

	resultPeriod_.Letter = '\0';
	resultPeriod_.Factor = 0;
	createUI();
}

AddEventPeriod::~AddEventPeriod() {
}

//Function to perform correct edit box keyboard show
void AddEventPeriod::preShow() {
	ebNum->setVisible(false);
	ebNum->setVisible(true);
	ebNum->showKeyboard();
}

void AddEventPeriod::buttonClicked(Widget *button) {
	if (button == bAdd) {
		if (lbCurrPeriod->getText() == Lang::getString(GS_YEARS)) {
			resultPeriod_.Letter = 'y';
		} else if (lbCurrPeriod->getText() == Lang::getString(GS_MONTHS)) {
			resultPeriod_.Letter = 'm';
		} else {
			resultPeriod_.Letter = 'y';
		}
		resultPeriod_.Factor = Convert::toInt(ebNum->getText().c_str());
		done_ = true;
		sParent->show();
	} else if (button == btnPeriodToggle) {
		if (lbCurrPeriod->getText() == Lang::getString(GS_YEARS)) {
			lbCurrPeriod->setText(Lang::getString(GS_MONTHS));
		} else {
			lbCurrPeriod->setText(Lang::getString(GS_YEARS));
		}
	}else if(button == bBack){
		resultPeriod_.Factor = -1;
		resultPeriod_.Letter = '\0';
		done_ = true;
		sParent->show();
	}else if(button == bm3){
		int val = Convert::toInt(ebNum->getText().c_str());
		val -= 3;
		if(val < 1){
			val = 1;
		}
		ebNum->setText(Convert::toString(val));
	}else if(button == bm1){
		int val = Convert::toInt(ebNum->getText().c_str());
		val -= 1;
		if(val < 1){
			val = 1;
		}
		ebNum->setText(Convert::toString(val));
	}else if(button == bp3){
		int val = Convert::toInt(ebNum->getText().c_str());
		val += 3;
		ebNum->setText(Convert::toString(val));
	}else if(button == bp1){
		int val = Convert::toInt(ebNum->getText().c_str());
		val += 1;
		ebNum->setText(Convert::toString(val));
	}
}

Period AddEventPeriod::getResult() {
	return resultPeriod_;
}

bool AddEventPeriod::isDone() {
	return done_;
}

void AddEventPeriod::reset() {
	ebNum->setText("1");
	lbCurrPeriod->setText(Lang::getString(GS_YEARS));
	preShow();
	done_ = false;
	Styler::setLabelFont(lb, Styler::fontnameScreenTitle);
}

void AddEventPeriod::createUI() {
	vl = new VerticalLayout();
	vl->setScrollable(true);
	vl->setBackgroundColor(Styler::getClBgMessage());
	vl->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

	lb = new Label(Lang::getString(GS_ADDEVENTPERIODTITLE));
	Styler::setLabelFont(lb, Styler::fontnameScreenTitle);
	Styler::setLabelStyle(lb, LSLevel1);
	vl->addChild(lb);
	Styler::addSeparator(vl, Styler::getSzPadding());

	/**
	 * period selector
	 */
	lbLetter = new Label(Lang::getString(GS_SELECTPERIOD));
	lbLetter->fillSpaceHorizontally();
	lbLetter->wrapContentHorizontally();
	Styler::subLabel(lbLetter);
	vl->addChild(lbLetter);

	VerticalLayout* hz = new VerticalLayout();
	hz->fillSpaceHorizontally();
	hz->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	lbCurrPeriod = new Label(Lang::getString(GS_YEARS));
	lbCurrPeriod->setFontSize(Styler::getSzFontSize1());
	lbCurrPeriod->fillSpaceHorizontally();
	lbCurrPeriod->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	lbCurrPeriod->wrapContentHorizontally();
	hz->addChild(lbCurrPeriod);
	btnPeriodToggle = new Button();
	btnPeriodToggle->setText(Lang::getString(GS_CHANGEPERIOD));
	btnPeriodToggle->addButtonListener(this);
	hz->addChild(btnPeriodToggle);
	vl->addChild(hz);

	lbFactor = new Label(Lang::getString(GS_SELECTPERIODCOUNT));
	lbFactor->fillSpaceHorizontally();
	lbFactor->wrapContentHorizontally();
	Styler::subLabel(lbFactor);
	vl->addChild(lbFactor);

	HorizontalLayout* hzebb = new HorizontalLayout();
	hzebb->fillSpaceHorizontally();
	hzebb->setScrollable(true);

	bm3 = new Button();
	bm3->setText(" -3 ");
	bm3->addButtonListener(this);
	hzebb->addChild(bm3);

	bm1 = new Button();
	bm1->setText(" -1 ");
	bm1->addButtonListener(this);
	hzebb->addChild(bm1);

	ebNum = new EditBox();
	ebNum->setText("1");
	ebNum->fillSpaceHorizontally();
	hzebb->addChild(ebNum);

	bp1 = new Button();
	bp1->setText(" +1 ");
	bp1->addButtonListener(this);
	hzebb->addChild(bp1);

	bp3 = new Button();
	bp3->setText(" +3 ");
	bp3->addButtonListener(this);
	hzebb->addChild(bp3);

	vl->addChild(hzebb);

	/**
	 * controls at bottom
	 */
	hlButtons = new HorizontalLayout();
	Styler::setBottomCtrlLayoutStyle(hlButtons);

	bAdd = new Button();
	bAdd->setText(Lang::getString(GS_ADD));
	bAdd->addButtonListener(this);
	bAdd->fillSpaceHorizontally();
	hlButtons->addChild(bAdd);

	bBack = new Button();
	bBack->setText(Lang::getString(GS_BACK));
	bBack->addButtonListener(this);
	bBack->fillSpaceHorizontally();
	hlButtons->addChild(bBack);

	vl->addChild(hlButtons);

	setMainWidget(vl);
}
