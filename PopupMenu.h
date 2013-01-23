#ifndef POPUPMENU_H_
#define POPUPMENU_H_

#include "Styler.h"

#include <MAUtil/String.h>
#include <MAUtil/Vector.h>
#include <NativeUI/Widgets.h>
#include "Convert.h"

using namespace NativeUI;
using namespace MAUtil;

/**
 * \brief	Creates popup menu with title, help message and some buttons.
 *
 * \version 0.1
 *
 * ### Usage in caller
 * It is quite tricky to work with class. You should add **Timer** to update result of menu.
 * #### in class definition:
 *
 *      class ClassName : ..., public TimerListener
 *      ...
 *      PopupMenu* popupMenu;
 *
 * #### in class implementation:
 *
 *      virtual void runTimerEvent(){
 *          if(popupMenu->result != -1){
 *		    ...
 *		    Environment::getEnvironment().removeTimer(this);
 *		    popupMenu->reset();
 *      }
 *
 * #### setup menu
 *      popupMenu->clearMenuItems();
 *      popupMenu->addMenuItem(string_to_add);
 *      ...
 *
 * #### to call menu:
 *
 *	    popupMenu->show();
 *	    Environment::getEnvironment().addTimer(this, 1000, 0);
 */
class PopupMenu: public ButtonListener{
public:
	int result;

	/**
	 * Default constructor.
	 * @param screen	Parent screen.
	 * @param helpMessage	Menu informational string.
	 * @param menuTitle	Tile of menu.
	 */
	PopupMenu(Screen* screen, String helpMessage = "select item", String menuTitle = "");

	/**
	 * Default destructor.
	 */
	~PopupMenu();

	/**
	 * Show current menu.
	 */
	void show();

	/**
	 * Hide current menu.
	 */
	void hide();

	/**
	 * Add one item to menu.
	 * @param menuItemName	String representing new menu item.
	 */
	void addMenuItem(String menuItemName);

	/**
	 * Clean all menu items.
	 */
	void clearMenuItems();

	/**
	 * Set help message of menu.
	 * @param helpMessage	String to set as help menu.
	 * @param justification	Help message justification -1left, 0center, 1right
	 */
	void setMenuHelpMessage(String helpMessage, int justification = -1);

	/**
	 * Set menu title.
	 * @param menuTitle	String to set as title.
	 */
	void setMenuTitle(String menuTitle);

	/**
	 * Reset menu return code.
	 */
	void reset();

private:
	Dialog* dlg;
	VerticalLayout* vl;
	Label* lb;
	VerticalLayout* vlButt;
	Screen* parentScreen;

	Vector<String> menuItemNames;

	void createUI();
	void createMenuButtons();
	int getButtonIndexByName(Button* button);
	virtual void buttonClicked(Widget* button);
};

#endif /* POPUPMENU_H_ */
