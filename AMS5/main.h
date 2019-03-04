#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAXCARDNUMBER 10000000
#define _CRT_SECURE_NO_WARNINGS
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

typedef struct Node
{
	Card* data;
	struct Node* next;
}Node;


/* Menu */
void outputMenu();
void addCard();
void printCard();
void useComputer();
void exitComputer();
void topUp();
void withdraw();
void searchAll();
void exitCard();
/* Card File */
int saveCard(char* aName, char* aPwd, float fBalance, struct tm endtm);
int readCard();
int parseCard();
/* Tool */
time_t stringToTime(char* s);
/* List */
void addToList(Card* a);
int deleNode(char* aName);
Card* searchList(char *aName);
void printAll();
/* Card Service */
void initCardList();
Card* queryCard(char *aName);


int opt;			 // opt that the user chosen in the menu
int nowCardNum=0;
Node card;

#endif