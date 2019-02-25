#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAXCARDNUMBER 1000000
// #define DEBUG

typedef struct Card
{
	char	aName[18];		//卡号
	char	aPwd[8];		//密码
	int		nStatus;		//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t	tStart;			//开卡时间
	time_t	tEnd;			//卡的截止时间
	float	fTotalUse;		//累计金额
	time_t	tLast;			//最后使用时间
	int		nUseCount;		//使用次数
	float	fBalance;		//余额
	int		nDel;			//删除标识 0-未删除，1-删除
}Card;

int opt; // opt the user chosed in the menu
int nowCardNum = 0;
Card card[MAXCARDNUMBER+1];

void outputMenu() {
	printf("----------菜单----------\n");
	printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n0.退出");
	printf("\n------------------------\n");
	printf("请输入功能编号：(0~8)");
	scanf("%d",&opt);
}

/*
Controller 层
*/
int initCard(char* aName, char* aPwd, float fBalance, struct tm endtm) {
	if(nowCardNum == MAXCARDNUMBER) return 0;
	nowCardNum++;
	strcpy(card[nowCardNum].aName,aName);	// 卡号
	strcpy(card[nowCardNum].aPwd,aPwd);		// 密码
	card[nowCardNum].fBalance = fBalance;	// 余额
	card[nowCardNum].tStart = time(0);		// 开卡时间
	card[nowCardNum].tLast = card[nowCardNum].tStart;	// 最后使用时间
	card[nowCardNum].tEnd = mktime(&endtm);				// 截止时间
	
	card[nowCardNum].nDel = 0;				// 删除标识
	card[nowCardNum].nUseCount = 0;			// 使用次数
	card[nowCardNum].fTotalUse = 0;			// 累计金额
	card[nowCardNum].nStatus = 0;			// 卡状态
	return 1;
}

Card* searchCard(char *aName) {
	for(int i=1;i<=nowCardNum;i++)
	{
		if(strcmp(card[i].aName,aName)==0)
		{
			return &card[i];
		}
	}
	return NULL;
}
/*
Controller 层 结束
*/


/*
View 层
*/
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
	int result = initCard(aName, aPwd, fBalance, endtm);
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
/*
View 层 结束
*/

void main() {
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
	// return 0;
}
