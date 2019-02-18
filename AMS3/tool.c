#ifndef __MAIN_H__
	#define __MAIN_H__
	#include "main.h"
#endif

time_t stringToTime(char* s) {
	// TODO complete
	time_t res;
	sscanf(s, "%ld", &res);
	return res;
}