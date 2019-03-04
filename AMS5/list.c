#include "main.h"

void addToList(Card* a, Node* head) {
	Node* now = head;
	while(now->next != NULL) now = now->next;
	Node* res = (Node*)malloc(sizeof(Node));
	res->data = a;
	res->next = NULL;
	now->next = res;
}

Card* searchList(char *aName, Node* head) {
	Node* now = head;
	while(now->next != NULL){
		now = now->next;
		if(strcmp(now->data->aName,aName)==0)
			return now->data;
	}
	return NULL;
}

int deleNode(char* aName, Node* head) {
	Node* front = NULL;
	Node* now = head;

	while(now->next != NULL) {
		front = now;
		now = now->next;
		if(strcmp(now->data->aName,aName)==0){
			front->next = now->next;
			free(now);
			return 1;
		}
	}
	return 0;
}

void printAll(Node* head) {
	Node* now = head;
	while(now->next != NULL) {
		now = now->next;
		printf("%s\n",now->data->aName);
	}
}