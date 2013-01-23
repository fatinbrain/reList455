#ifndef TOOLS_H_
#define TOOLS_H_

#include "Period.h"
#include <conprint.h>
#include <matime.h>
#include <MAUtil/String.h>
#include <MAP/DateTime.h>

using namespace MAUtil;
using namespace MAPUtil;


#define SECS_IN_DAY 86400

struct DaysTo_s{
	int DaysTo;
	int FactorCount;
};

struct stDate{
	int Year;
	int Month;
	int Day;
};

DaysTo_s grabDt(DateTime initDate, Period prd);
MAUtil::String date2str(time_t date);
void printDt(DateTime dt, String s = "");


#endif /* TOOLS_H_ */
