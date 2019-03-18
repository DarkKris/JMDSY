#include "main.h"

int main() {
	// 初始化链表
	initOptLog();
	initLoginLog();
	initCardList(&card);

	// 读取并解析Card.txt
	readCard();
	parseCard();

	// 读取并解析login_log.txt
	readLog();
	praseLog();

	// 读取并解析option_log.txt
	readOptLog();
	praseOptLog();

	// UI
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
		case 0:updateSaveAll();updateLog();updateOptLog();break;
		default: printf("请正确输入编码!\n");
		}
	}while(opt != 0);
	return 0;
}
