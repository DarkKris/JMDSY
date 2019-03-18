#include "main.h"

char rows[MAXCARDNUMBER+1][5000];
int allRow = 0;
extern int nowCardNum;

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
		Card* rescard = (Card*)malloc(sizeof(Card));
		char tStart[50]={0};
		char tEnd[50]={0};
		char tLast[50]={0};
		nowCardNum++;
		sscanf(rows[i],"%s %s %d %s %s %f %s %d %f %d",rescard->aName,rescard->aPwd,&rescard->nStatus,tStart,tEnd,&rescard->fTotalUse,tLast,&rescard->nUseCount,&rescard->fBalance,&rescard->nDel);
		rescard->tStart = stringToTime(tStart);
		rescard->tEnd = stringToTime(tEnd);
		rescard->tLast = stringToTime(tLast);
		addToList(rescard,&card);
	}
	return 1;
}

int saveCard(char* aName, char* aPwd, float fBalance, struct tm endtm) {
	// save Card info from file "card.txt"
	if(nowCardNum == MAXCARDNUMBER) return 0;
	nowCardNum++;

	time_t nowTime = time(0);
	Card rescard;
	FILE* cardFile = fopen("card.txt", "a+");

	strcpy(rescard.aName,aName);	// 卡号
	strcpy(rescard.aPwd,aPwd);		// 密码
	rescard.fBalance = fBalance;	// 余额
	rescard.tStart = nowTime;		// 开卡时间
	rescard.tLast = rescard.tStart;	// 最后使用时间
	rescard.tEnd = mktime(&endtm);	// 截止时间
	rescard.nDel = 0;				// 删除标识
	rescard.nUseCount = 0;			// 使用次数
	rescard.fTotalUse = 0;			// 累计金额
	rescard.nStatus = 0;			// 卡状态
	addToList(&rescard,&card);

	fprintf(cardFile, "%s ", aName);		 	// 卡号
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

void updateSave(Card* data) {
	FILE *cardFile = fopen("card.txt","a+");

	fprintf(cardFile, "%s ", data->aName);		 	// 卡号
	fprintf(cardFile, "%s ", data->aPwd);			// 密码
	fprintf(cardFile, "%d ", data->nStatus);		// 卡状态
	fprintf(cardFile, "%ld ", data->tStart);		// 开卡时间
	fprintf(cardFile, "%ld ", data->tEnd);			// 截止时间
	fprintf(cardFile, "%f ", data->fTotalUse);		// 累计金额
	fprintf(cardFile, "%ld ", data->tLast);			// 最后使用时间
	fprintf(cardFile, "%d ", data->nUseCount);		// 使用次数
	fprintf(cardFile, "%f ", data->fBalance);		// 余额
	fprintf(cardFile, "%d\n", data->nDel);			// 删除标识
	fclose(cardFile);
}

void updateSaveAll() {
	FILE *cardfile = fopen("card.txt","w+");// 清空文件
	fclose(cardfile);
	Node* now = &card;
	while(now->next != NULL) {
		now = now->next;
		Card* res = now->data;
		updateSave(res);
	}
}
