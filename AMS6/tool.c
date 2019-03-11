#include "main.h"

time_t stringToTime(char* s) {
	// TODO complete
	time_t res;
	sscanf(s, "%ld", &res);
	return res;
}

void printCardInfo(const Card* res, int haveHead) {
	// 表头输出
	if(haveHead){
		printf("\n卡号\t");
		if(strlen(res->aName)>8)printf("\t"); // 对齐
		printf("密码\t开卡金额\t卡状态\n");
	}

	printf("%s\t%s\t%f\t",res->aName, res->aPwd, res->fBalance);
	switch(res->nStatus) {
		case 0: printf("未上机\n");break;
		case 1: printf("正在上机\n");break;
		case 2: printf("已注销\n");break;
		case 3: printf("失效\n");break;
	}
}