#include <stdio.h>
#include <stdlib.h>

int opt; // opt the user chosed in the menu

void outputMenu() {
	printf("欢迎进入计费管理系统\n----------菜单----------\n");
	printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n0.退出");
	printf("\n------------------------\n");
	printf("请输入功能编号：");
	scanf("%d",&opt);
}

void addCard() {
	printf("添加卡\n");
}

void searchCard() {
	printf("查询卡\n");
}

void useComputer() {
	printf("上机\n");
}

void exitComputer() {
	printf("下机\n");
}

void topUp() {
	printf("充值\n");
}

void withdraw() {
	printf("退费\n");
}

void searchAll() {
	printf("查询统计\n");
}

void exitCard() {
	printf("注销卡\n");
}

void main() {
	do {
		outputMenu();
		switch(opt){
		case 1:addCard();break;
		case 2:searchCard();break;
		case 3:useComputer();break;
		case 4:exitComputer();break;
		case 5:topUp();break;
		case 6:withdraw();break;
		case 7:searchAll();break;
		case 8:exitCard();break;
		}
	}while(opt != 0);
	// return 0;
}
