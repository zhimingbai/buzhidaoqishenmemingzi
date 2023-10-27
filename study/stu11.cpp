//简单的单链表的排序
#include <stdio.h>
#include <stdlib.h>

// 声明节点
typedef struct Node {
	int data;
	struct Node *next;
} Node, linkList;

// 创建节点
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

// 创建一个空的单链表，并返回指向该单链表头结点的指针。
linkList *createLinkList() {
	linkList *list = (linkList *)malloc(sizeof(linkList));
	list->next = NULL;
	return list;
}

// 头插法
void insertHead(linkList *headNode, int data) {
	Node *newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

// 尾插法
void insertTail(linkList *list, int data) {
	Node *newNode = createNode(data);
	Node *lastNode = list;
	while (lastNode->next != NULL) {
		lastNode = lastNode->next;
	}
	lastNode->next=newNode;
}

// 删除链表指定位置节点
void deleteNode(linkList *list, int deleteData) {
	Node *deleteNode = list->next;
	Node *deleteNodeFront = list;
	if (deleteNode == NULL) {
		printf("无法删除链表，链表为空\n");
		return;
	} else {
		while (deleteNode->data != deleteData) {
			deleteNodeFront = deleteNode;
			deleteNode = deleteNode->next;
		}
		deleteNodeFront->next = deleteNode->next;
		free(deleteNode);
	}
}

// 打印输出链表数据
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

// 有序插入单链表
void insertSorted(linkList *list, int data) {
	Node *newNode = createNode(data);
	if (list->next == NULL || list->next->data >= data) {
		newNode->next = list->next;
		list->next = newNode;
		return;
	} else {
		Node *pMoveNode = list->next;
		while (pMoveNode->next != NULL && pMoveNode->next->data < data) {
			pMoveNode = pMoveNode->next;
		}
		newNode->next = pMoveNode->next;
		pMoveNode->next = newNode;
	}
}

// 两个链表的有序合并，然后用listC进行输出
linkList *mergeList(linkList *listA, linkList *listB) {
	Node *pMa = listA->next;
	Node *pMb = listB->next;
	linkList *listC = createLinkList();
	Node *pMc = listC;
	while (pMa != NULL && pMb != NULL) {
		if (pMa->data <= pMb->data) {
			pMc->next = pMa;
			pMc = pMa;
			pMa = pMa->next;
		} else {
			pMc->next = pMb;
			pMc = pMb;
			pMb = pMb->next;
		}
	}
	pMc->next = pMa ? pMa : pMb;
	return listC;
}

// 无序单链表的有序排序
linkList *sortList(linkList *listA) {
	linkList *listB = createLinkList();
	Node *pMb = listA->next;
	while (pMb != NULL) {
		insertSorted(listB, pMb->data);
		pMb = pMb->next;
	}
	return listB;
}

int main() {
	linkList *listA = createLinkList();
	linkList *listB = createLinkList();
	linkList *listC;
	
	insertTail(listA, 1);
	insertTail(listA, 12);
	insertTail(listA, 5);
	insertTail(listA, 23);
	insertTail(listA, 11);
	insertTail(listA, 8);
	
	insertTail(listB, 2);
	insertTail(listB, 26);
	insertTail(listB, 16);
	insertTail(listB, 6);
	
	printf("原始链表A：");
	printList(listA);
	printf("原始链表B：");
	printList(listB);
	
	listA = sortList(listA);
	listB = sortList(listB);
	
	printf("有序排序之后的两个链表\n");
	printf("排序后的链表A：");
	printList(listA);
	printf("排序后的链表B：");
	printList(listB);
	
	printf("合并之后\n");
	listC = mergeList(listA, listB);
	printf("合并后的链表C：");
	printList(listC);
	
	return 0;
}


