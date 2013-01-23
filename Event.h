#ifndef EVENT_H_
#define EVENT_H_

#include "Tools.h"
#include "Periods.h"
#include <ma.h>
#include <matime.h>
#include <mastdlib.h>
#include <MAUtil/String.h>
#include <MAP/DateTime.h>

using namespace MAUtil;
using namespace MAPUtil;

const int MINIMAL_EVENT_LENGTH = 10;

class Event{
private:
	DateTime InitDate;
public:
	String Name;
	stDate InitDate_st;
	Periods periods;

	Event(String name);
	Event();
	void set(String name, int year, int month, int day);
	void setDate(int year, int month, int day);

	void clear();
	DateTime getEventDate();

	String toString();
	void parse(String s);

	void addPeriod(char Letter, int Factor);
private:
	void parsePeriods(Periods &p, String s);
};


#endif /* EVENT_H_ */
