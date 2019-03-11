#include "main.h"

void initCardList(Node* head) {
	head->next = NULL;
	head->data = NULL;
}

Card* queryCard(char* aName) {
	Node* now = &card;
	while(now->next != NULL){
		now = now->next;
		if(strcmp(now->data->aName,aName)==0)
			return now->data;
	}
	return NULL;
}

Node* queryCards(const char* pName , int* pIndex) {
	Node* pCard = (Node*)malloc(sizeof(Node));//保存查询到的符合条件的卡信息。
	Node* now = &card;
	//遍历链表
	while (now->next != NULL)
	{
		now = now->next;
		//判断当前结点中的卡号是否包含输入的关键字
		if(strstr(now->data->aName,pName) != NULL)
		{
		    //如果包含，则保存结点中的数据
		    addToList(now->data, pCard);
		}
		//如果不相同，则将p指针指向下一个结点
	}
	return pCard;
}