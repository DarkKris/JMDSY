#include "main.h"

int main() {
	initLoginLog();
	initCardList(&card);
	readCard();
	parseCard();
	readLog();
	praseLog();
	printf("欢迎进入计费管理系统\n");
	do {
		outputMenu();
		switch(opt){
		case 1:addCard();break;
		case 2:printCard();break;
		case 3:useComputer();break;
		case 4:exitComputer();break;
		case 5:topUp();break;
		case 6:withdraw();break;
		case 7:searchAll();break;
		case 8:exitCard();break;
		case 0:updateSaveAll();updateLog();break;
		default: printf("请正确输入编码!\n");
		}
	}while(opt != 0);
	return 0;
}
