#ifndef POPUPPROGRESS_H_
#define POPUPPROGRESS_H_

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>
#include "Convert.h"
#include "Styler.h"


using namespace NativeUI;
using namespace MAUtil;

/**
 * \brief Popup progress bar with title, text.
 *
 *	\version 0.1
 */
class PopupProgress{
public:
	/**
	 * \brief Default constructor.
	 * @param title Title of popup progress.
	 * @param message Help message of window.
	 */
	PopupProgress(/*Screen* parent, */String title = "", String message = "");

	/**
	 * \brief Default destructor.
	 */
	~PopupProgress();

	/**
	 * \brief Set maximal value of progress bar.
	 * @param maxVal  New maximal value.
	 */
	void setMaxVal(int maxVal);

	/**
	 * \brief Set current progress value.
	 * @param val New progress value.
	 */
	void setProgress(int val);

	/**
	 * \brief Set title of popup progress.
	 * @param title New title.
	 */
	void setTitle(String title);

	/**
	 * \brief Set help message.
	 * @param message New help message.
	 */
	void setMessage(String message);

	/**
	 * \brief Show window.
	 */
	void show();

	/**
	 * \brief Hide window.
	 */
	void hide();


private:
	/**
	 * \brief Hidden default constructor.
	 */
	PopupProgress();

	/**
	 * \name Visual widgets.
	 * \brief List of all widgets used to create user interface.
	 */
	/**@{*/
	Dialog* dlg;
	VerticalLayout* vlMain;
	Label* lbMessage;
	VerticalLayout* hlProgress;
	ProgressBar* pb;
	Label* lbPercent;
	/**@}*/

	String sTitle;
	String sMessage;

	int upCount;

	/**
	 * \brief Creates user interface.
	 */
	void createUI();

	/**
	 * \brief Update percentage text.
	 */
	void updatePercentage();
};

#endif /* POPUPPROGRESS_H_ */
