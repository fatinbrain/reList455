#include "Period.h"

Period::Period(char letter, int factor){
	Letter = letter;
	Factor = factor;
}

Period::Period(){
	Letter = '\0';
	Factor = 0;
}

void Period::set(char letter, int factor){
	Letter = letter;
	Factor = factor;
}

String Period::toString()
{
	String rez = "";
	rez += this->Letter;
	rez += Convert::toString(this->Factor);

	return rez;
}


