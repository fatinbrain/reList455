/**
 * \file Lang.h
 * \brief Translations on various languages.
 */


#ifndef LANG_H_
#define LANG_H_

#include <MAUtil/String.h>
#include <maassert.h>

using MAUtil::String;


/** Counts.*/
/**@{*/
static const int MAXSTRCOUNT = 50;
static const int LANGSCOUNT = 2;
/**@}*/


/** Indexes.*/
/**@{*/
static const int GS_MAINTITLE = 0;
static const int GS_WAIT = 1;
static const int GS_WAITPB = 2;
static const int GS_NEWEVENT = 3;
static const int GS_IMPORT = 4;
static const int GS_EXPORT = 5;
static const int GS_EXIT = 6;
static const int GS_READDATA = 7;
static const int GS_PARSING = 8;
static const int GS_CREATEALARMSFROMEVENTS = 9;
static const int GS_RENDERALARM = 10;
static const int GS_FONTREFRESH = 11;
static const int GS_LETTERMONTH = 12;
static const int GS_LETTERYEAR = 13;
static const int GS_NOW = 14;
static const int GS_YESTERDAY = 15;
static const int GS_CM_EVENTNAME = 16;
static const int GS_CM_EVENTPERIODS = 17;
static const int GS_CM_TITLE = 18;
static const int GS_CM_EDITCURREVENT = 19;
static const int GS_CM_DELETEPERIOD = 20;
static const int GS_CM_DELETEEVENT = 21;
static const int GS_WRITEEVENTSTODEVICE = 22;
static const int GS_SORTALARMS = 23;
static const int GS_SINCE = 24;
static const int GS_NOPERIODS = 25;
static const int GS_EDITEVENTTITLE = 26;
static const int GS_EVENTNAME = 27;
static const int GS_EVENTDATE = 28;
static const int GS_EVENTREPEATPERIOD = 29;
static const int GS_ADDEVENTPERIOD = 30;
static const int GS_CANCEL = 31;
static const int GS_OK = 32;
static const int GS_ADDEVENTPERIODTITLE = 33;
static const int GS_SELECTPERIOD = 34;
static const int GS_CHANGEPERIOD = 35;
static const int GS_SELECTPERIODCOUNT = 36;
static const int GS_ADD = 37;
static const int GS_BACK = 38;
static const int GS_YEARS = 39;
static const int GS_MONTHS = 40;
static const int GS_OPTIONS = 41;
static const int GS_LANGUAGE = 42;
static const int GS_CHANGE = 43;
static const int GS_LANGUAGESELECTTITLE = 44;
static const int GS_LANGUAGESELECTMESSAGE = 45;
static const int GS_STYLE = 46;
static const int GS_STYLESELECTTITLE = 47;
static const int GS_STYLESELECTMESSAGE = 48;
/**@}*/


/**
 * \brief Structure to represent one of languages.
 */
struct lanuage{
	int id;
	String name;
	String strings[MAXSTRCOUNT];
};


/**
 * \brief Static class of all translations.
 */
class Lang{
public:
	Lang();
	static String getString(int stringIndex);
	static int getCurrLangId();
	static void setCurrLangId(const int currLangId);
	static String getCurrLangName();
	static int getLangsCount();
	static String getLangName(const int index);
private:
	static int currLangId;
	static lanuage languages[LANGSCOUNT];
};


#endif /* LANG_H_ */
