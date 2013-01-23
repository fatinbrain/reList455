#ifndef STYLES_H_
#define STYLES_H_

#include <MAUtil/String.h>

using MAUtil::String;

const int COUNTFONTS = 3;
const int COUNTSIZES = 8;
const int COUNTCOLORS = 9;
const int COUNTSTYLES = 2;

const int SI_SZ_F1 = 0;
const int SI_SZ_F2 = 1;
const int SI_SZ_FDL = 2;
const int SI_SZ_WDL = 3;
const int SI_SZ_P = 4;
const int SI_SZ_FLM = 5;
const int SI_SZ_BCH = 6;
const int SI_SZ_ND = 7;

const int SI_FN_DL = 0;
const int SI_FN_EN = 1;
const int SI_FN_ST = 2;

const int SI_CL_FDL = 0;
const int SI_CL_BDL = 1;
const int SI_CL_BM = 2;
const int SI_CL_FN = 3;
const int SI_CL_FM = 4;
const int SI_CL_BBC = 5;
const int SI_CL_LG1 = 6;
const int SI_CL_LG2 = 7;
const int SI_CL_FT = 8;

struct Style{
	String name;
	char* fonts[COUNTFONTS];
	int sizes[COUNTSIZES];
	long colors[COUNTCOLORS];
};

struct Styles{
public:
	static int getItemsCount();
	static Style items[COUNTSTYLES];
};

#endif /* STYLES_H_ */


