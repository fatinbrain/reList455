#include "Tools.h"

void printDt(DateTime dt, String s) {
	printf("%s[%02d.%02d.%02d %02d:%02d:%02d]\n", s.c_str(),
			dt.getYear() + 1900, dt.getMonth() + 1, dt.getDay(), dt.getHour(),
			dt.getMinute(), dt.getSecond());
}

DaysTo_s grabDt(DateTime initDate, Period prd) {
	DaysTo_s dts;
	dts.DaysTo = -1;
	dts.FactorCount = 0;

	DateTime dtToday = DateTime::today();

	switch (prd.Letter) {
	case 'y':
	case 'Y': {
		printf("initdate:%d.%d.%d\n", initDate.getYear(), initDate.getMonth(), initDate.getDay());
		int factor = (dtToday.getYear() - initDate.getYear()) / prd.Factor;

		int nextAlarmYear = initDate.getYear() + factor * prd.Factor;

		if (nextAlarmYear < 2038) {

			DateTime dtNextAlarm(nextAlarmYear, initDate.getMonth(),
					initDate.getDay());

			printDt(dtNextAlarm, "pre_nextalarm");

			if (dtNextAlarm.getTicks() + 86400 < dtToday.getTicks()) {
				printf("incr alarm");
				dtNextAlarm = dtNextAlarm.addYears(prd.Factor);
			}

			printDt(dtNextAlarm, "nextalarm");

			TimeSpan ts(dtNextAlarm.getTicks() - dtToday.getTicks());
			dts.DaysTo = (int) ts.getTotalDays();
			dts.FactorCount = (dtNextAlarm.getYear() - initDate.getYear())
					/ prd.Factor;
		}
		break;
	}
	case 'm':
	case 'M': {
		tm tmAlarm;
		time_t nextAlarm = initDate.getTicks();
		int cntz = 0;

		split_time(nextAlarm, &tmAlarm);

		while(nextAlarm < dtToday.getTicks()){
			tmAlarm.tm_mon += prd.Factor;
			cntz++;
			if(tmAlarm.tm_mon >= 12){
				tmAlarm.tm_mon -= 12;
				tmAlarm.tm_year++;
			}
			nextAlarm = mktime(&tmAlarm);
		}

		printDt(nextAlarm, "nextalarm");

		TimeSpan ts(nextAlarm - dtToday.getTicks());
		dts.DaysTo = (int) ts.getTotalDays();
		dts.FactorCount = cntz;

		break;
	}

	}
	printf("***dt get: dt%d per%d\n", dts.DaysTo, dts.FactorCount);
	return dts;
}

MAUtil::String date2str(time_t date) {
	struct tm t = { 0 };
	split_time(date, &t);

	MAUtil::String s = "";
	s += Convert::toString(t.tm_mday);
	s += ".";
	s += Convert::toString(t.tm_mon + 1);
	s += ".";
	s += Convert::toString(t.tm_year + 1900);

	return s;
}
