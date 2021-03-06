#include "main.h"

char rows[MAXCARDNUMBER+1][5000]={0};
int allRow = 0;

int readCard() {
	// read all of Cards info from file "card.txt"
	FILE* cardFile = fopen("card.txt", "r");
	int row = 1;

	while(~fscanf(cardFile, "%s", rows[row])){
		for(int i=1;i<=9;i++)
		{
			char res[500]={0};
			fscanf(cardFile, "%s", res);
			strcat(rows[row]," ");
			strcat(rows[row],res);
		}
		row++;
	}
	allRow = row-1;
	fclose(cardFile);
	return 1;
}

int parseCard() {
	// parse String from "readCard" function and storage it to "struct Card"
	nowCardNum=0;
	for(int i=1;i<=allRow;i++)
	{
		char tStart[50]={0};
		char tEnd[50]={0};
		char tLast[50]={0};
		nowCardNum++;
		sscanf(rows[i],"%s %s %d %s %s %f %s %d %f %d",card[nowCardNum].aName,card[nowCardNum].aPwd,&card[nowCardNum].nStatus,tStart,tEnd,&card[nowCardNum].fTotalUse,tLast,&card[nowCardNum].nUseCount,&card[nowCardNum].fBalance,&card[nowCardNum].nDel);
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

	FILE* cardFile = fopen("card.txt", "a+");

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

	fprintf(cardFile, "%s ", aName);		 		// 卡号
	fprintf(cardFile, "%s ", aPwd);				// 密码
	fprintf(cardFile, "%d ", 0);				// 卡状态
	fprintf(cardFile, "%ld ", nowTime);			// 开卡时间
	fprintf(cardFile, "%ld ", mktime(&endtm));	// 截止时间
	fprintf(cardFile, "%f ", 0.0);				// 累计金额
	fprintf(cardFile, "%ld ", nowTime);			// 最后使用时间
	fprintf(cardFile, "%d ", 0);				// 使用次数
	fprintf(cardFile, "%f ", fBalance);			// 余额
	fprintf(cardFile, "%d\n", 0);				// 删除标识

	fclose(cardFile);

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
