#ifndef PERIODS_H_
#define PERIODS_H_

#include "Period.h"

#include <MAUtil/Vector.h>
#include <MAUtil/String.h>

class Periods{
	Vector<Period> periods_;

public:
	void add(Period &e);
	int size();
	Period& operator [](int i);
	void clear();
	void remove(int index);

	String toString();
};


#endif /* PERIODS_H_ */
