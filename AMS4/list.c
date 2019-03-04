#include "main.h"

/* 链表 */

void initList() {
	list.id = -1;
	list.next = NULL;
}

void addNode(int id) {
	Node* now = &list;
	while(now->next!=NULL) now = now->next;
	Node* res = (Node*)malloc(sizeof(Node));
	res->next = NULL;
	res->id = id;
	now->next = res;
}

void deleteNode(int id) {
	Node* now = &list;
	Node* front = NULL;
	while(now->next!=NULL) {
		front = now;
		now = now->next;
		if(now->id == id) {
			front->next = now->next;
			break;
		}
	}
}

int searchNode(int id) {
	int i = 0;
	Node* now = &list;
	while(now->next!=NULL){
		now = now->next;
		i++;
		if(now->id == id) {
			return i;
		}
	}
	return 0;
}

void printAll() {
	Node *now = &list;
	while(now->next!=NULL) {
		now = now->next;
		printf("%d -> ",now->id);
	}
}