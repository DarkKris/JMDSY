#include "main.h"

int opt; // opt the user chosed in the menu

void outputMenu() {
	printf("----------菜单----------\n");
	printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n0.退出");
	printf("\n------------------------\n");
	printf("请输入功能编号：(0~8)");
	scanf("%d",&opt);
}

void addCard() {
	char aName[18],aPwd[8];
	float fBalance;
	struct tm endtm;

	printf("\n添加卡:\n");
	printf("请输入卡号：");
	scanf("%s",aName);
	printf("请输入密码：");
	scanf("%s",aPwd);
	printf("请输入开卡金额：");
	scanf("%f",&fBalance);

	printf("请输入截止时间(年)：");
	scanf("%d",&endtm.tm_year);
	printf("请输入截止时间(月)：");
	scanf("%d",&endtm.tm_mon);
	printf("请输入截止时间(日)：");
	scanf("%d",&endtm.tm_mday);
	int result = saveCard(aName, aPwd, fBalance, endtm);
	if(result) printf("\n卡创建成功！\n\n");
	else printf("\n卡创建失败！\n\n");
}

void printCard() {
	char aName[18];
	printf("\n查询卡:\n");
	printf("请输入查询卡号：");
	scanf("%s",aName);
	Card* res = searchCard(aName);
	printf("\n卡号\t\t密码\t开卡金额\t卡状态\n");
	printf("%s\t%s\t%f\t",res->aName, res->aPwd, res->fBalance);
	switch(res->nStatus) {
		case 0: printf("未上机\n");break;
		case 1: printf("正在上机\n");break;
		case 2: printf("已注销\n");break;
		case 3: printf("失效\n");break;
	}
	printf("\n");
}

void useComputer() {
	printf("上机\n");
}

void exitComputer() {
	printf("下机\n");
}

void topUp() {
	printf("充值\n");
}

void withdraw() {
	printf("退费\n");
}

void searchAll() {
	printf("查询统计\n");
}

void exitCard() {
	printf("注销卡\n");
}

int main() {
	readCard();
	parseCard();
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
		case 0:break;
		default: printf("请正确输入编码!\n");
		}
	}while(opt != 0);
	return 0;
}
