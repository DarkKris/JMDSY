#include "main.h"

void initCardList() {
	card.next = NULL;
	card.data = NULL;
}

Card* queryCard() {
	Node* now = &card;
	while(now->next != NULL){
		now = now->next;
		if(strcmp(now->data->aName,aName)==0)
			return now->data;
	}
	return NULL;
}