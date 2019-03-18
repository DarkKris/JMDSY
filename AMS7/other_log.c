#include "main.h"

extern other_log optLog;

void initOptLog() {
	optLog.next=NULL;
	optLog.card=NULL;
}

void addOptLogToList(Card *card, int opt, time_t time, int money, int pre_money, int after_money) {
	other_log *now = &optLog;
	while(now->next!=NULL) {
		now = now->next;
	}
	// 建立新的节点
	other_log *res = (other_log*)malloc(sizeof(other_log));
	res->card = card;
	res->opt = opt;
	res->time = time;
	res->next = NULL;
	res->money = money;
	res->pre_money = card->fBalance - money;
	res->after_money = card->fBalance;
	// 储存
	now->next = res;
}

other_log* searchOptLog(char *aName) {
	other_log *ret;
	ret->next = NULL;
	ret->card = NULL; //init

	other_log *retnow = ret;
	other_log *now = &optLog;

	while(now->next!=NULL) {
		now = now->next;
		if(strcmp(now->card->aName,aName)==0) {
			other_log *new = (other_log*)malloc(sizeof(other_log));
			// save info
			new->card = now->card;
			new->next = NULL;
			new->opt = now->opt;
			new->time = now->time;
			new->money = now->money;
			new->pre_money = now->pre_money;
			new->after_money = now->after_money;
			// insert
			retnow->next = new;
			retnow = ret->next;
		}
	}
	return ret;
}