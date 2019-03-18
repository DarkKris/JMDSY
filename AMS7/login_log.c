#include "main.h"

extern login_log loginLog;

void initLoginLog() {
	loginLog.next=NULL;
	loginLog.card=NULL;
}

void addLogToList(Card *card, int opt, time_t time) {
	login_log *now = &loginLog;
	while(now->next!=NULL) {
		now = now->next;
	}
	login_log *res = (login_log*)malloc(sizeof(login_log));
	res->card = card;
	res->opt = opt;
	res->time = time;
	res->next = NULL;
	now->next = res;
}

login_log* searchLog(char *aName) {
	login_log *ret;
	ret->next = NULL;
	ret->card = NULL; //init

	login_log *retnow = ret;
	login_log *now = &loginLog;

	while(now->next!=NULL) {
		now = now->next;
		if(strcmp(now->card->aName,aName)==0) {
			login_log *new = (login_log*)malloc(sizeof(login_log));
			// save info
			new->card = now->card;
			new->next = NULL;
			new->opt = now->opt;
			new->time = now->time;
			// insert
			retnow->next = new;
			retnow = ret->next;
		}
	}
	return ret;
}