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
	int res_year = 0;
	do{
		scanf("%d",&res_year);
		if(res_year<=2200 && res_year>=2019)
		{
			endtm.tm_year = res_year;
			break;
		}
		printf("请正确输入年份(2019~2200): ");
	}while(true);

	printf("请输入截止时间(月): ");
	int res_month = 0;
	do{
		scanf("%d",&res_month);
		if(res_month<=12 && res_month>=1) {
			endtm.tm_mon = res_month;
			break;
		}
		printf("请正确输入月份(1~12): ");
	}while(true);

	printf("请输入截止时间(日)：");
	int res_day = 0;
	do {
		scanf("%d",&endtm.tm_mday);
		if(res_day<=31 && res_day>=1)
		{
			endtm.tm_mday = res_day;
			break;
		}
		printf("请正确输入日期(1~31): ");
	}while(true);

	int result = saveCard(aName, aPwd, fBalance, endtm);
	if(result) printf("\n卡创建成功！\n\n");
	else printf("\n卡创建失败！\n\n");
}

void printCard() {
	char aName[18]={0};
	char pName[18]={0};
	int pIndex;
	Node* pres = NULL;
	int opt;
	int flag = 0;
	printf("\n查询卡:\n请选择查询类型:\n------------\n1. 精确查找\n2. 模糊查找\n------------\n\n请选择(1~2) : ");
	int whileFlag = 1;
	while(whileFlag){
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:	
				// 精确查找
				printf("请输入精确查找查询卡号(1~16)：");
				scanf("%s",aName);
				Card* ares = queryCard(aName);
				if(ares == NULL){
					printf("没要查找到相应数据\n");
					return;
				}
				printCardInfo(ares,1);
				whileFlag = 0;
				break;
			case 2:
				// 模糊查找
				printf("请输入模糊查找内容(1~16): ");
				scanf("%s",pName);
				pres = queryCards(pName,&pIndex);
				if(pres->next == NULL) {
					printf("没要查找到相应数据\n");
					return;
				}
				flag = 1;
				while(pres->next!=NULL){
					pres = pres->next;
					printCardInfo(pres->data,flag);
					flag = 0;
				}
				whileFlag = 0;
				break;
			default: printf("输入错误，请重新输入 : ");
		}
	}
	printf("\n");
}

void useComputer() {
	char aName[18]={0};

	printf("上机\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	Card* rescard = queryCard(aName);
	if(rescard == NULL) {
		printf("卡号不存在\n");
		return;
	}
	if(rescard->fBalance<=0.0) {
		printf("余额不足，请先充值\n");
		return;
	}
	rescard->nStatus = 1;
	rescard->tLast = time(NULL);
	// 上机日志储存
	addLogToList(rescard,1,time(0));
	printf("上机成功\n");
}

void exitComputer() {
	char aName[18]={0};

	printf("下机\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	Card* rescard = queryCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	// 信息更新
	rescard->nStatus = 0;
	float cost = ((time(NULL)-rescard->tLast)/60/60+1)*5;//每小时五块钱
	rescard->fBalance -= cost;
	rescard->fTotalUse += cost;
	rescard->nUseCount +=1;
	// 下机日志储存
	addLogToList(rescard,0,time(0));
	printf("下机成功\n");
}

void topUp() {
	char aName[18]={0};
	float money=0;

	printf("充值\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	printf("请输入充值金额: ");
	scanf("%f",&money);
	Card* rescard = queryCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	rescard->fBalance += money;
	addOptLogToList(rescard,1,time(0),money,rescard->fBalance-money,rescard->fBalance);
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
	Card* rescard = queryCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	if(rescard->fBalance >= money)
	{
		rescard->fBalance -= money;
		addOptLogToList(rescard,2,time(0),money,rescard->fBalance+money,rescard->fBalance);
		printf("退费成功\n");
	}else{
		printf("余额不足。（余额：%f)\n",rescard->fBalance);
	}
}

void searchAll() {
	printf("查询统计: \n");
	printAll(&card);
}

void exitCard() {
	char aName[18]={0};

	printf("注销卡\n");
	printf("请输入卡号: ");
	scanf("%s",aName);
	Card* rescard = queryCard(aName);
	if(rescard == NULL){
		printf("卡号不存在\n");
		return;
	}
	rescard->nStatus = 2;
	addOptLogToList(rescard,0,time(0),0,0,0);
	printf("注销成功\n");
}