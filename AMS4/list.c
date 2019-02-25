#include "main.h"

void addToList(Card* a) {
	Node* now = &card;
	while(now->next != NULL) now = now->next;
	Node res;
	res.data = a;
	res.next = NULL;
	now->next = &res;
}

Card* searchList(char *aName) {
	Node* now = &card;
	while(now->next != NULL){
		now = now->next;
		if(strcmp(now->data->aName,aName)==0)
			return now->data;
	}
	return NULL;
}

int deleNode(char* aName) {
	Node* front = NULL;
	Node* now = &card;

	while(now->next != NULL) {
		front = now;
		now = now->next;
		if(strcmp(now->data->aName,aName)==0){
			front->next = now->next;
			free(now);
		}
		return 1;
	}
	return 0;
}

void printAll() {
	Node* now = &card;
	while(now->next != NULL) {
		now = now->next;
		printf("%s\n",now->data->aName);
	}
}