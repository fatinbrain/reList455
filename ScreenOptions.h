#ifndef SCREENOPTIONS_H_
#define SCREENOPTIONS_H_

#include "Convert.h"
#include "Options.h"
#include "Styler.h"
#include "Lang.h"
#include "Styles.h"
#include "PopupMenu.h"
#include <MAUtil/String.h>
#include <NativeUI/Widgets.h>


using namespace MAUtil;
using namespace NativeUI;

enum menuMode { MM_LANG, MM_STYLE };

class ScreenOptions:public Screen, public ButtonListener, TimerListener{
public:
	ScreenOptions(Screen* parent);
	~ScreenOptions();

	bool isDone();
	void reset();


private:
	bool done;
	int newLangId;
	int newStyleId;
	menuMode mMode;

	Screen* sParent;
	VerticalLayout* vlMain;
	Label* lbScreenTitle;

	Label* lbLanguage;
	Label* lbCurrLang;
	Button* btnChangeLang;

	Label* lbStyle;
	Label* lbCurrStyle;
	Button* btnChangeStyle;

	HorizontalLayout* hlButtons;
	Button* btnAccept;
	Button* btnCancel;

	PopupMenu* pmOptions;

	virtual void buttonClicked(Widget* button);
	void createUI();

	virtual void runTimerEvent();
};

#endif /* SCREENOPTIONS_H_ */
