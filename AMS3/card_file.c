#ifndef __MAIN_H__
	#define __MAIN_H__
	#include "main.h"
#endif
#define MAXCARDNUMBER 1000000
#include "tool.c"

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

int nowCardNum = 0;
Card card[MAXCARDNUMBER+1];
char rows[MAXCARDNUMBER+1][5000]={0};
int allRow = 0;

cardFile = open("card.txt", "rw");

int readCard() {
	// read all of Cards info from file "card.txt"
	int row = 1;
	while(~scanf("%s",rows[row])) row++;
	allRow = row;
	return 1;
}

int parseCard() {
	// parse String from "readCard" function and storage it to "struct Card"
	nowCardNum=0;
	for(int i=1;i<=allRow;i++)
	{
		char tStart[50];
		char tEnd[50];
		char tLast[50];
		nowCardNum++;
		sscanf(rows[i],"%s,%s,%d,%s,%s,%f,%s,%d,%f,%d",card[nowCardNum].aName,card[nowCardNum].aPwd,&card[nowCardNum].nStatus,tStart,tEnd,&card[nowCardNum].fTotalUse,tLast,&card[nowCardNum].nUseCount,&card[nowCardNum].fBalance,&card[nowCardNum].nDel);
		card[nowCardNum].tStart = stringToTime(tStart);
		card[nowCardNum].tEnd = stringToTime(tEnd);
		card[nowCardNum].tLast = stringToTime(tLast);
	}
	return 1;
}

int saveCard(char* aName, char* aPwd, float fBalance, struct tm endtm) {
	// save Card info from file "card.txt"
	if(nowCardNum == MAXCARDNUMBER) return 0;
	nowCardNum++;

	time_t nowTime = time(0);

	fprintf(cardFile, "%s,", aName);			// 卡号
	fprintf(cardFile, "%s,", aPwd);				// 密码
	fprintf(cardFile, "%d,", 0);				// 卡状态
	fprintf(cardFile, "%d,", nowTime);			// 开卡时间
	fprintf(cardFile, "%d,", mktime(&endtm));	// 截止时间
	fprintf(cardFile, "%f,", 0);				// 累计金额
	fprintf(cardFile, "%d,", nowTime);			// 最后使用时间
	fprintf(cardFile, "%d,", 0);				// 使用次数
	fprintf(cardFile, "%f,", fBalance);			// 余额
	fprintf(cardFile, "%d\n", 0);				// 删除标识

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
