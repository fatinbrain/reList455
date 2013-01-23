#ifndef EVENTS_H_
#define EVENTS_H_

#include "Common.h"
#include "Event.h"

#include <ma.h>
#include <MAUtil/Vector.h>
#include <MAUtil/String.h>

using MAUtil::Vector;
using MAUtil::String;

const int MINIMAL_EVENTS_LENGTH = 10;

class Events{
private:
	Vector<Event> Events_;
	void(*callback)(int, int);

public:
	Events();
	void add(Event e);
	void remove(int index);
	int size();
	Event& operator [](int i);
	void clear();

	String toString();
	void parse(String s);
	void regCallback(void(*cb)(int, int));
};



#endif /* EVENTS_H_ */
