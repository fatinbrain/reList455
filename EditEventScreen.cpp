#include "EditEventScreen.h"

EditEventScreen::EditEventScreen(Screen* parent, Event& e) :
		Screen(), _event(e), done(false) {
	sParent = parent;
	screenAddEventPeriod = new AddEventPeriod(this);

	createUI();
}

EditEventScreen::EditEventScreen(Screen *parent) :
		Screen(), done(false) {
	sParent = parent;
	screenAddEventPeriod = new AddEventPeriod(this);
	createUI();
}

EditEventScreen::~EditEventScreen() {
}

void EditEventScreen::grabScreenInfoToInternalEvent() {
	_event.Name = ebName->getText();
	_event.setDate(dpDate->getYear(), dpDate->getMonth(),
			dpDate->getDayOfMonth());
}

void EditEventScreen::buttonClicked(Widget *button) {
	if (button == bCancel) {
		sParent->show();
	} else if (button == btnEditPeriods) {
		Environment::getEnvironment().addTimer(this, 1000, 0);
		screenAddEventPeriod->preShow();
		screenAddEventPeriod->show();
	} else if (button == bOk) {
		done = true;
		grabScreenInfoToInternalEvent();
		sParent->show();
	}
}

void EditEventScreen::editBoxReturn(EditBox *editBox) {
	setOkEnablity();
}


void EditEventScreen::resetPeriodLabel() {
	lbPeriods->setText(Lang::getString(GS_NOPERIODS));
}

void EditEventScreen::eventInfoToScreen() {
	//fill fields in case not empty event
	if (_event.Name != "") {
		ebName->setText(_event.Name);
		dpDate->setYear(_event.InitDate_st.Year);
		dpDate->setMonth(_event.InitDate_st.Month);
		dpDate->setDayOfMonth(_event.InitDate_st.Day);
		if (_event.periods.toString().length() > 1) {
			lbPeriods->setText(_event.periods.toString());
		} else {
			resetPeriodLabel();
		}
	} else {
		reset();
	}
}

void EditEventScreen::createUI() {
	vl = new VerticalLayout();
	vl->setScrollable(true);
	vl->wrapContentHorizontally();
	vl->wrapContentVertically();
	vl->setBackgroundColor(Styler::getClBgMessage());

	/**
	 * capital
	 */
	lb = new Label(Lang::getString(GS_EDITEVENTTITLE));
	Styler::setLabelFont(lb, Styler::fontnameScreenTitle);
	Styler::setLabelStyle(lb, LSLevel1);
	vl->addChild(lb);
	Styler::addSeparator(vl, Styler::getSzPadding());

	/**
	 * event name
	 */
	stName = new Label(Lang::getString(GS_EVENTNAME));
	Styler::subLabel(stName);
	vl->addChild(stName);

	ebName = new EditBox();
	ebName->fillSpaceHorizontally();
	ebName->addEditBoxListener(this);
	vl->addChild(ebName);

	/**
	 * event date
	 */
	stDate = new Label(Lang::getString(GS_EVENTDATE));
	Styler::subLabel(stDate);
	vl->addChild(stDate);

	dpDate = new DatePicker();
	dpDate->fillSpaceHorizontally();
	vl->addChild(dpDate);

	/**
	 * periods
	 */
	stPeriod = new Label(Lang::getString(GS_EVENTREPEATPERIOD));
	Styler::subLabel(stPeriod);
	vl->addChild(stPeriod);

	lbPeriods = new Label("");
	lbPeriods->setFontSize(Styler::getSzFontSize1());
	lbPeriods->fillSpaceHorizontally();
	lbPeriods->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	lbPeriods->wrapContentHorizontally();
	vl->addChild(lbPeriods);

	btnEditPeriods = new Button();
	btnEditPeriods->setText(Lang::getString(GS_ADDEVENTPERIOD));
	btnEditPeriods->addButtonListener(this);
	vl->addChild(btnEditPeriods);

	/**
	 * bottom buttons
	 */
	hlConfirm = new HorizontalLayout();
	Styler::setBottomCtrlLayoutStyle(hlConfirm);

	bCancel = new Button();
	bCancel->setText(Lang::getString(GS_CANCEL));
	bCancel->fillSpaceHorizontally();
	bCancel->addButtonListener(this);

	bOk = new Button();
	bOk->setText(Lang::getString(GS_OK));
	bOk->fillSpaceHorizontally();
	bOk->addButtonListener(this);
	bOk->setEnabled(false);

	hlConfirm->addChild(bOk);
	hlConfirm->addChild(bCancel);

	eventInfoToScreen();

	vl->addChild(hlConfirm);

	setMainWidget(vl);

	reset();
}

void EditEventScreen::editBoxEditingDidEnd(EditBox *editBox) {
	setOkEnablity();
}

Event EditEventScreen::getEvent() {
	return _event;
}

bool EditEventScreen::isDone() {
	return done;
}

void EditEventScreen::setEvent(Event & event) {
	_event = event;
	eventInfoToScreen();
}

void EditEventScreen::reset() {
	ebName->setText("");
	editRe();

	DateTime dt = DateTime::today();
	dpDate->setYear(dt.getYear() + 1900);
	dpDate->setMonth(dt.getMonth() + 1);
	dpDate->setDayOfMonth(dt.getDay());

	///not available for android platform in MoSync3.2
//	Date dtBuff(1, 1, 1902);
//	Date dtBuff(1, 1, 1910);
//	dpDate->setMinDate(dtBuff);
//	dtBuff.year = 2037;
//	dtBuff.year = 2030;
//	dpDate->setMaxDate(dtBuff);

	resetPeriodLabel();
	done = false;
	Styler::setLabelFont(lb, Styler::fontnameScreenTitle);
	screenAddEventPeriod->reset();
}

void EditEventScreen::editBoxTextChanged(EditBox *editBox,
		const MAUtil::String & text) {
	setOkEnablity();
}

void EditEventScreen::setOkEnablity() {
	bool okEnable = false;
	okEnable = (ebName->getText().length() > 0)
			&& (lbPeriods->getText().find("*") == String::npos);

	bOk->setEnabled(okEnable);
}

void EditEventScreen::datePickerValueChanged(DatePicker* datePicker,
		const struct Date& selectedDate) {
	setOkEnablity();
}


void EditEventScreen::editRe() {
	ebName->setVisible(false);
	ebName->setVisible(true);

	dpDate->setVisible(false);
	dpDate->setVisible(true);
}

void EditEventScreen::runTimerEvent() {
	if (screenAddEventPeriod->isDone()) {
		Environment::getEnvironment().removeTimer(this);
		screenAddEventPeriod->reset();
		Period periodBuff = screenAddEventPeriod->getResult();
		if (periodBuff.Factor > 0 && periodBuff.Letter != '\0') {
			_event.periods.add(periodBuff);
			lbPeriods->setText(_event.periods.toString());
		}
		setOkEnablity();
	}
}
