#include "main.h"

extern login_log loginLog;
char logs[MAXCARDNUMBER+1][5000];
int allLogRow = 0;

void readLog() {
	// read all of Cards info from file "login_log.txt"
	FILE* logFile = fopen("login_log.txt", "r");
	int row = 1;

	while(~fscanf(logFile, "%s", logs[row])){
		for(int i=1;i<=3;i++) // i的上限是参数数量
		{
			char res[500]={0};
			fscanf(logFile, "%s", res);
			strcat(logs[row]," ");
			strcat(logs[row],res);
		}
		row++;
	}
	allLogRow = row-1;
	fclose(logFile);
}

void praseLog() {
	for(int i=1;i<=allLogRow;i++)
	{
		login_log *log = (login_log*)malloc(sizeof(login_log));
		char aName[18]={0};
		char time[50]={0};
		sscanf(logs[i],"%s %d %s",aName,&log->opt,time);
		log->card = queryCard(aName);
		log->time = stringToTime(time);
		addLogToList(log->card,log->opt,log->time);
		free(log);
	}
}

void saveLog(login_log *log) {
	FILE* logFile = fopen("login_log.txt", "a+");
	fprintf(logFile, "%s %d %ld\n",log->card->aName,log->opt,log->time);
	fclose(logFile);
}

void updateLog() {
	FILE* logFile = fopen("login_log.txt", "w+");
	login_log *now = &loginLog;
	while(now->next!=NULL){
		now = now->next;
		saveLog(now);
	}
	fclose(logFile);
}