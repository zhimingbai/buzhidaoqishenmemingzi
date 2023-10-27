//单链表

#include <stdio.h>
#include <stdlib.h>

//声明数据域
typedef struct {
	double score;
} elemType;

//声明结点的类型和指向结点的指针类型
typedef struct lnode {
	//节点数据域
	elemType data;
	//节点指针域
	struct lnode *next;
	//LinkList为指向结构体Lnode的指针类型
} lNode, *linkList;

//创建节点
//为了我们的链表最后进入死循环，
// 因此我们创建的每一个节点时都需要newNode->next = newNode;
lNode *createNode(elemType e) {
	lNode *newNode = (lNode *) (struct Node *) malloc(sizeof(lNode));
	newNode->data = e;
	newNode->next = newNode;
	return newNode;
}

//单链表的初始化
void initList(linkList list) {
	//list初始化，给他分配内存空间
	list = (linkList) malloc(sizeof(lNode));
	//指针指向NULL
	list->next = NULL;
}

//判断链表是否为空
int listEmpty(linkList list) {
	//若list为空则返回1，反之返回0
	if (list->next == NULL) {
		return 1;
	} else {
		return 0;
	}
}

//单链表的删除，完全删除，按理来说应该是把头结点也删除了
//但是这种方法我目前还没有看明白，暂时可以使用下面那个方法
int deleteList(linkList list) {
	//声明一个 lNode 类型的指针 pMoveNode，用于跟踪要删除的节点。
	lNode *pMoveNode;
	//当list==NULL的时候跳出循环
	while (list != NULL) {
		/*
		 * 将当前节点（列表）的地址赋值给 pMoveNode。
		 * 更新列表指针，使其指向列表中的下一个节点。
		 * 使用 free() 函数释放分配给 pMoveNode 的内存。
		 */
		pMoveNode = list;
		/*
		 * 因为先执行list = list->next ，在执行free(pMoveNode)
		 */
		list = list->next;
		free(pMoveNode);
	}
	//如果链表销毁成功，返回1，不成功返回0。
	if (listEmpty(list) == 1) {
		return 1;
	} else {
		return 0;
	}
}

//清空单链表，链表仍然存在，单链表中没有元素，成为空链表（头指针和头结点仍然存在）
void clearList(linkList list) {
	lNode *p, *q;
	p = list->next;
	//当p->next==NULL时跳出循环
	while (p->next != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
	/*
	 * 如果想现在把头结点也删除可以这样写
	 * list->next = list->next->next;
	 * 此时头结点的指针就指向NULL了。
	 */
	//头结点指针域指向空
	list->next = NULL;
	printf("清空单链表已完成\n");
}

//求单链表的表长，返回list中数据元素个数（不包含头结点）
/*
 * 主要思路是
 * 从首元结点开始，依次计数所有节点，当然需要跳过头结点
 */
int listLength(linkList list) {
	//声明一个 lNode 类型的指针 pMoveNode，用于跟踪要遍历的节点。
	lNode *pMoveNode = list->next;
	//定义一个cnt用于计数
	int cnt = 0;
	while (pMoveNode != NULL) {
		cnt++;
		pMoveNode = pMoveNode->next;
	}
	return cnt;
}

//遍历单链表的数据元素
void printList(linkList list) {
	//声明一个 lNode 类型的指针 pMoveNode，用于跟踪要遍历的节点。
	//pMoveNode为第一节点
	lNode *pMoveNode = list->next;
	while (pMoveNode != NULL) {
		printf("(%.2f)->", pMoveNode->data.score);
		pMoveNode = pMoveNode->next;
	}
}

//取值--取单链表中第i个元素的内容
/*
 * 取值的时候，只能从链表的头指针开始出发，顺着next逐个节点往下搜索，直至搜索到第i个节点为止，
 * 因此链表不是随机存储结构。
 */
//获取线性表中list的中的第i个元素，通过变量e进行返回
int getElem_L(linkList list, int i) {
	//声明一个 lNode 类型的指针 pMoveNode，用于跟踪要遍历的节点。
	//pMoveNode为第一节点
	lNode *pMoveNode = list->next;
	//cnt表示计数
	int cnt = 1;
	//当pMoveNode==NULL或cnt>=i的时候，跳出循环
	while (pMoveNode != NULL || cnt < i) {
		pMoveNode = pMoveNode->next;
		cnt++;
	}
	if (pMoveNode == NULL || cnt > i) {
		printf("第i个元素不存在\n");
		return 0;
	} else {
		//取得第i个元素的数据
		printf("第%d个元素，(%.2f)", i, pMoveNode->data.score);
		return 1;
	}
}

//查找--按值查找，根据指定数据获取该数据在链表当中的位置
/*
 * 算法步骤：
 * 1、从第一个节点起，依次和e进行比较
 * 2、如果找到一个值与e相等的数据元素，则返回其在链表中的地址或则是位置
 */
int locateElem_L(linkList list,elemType e){
	//声明一个 lNode 类型的指针 pMoveNode，用于跟踪要遍历的节点。
	//pMoveNode为第一节点
	lNode *pMoveNode = list->next;
	//cnt表示计数
	int cnt = 1;
	//当pMoveNode == NULL的时候跳出循环
	while (pMoveNode != NULL) {
		//如果成绩相等，那么就返回此时的cnt
		if ( pMoveNode->data.score == e.score) {
			return cnt;
		}
		pMoveNode = pMoveNode->next;
		cnt++;
	}
	return 0;
}

//插入节点
/*
 * 算法步骤：
 * 1、首先找到ai-1的存储位置p。
 * 2、生成一个数据域e的新节点。
 * 3、插入新节点：1-新节点的指针指向节点ai 2-节点ai-1的指针域指向新的节点
 */
int listInsert_L(linkList list,int position,elemType e){
	//声明一个 lNode 类型的指针 pMoveNode，用于跟踪要遍历的节点。
	//pMoveNode为第头节点，要从头节点开始
	lNode *pMoveNode=list;
	//cnt表示计数，要从0开始
	int cnt = 0;
	while (pMoveNode!=NULL||cnt<position-1){
		cnt++;
		pMoveNode=pMoveNode->next;
	}
	if(pMoveNode==NULL||cnt>position-1){
		return -1;
	}
	//创建新节点
	linkList newNode= (linkList)malloc(sizeof(lNode));
	//1-新节点的指针指向节点ai
	//2-节点ai-1的指针域指向新的节点
	newNode->next=pMoveNode->next;
	newNode->data=e;
	pMoveNode->next=newNode;
	return 0;
}

//删除：删除第i个节点
/*
 * 1、首先找到ai-1的存储位置p，保存要删除的ai的值
 * 2、令p->next指向ai+1
 * 3、释放原本为ai的内存
 */
int listDelete(linkList list, int i, elemType *e){
	//声明一个 lNode 类型的指针 pMoveNode，用于跟踪要遍历的节点。
	//pMoveNode为第头节点，要从头节点开始
	lNode *pMoveNode=list;
	//cnt表示计数，要从0开始
	int cnt=0;
	//当pMoveNode==NULL或者cnt >= 1 - 1的时候退出循环，就可以找到i-1位置上的节点
	while (pMoveNode!=NULL|| cnt < i - 1){
		pMoveNode= pMoveNode->next;
		cnt++;
	}
	//判断是否越界
	if(cnt>i-1||pMoveNode->next==NULL){
		return -1;
	}
	//保存要删除的ai节点的地址
	lNode *pFree=pMoveNode->next;
	*e=pFree->data;
	//这一步也可以这样写pMoveNode->next=pMoveNode->next->next
	pMoveNode->next=pFree->next;
	free(pFree);
	return 0;
}

//头插法
void headInsert(linkList list, elemType e) {
	lNode *newNode = createNode(e);
	//头插法的基本格式保持不变
	newNode->next = list->next;
	list->next = newNode;
}

//尾插法：
void tailInsertion(linkList list, elemType e) {
	//创建插入节点newNode
	lNode *newNode = createNode(e);
	//创建一个过渡节点,方便我们找到链表最后一个节点，并让过渡节点等于头节点
	lNode *lastNode = list;
	//一直循环，让lastNode变成该链表的最后一个节点，当lastNode->next == NULL的时候退出循环
	while (lastNode->next != NULL){
		lastNode=lastNode->next;
	}
	//然后让过渡节点的next指向newNode
	lastNode->next=newNode;
}
int main() {
	//定义链表
	linkList *list;
	return 0;
}