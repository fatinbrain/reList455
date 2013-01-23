#include "Options.h"

int Options::version = 0;
int Options::langId = 0;
int Options::styleId = 0;


String extractPart(String& s, int shift = 0, char terminator = '|'){
	String sbuff = "";

	int i = shift;
	for(; s[i] != terminator; i++){
		sbuff += s[i];
	}

	s = s.substr(i + 1, s.length() - i - 1);
	printf("rezstr[%s]\n", s.c_str());
	return sbuff;
}

int extractInt(String& s, int shift = 0, char terminator = '|'){
	String sbuff = extractPart(s, shift, terminator);
	return Convert::toInt(sbuff);
}

Options::Options(){
}

Options::~Options() {
}

void Options::parse(String s) {
	//extract version
	String sBuff = "";

	printf("parsing from [%s]\n", s.c_str());
	version = extractInt(s);

	//invoke particular parser
	switch (version) {
		case 0:
			parse0(s);
			break;
		default:
			break;
	}
}

int Options::getStyleId() {
	return styleId;
}

void Options::setStyleId(int styleId) {
	Options::styleId = styleId;
}

void Options::parse0(String s) {
	printf("***parse0***\n[%s]\n", s.c_str());

	langId = extractInt(s);
	printf("langid setto:%d\n", langId);

	styleId = extractInt(s);
	printf("styleid setto:%d\n", styleId);
}


String Options::toString() {
	String rez = "";

	rez += Convert::toString(version);
	rez += "|";

	rez += Convert::toString(langId);
	rez += "|";

	rez += Convert::toString(styleId);
	rez += "|";

	return rez;
}

int Options::getLangId() {
	return langId;
}

void Options::setLangId(int langId) {
	Options::langId = langId;
}

