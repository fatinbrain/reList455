#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_


#include "ABS.h"
#include "Common.h"
#include "Events.h"
#include "Styler.h"
#include "StorageWorks.h"
#include "WaitMessage.h"
#include "PopupMessage.h"
#include "PopupProgress.h"
#include "PopupMenu.h"
#include "EditEventScreen.h"
#include "PopupProgress.h"
#include "StringSdcard.h"
#include "Lang.h"
#include "ScreenOptions.h"
#include "Options.h"

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>
#include "MAHeaders.h"
#include <maassert.h>

//#define VERSION "\n_deWer_v64_"
#define VERSION ""

using namespace NativeUI;
using namespace MAUtil;


/**
 * Constants section.
 */
const String storeName = "store01";
const String storeOptions = "storeOptions";
const String imExFName = "relist455.txt";

/**
 * OptionsMenuItems
 */
const int OMIAddItem = 0;
const int OMIExport = 1;
const int OMIImport = 2;
const int OMIOptions = 3;
const int OMIExit = 4 ;


/**
 * AlarmListContextMenuItems;
 */
const int CMIEdit = 0;
const int CMIRmPeriod = 1;
const int CMIRmEvent = 2;

/**
 * ScreenEditMode
 */
const int SEMInit = 0;
const int SEMEdit = 1;
const int SEMNew = 2;

class MainScreen: public Screen, public ScreenListener, public ListViewListener, public TimerListener{

public:
	MainScreen();
	~MainScreen();

	void close();


private:
    int editScreenMode;
    int eventPeriodIndexTransmission;
    int eventIndexTransmission;
    Options options;

    VerticalLayout* lMain;
    Label* lbTitleSplitter;
    ListView* lvAlarms;

    WaitMessage* waitMsg;
    PopupMessage* dbgPopup;
    PopupMenu* pmAlarmContextMenuClick;
    PopupProgress* popProgress;

    EditEventScreen* screenEditEvent;
    ScreenOptions* screenOptions;

    Events eventsList;
    Event eventBuffTransmission;
    AlarmMsgs alarmsList;

    void actScreenOptions();
    void actExit();
    void applyOptions();
    AlarmMsg generateAlarmMsg(Event e, int periodid);
    virtual void listViewItemClicked(ListView *listView, int index);
    virtual void listViewItemClicked(ListView *listView, ListViewItem *listViewItem);
    virtual void optionsMenuClosed(Screen *screen);
    virtual void optionsMenuItemSelected(Screen *screen, int index);
    virtual void runTimerEvent();
	void addNewEvent();
    void clearListView(ListView *listView);
	void CMAEdit(Event ev);
	void CMARmEvent(int eventItemIndex);
	void CMARmPeriod(int eventItemIndex, int eventPeriodIndex);
    void contextAlarmListMenuAction(int menuItemIndex);
    void createDefaultEventsList();
    void createUI();
	void dbgAction();
	void exportToSdcard();
    void fontOverload();
    void generateAlarmMsgsFromEvents();
    void grabOptions();
	void importFromSdcard();
    void initLoad();
    void obtainEventsList();
    void readOptionsFormDevice();
    void renderAlarm(AlarmMsg alarm, float ratio = 0);
    void renderAlarms();
    void renderEventList();
    void writeEventListToStore();
    void writeOptionsToDevice();

	/**
	 * \brief Function to perform callback from events.parsing().
	 *
	 *
	 * @param controlCode  Control code for function.
	 *
	 * *values*
	 *
	 *   **-1**  disable.
	 *
	 *   **0**  set Total events count.
	 *
	 *   **1**  set current parsed event index.
	 * @param argument  Argument of function.
	 */
	friend void updateParseEventInfo(int controlCode, int argument);
};

#endif /* MAINSCREEN_H_ */
