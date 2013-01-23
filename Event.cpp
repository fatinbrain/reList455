#include "Event.h"

stDate parseDate(String s);
void setDate(int year, int month, int day);

Event::Event(String name) {
	Name = name;
}

Event::Event() {
	Name = "";
}

void Event::set(String name, int year, int month, int day) {
	Name = name;
	setDate(year, month, day);
}

void Event::addPeriod(char Letter, int Factor)
{
	Period p;
	p.Factor = Factor;
	p.Letter = Letter;

	periods.add(p);
}

String Event::toString() {
	String rez = "";

	rez += Name;
	rez += ";";
	rez += Convert::toString(InitDate_st.Day);
	rez += ".";
	rez += Convert::toString(InitDate_st.Month);
	rez += ".";
	rez += Convert::toString(InitDate_st.Year);
	rez += ";";
	for (int i = 0; i < periods.size(); i++) {
		rez += periods[i].Letter;
		rez += Convert::toString(periods[i].Factor);
		rez += ",";
	}
	rez[rez.length() - 1] = ';';

	return rez;
}

void Event::setDate(int year, int month, int day) {
	InitDate_st.Year = year;
	InitDate_st.Month = month;
	InitDate_st.Day = day;
	InitDate = DateTime(year - 1900, month - 1, day);
}

DateTime Event::getEventDate() {
	return InitDate;
}

void Event::parsePeriods(Periods &periods, String s) {
	//-printf("*****\nparsing periods from [%s]\n", s.c_str());

	char periodLetter;
	int periodFactor;

	String sBuff = "";
	int posBreak = 0;

	s = " " + s;
	if (s[s.length() - 1] != ',') {
		s += ",";
	}

	Period p;

	while ((s.find(",", posBreak + 1) != String::npos)
			&& (posBreak < s.length())) {
		sBuff = s.substr(posBreak + 1,
				s.find(",", posBreak + 1) - posBreak - 1);
		posBreak = s.find(",", posBreak + 1);

		//-printf("period[%s]pos[%d]\n", sBuff.c_str(), posBreak);

		periodLetter = sBuff.c_str()[0];
		periodFactor = atoi(sBuff.substr(1, sBuff.length() - 1).c_str());

		p.Letter = periodLetter;
		p.Factor = periodFactor;
		periods.add(p);
	}

}

void Event::parse(String s) {
	//format:
	//  NAME;DD.MM.YYYY;p1,p2,p3;
	//-printf("parsing event form\n[%s]\n", s.c_str());

	if (s.length() < MINIMAL_EVENT_LENGTH) {
		return;
	}

	if (s[s.length() - 1] != ';') {
		s += ";";
	}

	String sBuff;
	int pos = -1;

	//grab Name
	for(pos = 0; s[pos] != ';'; pos++){
		sBuff += s[pos];
	}

	//-printf("NAME:[%s]\n", sBuff.c_str());
	this->Name = sBuff;

	//grab date
	int dd = -1;
	int mm = -1;
	int yyyy = -1;

	for(pos++, sBuff = ""; s[pos] != '.' && pos < s.length(); pos++){
		sBuff += s[pos];
	}
	dd = Convert::toInt(sBuff);
	//-printf("DATE:[%d.%d.%d]\n", dd, mm, yyyy);
	for(pos++, sBuff = ""; s[pos] != '.' && pos < s.length(); pos++){
		sBuff += s[pos];
	}
	mm = Convert::toInt(sBuff);
	//-printf("DATE:[%d.%d.%d]\n", dd, mm, yyyy);
	for(pos++, sBuff = ""; s[pos] != ';' && pos < s.length(); pos++){
		sBuff += s[pos];
	}
	yyyy = Convert::toInt(sBuff);
	//-printf("DATE:[%d.%d.%d]\n", dd, mm, yyyy);
	this->setDate(yyyy, mm, dd);

	//grab periods
	char periodLetter = '\0';
	int periodCount = -1;
	Period p;

	pos++;
	while(s[pos] != ';' && pos < s.length()){
		periodLetter = s[pos];
		sBuff = "";
		pos++;
		while(s[pos] != ',' && s[pos] != ';' && pos < s.length()){
			sBuff += s[pos];
			pos++;
		}
		periodCount = Convert::toInt(sBuff);
		//-printf("PERIOD:%c%d\n", periodLetter, periodCount);
		p.Letter = periodLetter;
		p.Factor = periodCount;
		this->periods.add(p);
		if(s[pos] != ';'){
			pos++;
		}
	}
}


void Event::clear() {
	this->set("", 0, 0, 0);
	this->periods.clear();
}
