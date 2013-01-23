#ifndef PERIOD_H_
#define PERIOD_H_

#include "Convert.h"
#include <MAUtil/String.h>

using MAUtil::String;

class Period{
public:
	char Letter;
	int Factor;
	Period(char, int);
	Period();
	void set(char, int);

	String toString();
};


#endif /* PERIOD_H_ */
