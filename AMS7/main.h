#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAXCARDNUMBER 100000
#define _CRT_SECURE_NO_WARNINGS
#define true 1
#define false 0

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

typedef struct login_log
{
	Card* card;
	int opt; // opt-1:下机 0:上机
	time_t time;
	struct login_log *next;
}login_log;

typedef struct other_log
{
	Card* card;
	int opt; 			// opt-0:注销卡 1:充值 2:退费
	int money;			// 当opt==1 or 2时：操作所涉及的金额 ；opt==0:money=0
	int pre_money;		// 当opt==1 or 2时：操作前的金额 ；opt==0:pre_money=0
	int after_money;	// 当opt==1 or 2时：操作后的金额 ；opt==0:after_money=0
	time_t time;
	struct other_log *next;
}other_log;

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
void updateSave(Card* data);
void updateSaveAll();

/* Tool */
time_t stringToTime(char* s);
void printCardInfo(const Card* res, int haveHead);

/* List */
void addToList(Card* a, Node* head);
int deleNode(char* aName, Node* head);
Card* searchList(char *aName,Node* head);
void printAll(Node* head);

/* Card Service */
void initCardList();
Card* queryCard(char *aName);
Card* queryCard();
Node* queryCards(const char* pName , int* pIndex);

/* Login Log */
void initLoginLog();
void addLogToList(Card *card, int opt, time_t time);
login_log* searchLog(char *aName);

/* Login Log File*/
void readLog();
void praseLog();
void saveLog();
void updateLog();

/* other Log */
void initOptLog();
void addOptLogToList(Card *card, int opt, time_t time, int money, int pre_money, int after_money);
other_log* searchOptLog(char *aName);

/* other Log File */
void readOptLog();
void praseOptLog();
void saveOptLog(other_log *log);
void updateOptLog();


int opt;				// opt that the user chosen in the menu
int nowCardNum;
Node card;				// card List
login_log loginLog;		// login_log List
other_log optLog;			// log List for topup , withdraw and exitCard

#endif