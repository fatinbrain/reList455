#include "Periods.h"

void Periods::add(Period & e) {
	periods_.add(e);
}

int Periods::size() {
	return periods_.size();
}

Period & Periods::operator [](int i) {
	return periods_[i];
}

void Periods::clear() {
	periods_.clear();
}

void Periods::remove(int index)
{
	periods_.remove(index);
}

String Periods::toString() {
	String s;

	for (int i = 0; i < periods_.size(); i++) {
		s += periods_[i].toString() + ";";
	}

	return s;
}
