#include "ABS.h"
#include <conprint.h>

int comare(AlarmMsg a1, AlarmMsg a2){
	return(a1.DaysTo - a2.DaysTo);
}

void swapMsgs(AlarmMsg &a1, AlarmMsg &a2){
	AlarmMsg buff;
	buff = a1;

	a1 = a2;
	a2 = buff;
}

void sortAlarmMsgs(AlarmMsgs &a){
	bool sw = true;
	int pass = 0;

	while(sw){
		pass++;
		sw = false;
		for(int i = 0; i < a.size() - 1; i++){
			if(comare(a[i], a[i+1]) > 0){
				swapMsgs(a[i], a[i+1]);
				sw = true;
			}
		}
	}

	printf("sort passes:%d\n", pass);
}
