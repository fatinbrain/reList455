#include "Events.h"

int Events::size() {
	return Events_.size();
}

Event& Events::operator [](int i) {
	return Events_[i];
}

String Events::toString() {
	String rez = "*";
	rez += Convert::toString(Events_.size());
	rez += "|";

	for (int i = 0; i < Events_.size(); i++) {
		rez += Events_[i].toString() + "|";
	}

	return rez;
}

void Events::clear() {
	Events_.clear();
}

void Events::remove(int index) {
	Events_.remove(index);
}

void Events::parse(String s) {
	//-printf("**parsing events from\n[%s]\n", s.c_str());

	Event e;

	String sBuff = "";
	int posBreak = 0;

	s = " " + s;
	if (s[s.length() - 1] != '|') {
		s += "|";
	}

	int currEvent = 0;
	int totalEvents = -1;


	if(s[1] == '*'){
		for(int i = 2; s[i] != '|'; i++){
			sBuff += s[i];
		}
		totalEvents = Convert::toInt(sBuff);
		//-printf("EVCOUNT:%d\n", totalEvents);
	}else{
		//-printf("noEVCOUNT\n");
	}

	//init
	callback(0, totalEvents);

	while ((s.find("|", posBreak + 1) != String::npos)
			&& (posBreak < s.length())) {
		//-printf("boom\n");
		sBuff = s.substr(posBreak + 1,
				s.find("|", posBreak + 1) - posBreak - 1);
		posBreak = s.find("|", posBreak + 1);

		//-printf("evline[%s]pos[%d]\n", sBuff.c_str(), posBreak);

		e.clear();
		if (sBuff.length() > MINIMAL_EVENTS_LENGTH) {
			e.parse(sBuff);
			Events_.add(e);

			//process
			callback(1, currEvent++);
		}
	}

	//disable
	callback(-1, -1);
}

void Events::add(Event e) {
	Events_.add(e);
}

void Events::regCallback(void (*cb)(int, int)) {
	callback = cb;
}

Events::Events(){
}
