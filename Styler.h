#ifndef STYLER_H_
#define STYLER_H_

#include "Styles.h"

#include <NativeUI/Widgets.h>

using namespace NativeUI;

/**
 * Various styles for labels and other widgets.
 */
enum LabelStyles{
	LSLevel1, LSLevel2, LSLevel3, LSPopupMessage, LSScreenName
};


/**
 * \brief  Styling class.
 * \version 0.2
 *
 * Perform style adjusts for various widgets.
 */
class Styler {
public:
	static const char* fontnameDaysLeft;
	static const char* fontnameEventName;
	static const char* fontnameScreenTitle;

	/**
	 * Set `sublabel` style for given label
	 * @param lb Label to act.
	 */
	static void subLabel(Label* lb);

	/**
	 * Set style for label.
	 * @param lb Label to act.
	 * @param style Style to set. \sa LabelStyles
	 */
	static void setLabelStyle(Label* lb, LabelStyles style);


	/**
	 * Set all paddings for given Layout.
	 * @param layout Layout to set padding.
	 * @param paddingSize Padding size. If `0` set default calculated value.
	 */
	static void setLayoutPadding(Layout* layout, int paddingSize = -1);

	/**
	 * Getter of font size for Level2.
	 * @return Font size of label for Level2.
	 */
	static int getSzFontSize2();

	/**
	 * Getter of font size for little message.
	 * @return Font size of label for little message.
	 */
	static int szFontLittleMessage();

	/**
	 * Getter of font size for Level1.
	 * @return Font size of label for Level1.
	 */
	static int getSzFontSize1();

	/**
	 * Returns screen size x.
	 * @return Screen size x.
	 */
    static int getScrX();

	/**
	 * Returns screen size y.
	 * @return Screen size y.
	 */
    static int getScrY();

    /**
     * Returns padding size for particular device screen size.
     * @return Padding size.
     */
    static int getSzPadding();

    /**
     * Returns font size of **DaysLeft** field.
     * @return DaysLeft field font size.
     */
    static int getSzFontDaysLeft();

    /**
     * Set style for bottom control horizontal layout.
     * @param layout Layout to process.
     */
    static void setBottomCtrlLayoutStyle(HorizontalLayout* layout);

    /**
     * Update internal constants to be actual for current device resolution.
     */
    static void update();

    /**
     * Maintain label font.
     * @param lb	label to work with
     * @param fontName	font name to set
     * @param fontSize	size of font
     * @return
     */
    static int setLabelFont(Label* lb, const char* fontName, int fontSize = 20);

    /**
     * Add separator to Layout.
     * \warning what about **horizontal** layout?
     * @param lay	Layout to process
     * @param size	size of separator
     */
    static void addSeparator(Layout* lay, int size = 10);

    /**
     * \name Size / color getters
     */
    /**@{*/
    static int getSzWidthDaysLeft();
    static int getClBgDaysLeft();
    static int getClBgMessage();
    static int getClFcDaysLeft();
    static int getClFcMessage();
    static int getClFcName();
    static int getSzFontLittleMessage();
	static int getClLabelGradient1();
	static int getClLabelGradient2();
	static int getCurrStyleId();
	static void setCurrStyleId(int currStyleId);

	/**@}*/


private:
    /**
     * Default constructor.
     */
    Styler();
    /**
	 * \name Sizes group.
	 * \brief Definitions of various sizes of widgets.
	 */
    ///@{
    static int szFontLittleMessage_;
    /**<Font size for label indicating `alarm message` field*/
    static int szFontDaysLeft_;
    /**<Font size for label indicating `DaysLeft` field*/
    static int szWidthDaysLeft_;
    /**<Font width for label indicating `DaysLeft` field*/
    static int szFontSize2_;
    /**<Font size for Level 2*/
    static int szFontSize1_;
    /**<Font size for Level 1*/
    static int szPadding_;
    /**<Padding size*/
    static int scrX;
    /**<Device size x*/
    static int scrY;
    /**<Device size y*/
    static int szBottomCtrlHeight;
    /**<Height of bottom controls layout*/
    ///@}

    static double szNativeDiagonal;
    static int currStyleId;

    /**
	 * \name Colors group.
	 * \brief Definition of various colors of widgets and its elements.
	 */
    ///@{
    static int clFCDaysLeft;
    static int clBGDaysLeft;
    static int clBGMessage;
    static int clFCName;
    static int clFCMessage;

    static int clBottomCtrlsLayoutColor;
    static int clLabelGradient2;
    static int clLabelGradient1;
    static int clFCTitle;
    ///@}
};

#endif /* STYLER_H_ */
