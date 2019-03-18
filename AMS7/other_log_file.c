#include "main.h"

extern other_log optLog;
char logs[MAXCARDNUMBER+1][5000];
int allOptLogRow = 0;

void readOptLog() {
	// read all of Cards info from file "option_log.txt"
	FILE* logFile = fopen("option_log.txt", "r");
	int row = 1;

	while(~fscanf(logFile, "%s", logs[row])){
		for(int i=1;i<=6;i++) // i的上限是参数数量
		{
			char res[500]={0};
			fscanf(logFile, "%s", res);
			strcat(logs[row]," ");
			strcat(logs[row],res);
		}
		row++;
	}
	allOptLogRow = row-1;
	fclose(logFile);
}

void praseOptLog() {
	for(int i=1;i<=allOptLogRow;i++)
	{
		other_log *log = (other_log*)malloc(sizeof(other_log));
		char aName[18]={0};
		char time[50]={0};
		sscanf(logs[i],"%s %d %s %d %d %d",aName,&log->opt,time,&log->money,&log->pre_money,&log->after_money);
		log->card = queryCard(aName);
		log->time = stringToTime(time);
		addOptLogToList(log->card,log->opt,log->time,log->money,log->pre_money,log->after_money);
		free(log);
	}
}

// 将操作日志写入文件（行）
void saveOptLog(other_log *log) {
	FILE* logFile = fopen("option_log.txt", "a+");
	if(log->opt==0) {
		fprintf(logFile, "%s %d %ld %d %d %d\n",log->card->aName,log->opt,log->time,0,0,0);
	}else {
		fprintf(logFile, "%s %d %ld %d %d %d\n",log->card->aName,log->opt,log->time,log->money,log->pre_money,log->after_money);
	}
	fclose(logFile);
}

void updateOptLog() {
	FILE* logFile = fopen("option_log.txt", "w+");
	other_log *now = &optLog;
	while(now->next!=NULL){
		now = now->next;
		saveOptLog(now);
	}
	fclose(logFile);
}