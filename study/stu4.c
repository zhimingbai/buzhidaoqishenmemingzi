//双链表
#include <stdio.h>
#include <stdlib.h>

#define TURE 1
#define FALSE 0

/*
 * 双链表因为本身的特性原因，因而会有连个指针域
 * 其中pre指针是指向上一个节点的指针，next指向下一个节点的指针
 */
//创建节点
typedef struct Node {
    int data;
    struct Node *pre;
    struct Node *next;
} Node, LinKList;

//初始化节点
Node *createNode(int data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->pre = NULL;
    node->next = NULL;
    return node;
}

//初始化链表
Node *createLinkList() {
    Node *list = (Node *) malloc(sizeof(Node));
    list->data = 0;
    list->pre = NULL;
    list->next = NULL;
    return list;
}

//头插法
void insertHead(LinKList *list, int data) {
    Node *newNode = createNode(data);
    //这里可以判断一下是否是第一次插入，因为第一次插入的时候仅仅只会操作来两个指针
    if (list->next == NULL) {
        //链表为空
        newNode->next = list->next;
        newNode->pre = list;
        list->next = newNode;
        list->data++;
    } else {
        //当链表不为空的时候
        newNode->pre = list;
        newNode->next = list->next;
        list->next->pre = newNode;
        list->next = newNode;
        list->data++;
    }
}

//尾插法
void initTail(LinKList *list, int data) {
    //创建一个newNode表示用于插入的节点
    Node *newNode = createNode(data);
    //创建一个pMoveNode节点用于遍历链表
    Node *pMoveNode = list;
    //当pMoveNode的next等于NULL时退出循环，此时pMoveNode就是链表的最后一个节点
    while (pMoveNode->next != NULL) {
        pMoveNode = pMoveNode->next;
    }
    //进行插入操作
    pMoveNode->next = newNode;
    newNode->pre = pMoveNode;
    newNode->next = NULL;
    list->data++;
}

//删除链表中的节点
int deleteNode(LinKList *list, int data) {
    Node *deleteNode = list->next;
    while (deleteNode != NULL) {
        if (deleteNode->data == data) {
            //表示找到对应的链表的节点,删除节点
            //同时这里还需要判断是否是最后一个节点
            if (deleteNode->next != NULL) {
                deleteNode->pre->next = deleteNode->next;
                deleteNode->next->pre = deleteNode->pre;
                free(deleteNode);
                list->data--;
            } else {
                deleteNode->pre->next=NULL;
                free(deleteNode);
                list->data--;
            }
            return TURE;
        }
        deleteNode = deleteNode->next;
    }
    return FALSE;
}

//打印链表
void printLinkList(LinKList *list) {
    //创建一个pMoveNode为第一节点，用于遍历所有节点
    Node *pMoveNode = list->next;
    //用于遍历循环，同时当pMoveNode等于NUUL时退出循环
    while (pMoveNode != NULL) {
        printf("(%d)->", pMoveNode->data);
        //用于遍历的核心条件
        pMoveNode = pMoveNode->next;
    }
    printf("NULL\n");
}

int main() {
    LinKList *list = createLinkList();
    printf("头插法\n");
    insertHead(list, 1);
    insertHead(list, 2);
    insertHead(list, 3);
    insertHead(list, 4);
    insertHead(list, 5);
    printLinkList(list);
    printf("尾插法\n");
    initTail(list, 6);
    initTail(list, 7);
    initTail(list, 8);
    initTail(list, 9);
    initTail(list, 10);
    printLinkList(list);
    printf("删除之后的链表");
    while (TURE){
        int num=0, deleteData=0;
        printf("输入0表示退出程序\n输入1表示执行删除操作\n输入2表示打印链表\n");
        scanf("%d",&num);
        switch (num) {
            //表示执行删除操作
            case 1:
                printf("请输入你想删除的节点的数据\n");
                scanf("%d",&deleteData);
                int lb=deleteNode(list,deleteData);
                if(lb==FALSE){
                    printf("该数据为（%d）的节点删除失败，请检查\n",deleteData);
                } else{
                    printf("已完成删除操作，请打印链表查看是否完成删除操作\n");
                }
                break;
            //表示执行打印操作
            case 2:
                printLinkList(list);
                break;
            //表示执行退出操作
            case 0:
                return 0;
                break;
        }
    }
}