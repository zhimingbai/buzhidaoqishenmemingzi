//简单的单链表的书写
#include <stdio.h>
#include <stdlib.h>
//声明节点
typedef struct Node{
	int data;
	struct Node *next;
}Node,linkList;
//创建节点
Node *createNode(int data) {
	//创建结构体变量
	Node *newNode = (struct Node *) malloc(sizeof(struct Node));
	//新节点的数值域等于传进的数值
	newNode->data = data;
	//新节点的指针域指向NULL
	newNode->next = NULL;
	//返回新节点
	return newNode;
}

//创建一个空的单链表，并返回指向该单链表头结点的指针。
linkList *createLinkList(){
	linkList *list = (linkList*)malloc(sizeof(linkList));
	list->data=0;
	list->next=NULL;
	return list;
}
//头插法：插入节点，参数：插入哪个链表，插入节点的数据是多少
void insertHead(linkList *headNode,int data){
	Node *newNode= createNode(data);
	newNode->next=headNode->next;
	headNode->next=newNode;
}
//尾插法
void insertTail(linkList *list,int data){
	Node *newNode= createNode(data);
	Node *lastNode=list;
	while (lastNode->next!=NULL){
		lastNode=lastNode->next;
	}
	lastNode->next=newNode;
}
//删除链表指定位置节点
void deleteNode(linkList *list,int deleteData){
	struct Node *deleteNode = list->next;
	struct Node *deleteNodeFront = list;
	if(deleteNode==NULL){
		printf("无法删除链表，链表为空\n");
		return;
	} else{
		while (deleteNode->data!=deleteData){
			deleteNodeFront=deleteNode;
			deleteNode=deleteNode->next;
		}
		deleteNodeFront->next=deleteNode->next;
		free(deleteNode);
	}
	
}
//打印输出链表数据
void printList(struct Node *list) {
	//初始化pMove为list的下一个节点，即跳过头节点，指向链表的第一个实际节点（如果有的话）。
	Node *pMoveNode = list->next;
	//这是一个while循环，它会持续执行直到pMoveNode指向了链表的最后一个节点之后的NULL。
	//在循环中，我们遍历整个链表，每次迭代移动到下一个节点。
	while (pMoveNode != NULL) {
		//在循环内部，我们使用printf函数打印输出当前节点的数据域值。
		//pMoveNode->data表示当前节点的数据。
		printf("%d ", pMoveNode->data);
		pMoveNode = pMoveNode->next;
	}
	printf("\n");
}
int main(){
	linkList *list=createLinkList();
	printf("头插法\n");
	for (int i = 0; i < 30; ++i) {
		insertHead(list,i*10);
	}
	printList(list);
	printf("尾插法\n");
	for (int i = 30; i < 60; ++i) {
		insertTail(list,i*10);
	}
	printList(list);
	deleteNode(list,20);
	deleteNode(list,360);
	deleteNode(list,240);
	deleteNode(list,180);
	deleteNode(list,560);
	printf("删除之后\n");
	printList(list);
	return 0;
}