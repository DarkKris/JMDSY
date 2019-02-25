#include "main.h"

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
	if(res == NULL){
		printf("没要查找到相应数据\n");
		return;
	}
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
	char aName[18]={0};

	printf("上机\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	Card* rescard = searchCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	rescard->nStatus = 1;
	printf("上机成功\n");
}

void exitComputer() {
	printf("下机\n");
}

void topUp() {
	char aName[18]={0};
	float money=0;

	printf("充值\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	printf("请输入充值金额: ");
	scanf("%f",&money);
	Card* rescard = searchCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	rescard->fBalance += money;
	printf("充值成功\n");
}

void withdraw() {
	char aName[18]={0};
	float money=0;

	printf("退费\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	printf("请输入退费金额: ");
	scanf("%f",&money);
	Card* rescard = searchCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	if(rescard->fBalance >= money)
	{
		rescard->fBalance -= money;
		printf("退费成功\n");
	}else{
		printf("余额不足。（余额：%f)\n",rescard->fBalance);
	}
}

void searchAll() {
	printf("查询统计\n");
	printAll();
}

void exitCard() {
	char aName[18]={0};

	printf("注销卡\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	Card* rescard = searchCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	rescard->nStatus = 2;
	printf("注销成功\n");
}