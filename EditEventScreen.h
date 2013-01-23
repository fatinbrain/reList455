/**
 * \file  EditEventScreen.h
 * \author  fat
 * \brief Contains class to work with event
 * \version  0.1
 */
#ifndef EDITEVENTSCREEN_H_
#define EDITEVENTSCREEN_H_

#include <NativeUI/Widgets.h>
#include <NativeUI/DatePicker.h>
#include "Event.h"
#include "AddEventPeriod.h"
#include "Styler.h"
#include "PopupMessage.h"
#include "Lang.h"

using namespace NativeUI;


/**
 * \brief Class to edit event info.
 *
 * Detailed info goes here.
 * \version 0.1
 */
class EditEventScreen: public Screen,
		public ButtonListener,
		public EditBoxListener,
		public TimerListener,
		public DatePickerListener{

public:
    EditEventScreen(Screen *parent, Event & e);
    EditEventScreen(Screen *parent);
    ~EditEventScreen();
    Event getEvent();
    void setEvent(Event & event);
    bool isDone();
    void reset();
private:
    bool done;
    Event _event;
    Screen *sParent;
    VerticalLayout *vl;
    Label *lb;
    Label *stName;
    EditBox *ebName;
    Label *stDate;
    DatePicker *dpDate;
    Label *stPeriod;
    Label *lbPeriods;
    Button *btnEditPeriods;
    HorizontalLayout *hlConfirm;
    Button *bOk;
    Button *bCancel;

    AddEventPeriod *screenAddEventPeriod;

    void resetPeriodLabel();
    void eventInfoToScreen();
    void grabScreenInfoToInternalEvent();

	void createUI();
	void setOkEnablity();
	void editRe();

	virtual void buttonClicked(Widget* button);
	virtual void editBoxReturn(EditBox* editBox);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox,
			const MAUtil::String& text);
	virtual void datePickerValueChanged(
	            DatePicker* datePicker,
	            const struct Date& selectedDate);

	virtual void runTimerEvent();
};

#endif /* EDITEVENTSCREEN_H_ */
