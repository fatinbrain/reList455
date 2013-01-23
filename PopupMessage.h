#ifndef POPUPMESSAGE_H_
#define POPUPMESSAGE_H_

#include "Styler.h"

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace MAUtil;
using namespace NativeUI;

/**
 * \brief  Class to create and process PopupMessage
 *
 * Creates popup message with title, help message string.
 * No buttons present.
 * \version 0.1
 */
class PopupMessage {
public:
	/**
	 * Default constructor.
	 * @param title	Title of PopupMessage
	 * @param message	Message string of PopupMessage
	 */
	PopupMessage(String title ="Message caption", String message = "text message");

	/**
	 * Default destructor
	 */
	~PopupMessage();

	/**
	 * Shows prepared message
	 */
	void show();

	/**
	 * Hides current message
	 */
	void hide();

	/**
	 * Set PopupMessage message string
	 * @param message	String to display
	 */
	void setMessage(String message);
	/**
	 * Set PopupMessage title
	 * @param title	String to set as title
	 */
	void setTitle(String title);
private:
	String message_;
		/**< String for message*/
	String title_;
		/**< String for title*/
	bool isVisible_;
		/**< Flag which shows current PopupMessage state*/

	/**
	 * \name UI members
	 * Various widgets for user interface of PopupMessage.
	 */
	///@{
	Dialog* dia_;
	Label* lbMessage_;
	///@}

	void createLayout();
};

#endif /* POPUPMESSAGE_H_ */
