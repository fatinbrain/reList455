#include "MainScreen.h"

MainScreen* mass;

void MainScreen::importFromSdcard() {
	String sBuff = readStringFromSdcard(imExFName);

	if(sBuff.length() > 10){
		eventsList.clear();
		eventsList.parse(sBuff);
		renderEventList();
	}
	dbgPopup->hide();
}

void MainScreen::exportToSdcard() {
	writeStringToSdcard(eventsList.toString(), imExFName);
}

void MainScreen::actScreenOptions() {
	screenOptions->show();
}

void MainScreen::readOptionsFormDevice() {
	StorageWorks sw(storeOptions);
	String sBuff = sw.read();

	if (sBuff != "") {
		options.parse(sBuff);
	}
}


void MainScreen::applyOptions() {
	Lang::setCurrLangId(options.getLangId());
	Styler::setCurrStyleId(options.getStyleId());
}

void MainScreen::actExit() {
	grabOptions();
	writeOptionsToDevice();
	writeEventListToStore();
}

void MainScreen::writeOptionsToDevice() {
	StorageWorks sw(storeOptions);
	sw.rm();
	sw.write(options.toString());
}

void MainScreen::grabOptions() {
	options.setLangId(Lang::getCurrLangId());
	options.setStyleId(Styler::getCurrStyleId());
}

void updateParseEventInfo(int controlCode, int argument) {
	switch (controlCode) {
	case -1:
		mass->popProgress->hide();
		break;
	case 0:
		mass->popProgress->setMessage(Lang::getString(GS_PARSING));
		mass->popProgress->setMaxVal(argument);
		mass->popProgress->show();
		break;
	case 1:
		mass->popProgress->setProgress(argument);
		break;
	default:
		break;
	}
}

MainScreen::MainScreen() :
		eventPeriodIndexTransmission(-1), editScreenMode(SEMInit) {

	readOptionsFormDevice();
	applyOptions();

	Styler::update();

	mass = this;

	screenOptions = new ScreenOptions(this);

	waitMsg = new WaitMessage();
	waitMsg->setTitle(Lang::getString(GS_WAIT));

	screenEditEvent = new EditEventScreen(this);

	dbgPopup = new PopupMessage();
	dbgPopup->setTitle(Lang::getString(GS_WAIT));

	popProgress = new PopupProgress(Lang::getString(GS_WAITPB));

	pmAlarmContextMenuClick = new PopupMenu(this);

	eventsList.regCallback(updateParseEventInfo);
	fontOverload();

	createUI();

	initLoad();
}

MainScreen::~MainScreen() {
	if (screenEditEvent != NULL) {
		delete screenEditEvent;
		screenEditEvent = NULL;
	}

	if (waitMsg != NULL) {
		delete waitMsg;
		waitMsg = NULL;
	}

	if (dbgPopup != NULL) {
		delete dbgPopup;
		dbgPopup = NULL;
	}

	if (pmAlarmContextMenuClick != NULL) {
		delete pmAlarmContextMenuClick;
		pmAlarmContextMenuClick = NULL;
	}
}

void MainScreen::createUI() {
	addOptionsMenuItem(Lang::getString(GS_NEWEVENT), NEW);
	addOptionsMenuItem(Lang::getString(GS_EXPORT), EXPORT);
	addOptionsMenuItem(Lang::getString(GS_IMPORT), IMPORT);
	addOptionsMenuItem(Lang::getString(GS_OPTIONS), OPTIONS);
	addOptionsMenuItem(Lang::getString(GS_EXIT), CLOSE);
//	addOptionsMenuItem("DeBug", DEBUG);

	addScreenListener(this);

	lMain = new VerticalLayout();
	lMain->fillSpaceHorizontally();
	lMain->fillSpaceVertically();

	String cap = "";
	cap += Lang::getString(GS_MAINTITLE);
	cap += VERSION;
	Label* lb = new Label(cap);

	Styler::setLabelFont(lb, Styler::fontnameScreenTitle);
	Styler::setLabelStyle(lb, LSLevel1);

	lMain->addChild(lb);

	lbTitleSplitter = new Label("");
	lbTitleSplitter->setHeight(5);
	lbTitleSplitter->fillSpaceHorizontally();
	lbTitleSplitter->setBackgroundGradient(Styler::getClLabelGradient1(),
			Styler::getClBgMessage());
	lMain->addChild(lbTitleSplitter);

	lvAlarms = new ListView();
	lvAlarms->addListViewListener(this);
	lvAlarms->setBackgroundColor(Styler::getClBgMessage());
	lMain->addChild(lvAlarms);

	setMainWidget(lMain);
}

void MainScreen::obtainEventsList() {
	waitMsg->setMessage(Lang::getString(GS_READDATA));
	waitMsg->show();
	StorageWorks sw(storeName);
	String sEvents = sw.read();

	eventsList.clear();
	if (sEvents == "") {
		createDefaultEventsList();
	} else {
		eventsList.parse(sEvents);
	}
}

void MainScreen::createDefaultEventsList() {
	Event e;

	e.periods.clear();
	e.set("New Year", 2013, 1, 1);
	e.addPeriod('y', 1);
	eventsList.add(e);

	e.periods.clear();
	e.set("Monthly event", 2001, 2, 5);
	e.addPeriod('m', 1);
	eventsList.add(e);

	e.periods.clear();
	e.set("Multi period event", 2004, 4, 6);
	e.addPeriod('y', 1);
	e.addPeriod('m', 5);
	eventsList.add(e);
}

void MainScreen::initLoad() {
	obtainEventsList();
	renderEventList();

	screenEditEvent->reset();
}

void MainScreen::generateAlarmMsgsFromEvents() {
	alarmsList.clear();

	AlarmMsg amBuff;

	int sz = eventsList.size();
	popProgress->setMessage(Lang::getString(GS_CREATEALARMSFROMEVENTS));
	popProgress->setMaxVal(sz);
	popProgress->show();
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < eventsList[i].periods.size(); j++) {
			popProgress->setProgress(i + 1);
			amBuff = generateAlarmMsg(eventsList[i], j);
			amBuff.EventIndex = i;
			amBuff.EventPeriodIndex = j;
			alarmsList.add(amBuff);
		}
	}
	popProgress->hide();
}

AlarmMsg MainScreen::generateAlarmMsg(Event e, int periodid) {
	AlarmMsg am;
	String s;
	int cnts;

	am.Name = e.Name;
	DaysTo_s dts;
	dts = grabDt(e.getEventDate(), e.periods[periodid]);
	if (e.getEventDate().getDay() != e.InitDate_st.Day) {
		dts.DaysTo++;
	}

	cnts = dts.FactorCount;
	s += Convert::toString(cnts);
	s += " x ";
	s += Convert::toString(e.periods[periodid].Factor);
	char xPeriod = e.periods[periodid].Letter;
	String sAdd = "";
	if (xPeriod == 'y') {
		sAdd += Lang::getString(GS_LETTERYEAR);
	} else if (xPeriod == 'm') {
		sAdd += Lang::getString(GS_LETTERMONTH);
	}
	s += sAdd;
	s += " ";
	s += Lang::getString(GS_SINCE);
	s += " ";
	s += Convert::toString(e.InitDate_st.Day, true);
	s += ".";
	s += Convert::toString(e.InitDate_st.Month, true);
	s += ".";
	s += Convert::toString(e.InitDate_st.Year);

	am.Message = s;
	am.DaysTo = dts.DaysTo;

	return am;
}

void MainScreen::renderAlarms() {
	clearListView(lvAlarms);

	int alarmListSize = alarmsList.size();
	float z = 0;
	popProgress->setMessage(Lang::getString(GS_RENDERALARM));
	popProgress->setMaxVal(alarmListSize);
	popProgress->show();
	for (int i = 0; i < alarmListSize; i++) {
		popProgress->setProgress(i + 1);
		z = i;
		z /= alarmListSize;
		renderAlarm(alarmsList[i], z);
	}
	popProgress->hide();
}

void MainScreen::clearListView(ListView *listView) {
	int chiCount = listView->countChildWidgets();
	for (int i = 0; i < chiCount; i++) {
		listView->removeChild((listView->getChild(0)));
	}
}

void MainScreen::fontOverload() {
	char x[128];
	int sz = maFontGetCount();
	popProgress->setMessage(Lang::getString(GS_FONTREFRESH));
	popProgress->setMaxVal(sz);
	popProgress->show();
	for (int i = 0; i < sz; i++) {
		maFontGetName(i, x, 128);
		popProgress->setProgress(i + 1);
	}
	popProgress->hide();
}

void MainScreen::renderAlarm(AlarmMsg alarm, float ratio) {
	String s;

	HorizontalLayout *mainItemLayout = new HorizontalLayout();
	VerticalLayout *verticalTextLayout = new VerticalLayout();
	Label *lbDaysTo = new Label();
	Label *lbName = new Label();
	Label *lbsplitter = new Label();
	Label *lbMessage = new Label();

	s = "";
	String multi = "";
	int val = alarm.DaysTo;

	if (val > 99) {
		val /= 30;
		multi = Lang::getString(GS_LETTERMONTH);

		if (val > 24) {
			val /= 12;
			multi = Lang::getString(GS_LETTERYEAR);
		}
	}

	if (val == 0) {
		s += Lang::getString(GS_NOW);
	} else if (val == -1) {
		s += Lang::getString(GS_YESTERDAY);
	} else {
		s += Convert::toString(val);
		s += multi;
	}

	mainItemLayout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mainItemLayout->setBackgroundColor(Styler::getClBgMessage());
	mainItemLayout->fillSpaceHorizontally();
	mainItemLayout->wrapContentHorizontally();

	//DaysTo setup
	VerticalLayout* vlDaysTo = new VerticalLayout();
	vlDaysTo->fillSpaceHorizontally();
	vlDaysTo->wrapContentHorizontally();
	vlDaysTo->setBackgroundColor(Styler::getClBgDaysLeft());
	vlDaysTo->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);

	lbDaysTo->setText(s);

	int daysLeftFontSize = static_cast<int>(Styler::getSzFontDaysLeft()
			- ratio * (Styler::getSzFontDaysLeft() - Styler::getSzFontSize1()));
	if (val < 1) {
		daysLeftFontSize /= 2;
	}

	Styler::setLabelFont(lbDaysTo, Styler::fontnameDaysLeft, daysLeftFontSize);

	lbDaysTo->setFontSize(daysLeftFontSize);
	lbDaysTo->fillSpaceHorizontally();
	lbDaysTo->fillSpaceVertically();
	lbDaysTo->setWidth(Styler::getSzWidthDaysLeft());
	lbDaysTo->setFontColor(Styler::getClFcDaysLeft());
	lbDaysTo->setBackgroundColor(Styler::getClBgDaysLeft());
	lbDaysTo->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	lbDaysTo->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	vlDaysTo->addChild(lbDaysTo);

	//name and message setup
	Styler::setLabelFont(lbName, Styler::fontnameEventName);
	lbName->setText(alarm.Name);
	lbName->setFontSize(Styler::getSzFontSize1());
	lbName->setFontColor(Styler::getClFcName());
	lbName->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
	lbMessage->setText(alarm.Message);
	lbMessage->setFontSize(Styler::szFontLittleMessage());
	lbMessage->setFontColor(Styler::getClFcMessage());
	lbMessage->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
	Label* lbAir = new Label();
	lbAir->setHeight(5);

	verticalTextLayout->addChild(lbName);
	verticalTextLayout->addChild(lbAir);
	verticalTextLayout->addChild(lbMessage);
	Styler::setLayoutPadding(verticalTextLayout, 3);
	verticalTextLayout->setPaddingLeft(Styler::getSzPadding() / 2);
	verticalTextLayout->setPaddingRight(Styler::getSzPadding() / 2);
	verticalTextLayout->wrapContentVertically();
	verticalTextLayout->fillSpaceHorizontally();

	mainItemLayout->addChild(vlDaysTo);
	mainItemLayout->addChild(lbsplitter);
	mainItemLayout->addChild(lbName);
	mainItemLayout->addChild(verticalTextLayout);
	mainItemLayout->wrapContentHorizontally();

	lvAlarms->addChild(mainItemLayout);
}

void MainScreen::close() {
	writeEventListToStore();
}

void MainScreen::optionsMenuItemSelected(Screen *screen, int index) {
	switch (index) {
	case OMIAddItem:
		editScreenMode = SEMNew;
		addNewEvent();
		break;
	case OMIImport:
		importFromSdcard();
		break;
	case OMIExport:
		exportToSdcard();
		break;
	case OMIOptions:
		actScreenOptions();
		break;
	case OMIExit:
		actExit();
		maExit(0);
		break;
	default:
		dbgAction();
		break;
	}
}

void MainScreen::dbgAction() {
	ASSERT_MSG(0, Convert::toString(Styler::getCurrStyleId()).c_str());
}

void MainScreen::optionsMenuClosed(Screen *screen) {
}

void MainScreen::listViewItemClicked(ListView *listView,
		ListViewItem *listViewItem) {
}

void MainScreen::listViewItemClicked(ListView *listView, int index) {
	///Alarm Context menu///

	String msg;
	msg = Lang::getString(GS_CM_EVENTNAME) + alarmsList[index].Name + Lang::getString(GS_CM_EVENTPERIODS)
			+ eventsList[alarmsList[index].EventIndex].periods.toString();

	eventIndexTransmission = alarmsList[index].EventIndex;
	eventBuffTransmission.clear();
	eventBuffTransmission = eventsList[eventIndexTransmission];
	eventPeriodIndexTransmission = alarmsList[index].EventPeriodIndex;

	pmAlarmContextMenuClick->setMenuHelpMessage(msg, -1);
	pmAlarmContextMenuClick->setMenuTitle(Lang::getString(GS_CM_TITLE));
	pmAlarmContextMenuClick->clearMenuItems();
	pmAlarmContextMenuClick->addMenuItem(Lang::getString(GS_CM_EDITCURREVENT));
	String sPeriod = "";
	sPeriod +=
			eventsList[alarmsList[index].EventIndex].periods[alarmsList[index].EventPeriodIndex].Letter;
	sPeriod +=
			Convert::toString(
					eventsList[alarmsList[index].EventIndex].periods[alarmsList[index].EventPeriodIndex].Factor);

	if (eventBuffTransmission.periods.size() > 1) {
		pmAlarmContextMenuClick->addMenuItem(
				Lang::getString(GS_CM_DELETEPERIOD) + " `" + sPeriod + "`");
	} else {
		pmAlarmContextMenuClick->addMenuItem("");
	}
	pmAlarmContextMenuClick->addMenuItem(Lang::getString(GS_CM_DELETEEVENT));
	pmAlarmContextMenuClick->show();
	Environment::getEnvironment().addTimer(this, 1000, 0);
}

void MainScreen::runTimerEvent() {
	if (pmAlarmContextMenuClick->result != -1) {
		Environment::getEnvironment().removeTimer(this);
		contextAlarmListMenuAction(pmAlarmContextMenuClick->result);
		pmAlarmContextMenuClick->reset();
	}

	if (screenEditEvent->isDone()) {
		if (editScreenMode == SEMEdit) {
			eventsList[eventIndexTransmission] = screenEditEvent->getEvent();
		} else if (editScreenMode == SEMNew) {
			eventsList.add(screenEditEvent->getEvent());
		}
		renderEventList();
		writeEventListToStore();
		screenEditEvent->reset();
	}
}

void MainScreen::writeEventListToStore() {
	waitMsg->setMessage(Lang::getString(GS_WRITEEVENTSTODEVICE));
	waitMsg->show();
	StorageWorks sw(storeName);
	sw.rm();
	sw.write(eventsList.toString());
	waitMsg->hide();
}

void MainScreen::contextAlarmListMenuAction(int menuItemIndex) {
	switch (menuItemIndex) {
	case CMIEdit:
		editScreenMode = SEMEdit;
		CMAEdit(eventBuffTransmission);
		break;
	case CMIRmPeriod:
		CMARmPeriod(eventIndexTransmission, eventPeriodIndexTransmission);
		break;
	case CMIRmEvent:
		CMARmEvent(eventIndexTransmission);
		break;
	default:
		break;
	}
}

void MainScreen::CMAEdit(Event ev) {
	Environment::getEnvironment().addTimer(this, 1000, 0);
	screenEditEvent->reset();
	screenEditEvent->setEvent(ev);
	screenEditEvent->show();
}

void MainScreen::CMARmPeriod(int eventItemIndex, int eventPeriodIndex) {
	eventsList[eventItemIndex].periods.remove(eventPeriodIndex);

	renderEventList();
}

void MainScreen::renderEventList() {
	generateAlarmMsgsFromEvents();

	waitMsg->setMessage(Lang::getString(GS_SORTALARMS));
	waitMsg->show();
	sortAlarmMsgs(alarmsList);
	waitMsg->hide();

	renderAlarms();

	waitMsg->hide();
}

void MainScreen::CMARmEvent(int eventItemIndex) {
	eventsList.remove(eventItemIndex);
	alarmsList.clear();
	renderEventList();
}

void MainScreen::addNewEvent() {
	Environment::getEnvironment().addTimer(this, 1000, 0);
	eventBuffTransmission.clear();
	screenEditEvent->setEvent(eventBuffTransmission);
	screenEditEvent->reset();
	screenEditEvent->show();
}

