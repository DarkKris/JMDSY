#include "main.h"

time_t stringToTime(char* s) {
	// TODO complete
	time_t res;
	sscanf(s, "%ld", &res);
	return res;
}