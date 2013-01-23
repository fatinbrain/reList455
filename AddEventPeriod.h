#ifndef ADDEVENTPERIOD_H_
#define ADDEVENTPERIOD_H_

#include "Convert.h"
#include "Period.h"
#include "Styler.h"
#include "Lang.h"
#include <MAUtil/String.h>
#include <NativeUI/Widgets.h>


using namespace MAUtil;
using namespace NativeUI;

class AddEventPeriod:public Screen, public ButtonListener/*, public EditBoxListener*/{
public:
	AddEventPeriod(Screen* parent);
	~AddEventPeriod();

	Period getResult();
	bool isDone();
	void reset();
	void preShow();

private:
	Screen* sParent;
	VerticalLayout* vl;
	Label* lb;

	Label* lbLetter;
	Label* lbCurrPeriod;
	Button* btnPeriodToggle;


	Label* lbFactor;
	EditBox* ebNum;
	Button* bp1;
	Button* bm1;
	Button* bp3;
	Button* bm3;

	HorizontalLayout* hlButtons;
	Button* bAdd;
	Button* bBack;

	Period resultPeriod_;
	bool done_;

	virtual void buttonClicked(Widget* button);

	void createUI();
};


#endif /* EDITEVENTPERIODS_H_ */
