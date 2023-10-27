//链式栈的基本书写
#include <stdio.h>
#include <stdlib.h>

//定义栈的节点
typedef struct Node
{
	int data;
	struct Node *next;
}Node;

//定义栈
typedef struct Stack{
	/*
	 * 一般情况下，Bottom不移动，一直指向栈底，
	 * 而Top一只移动，指向元素的上面一个节点
	 */
	//栈顶
	Node *Top;
	//栈底
	Node *Bottom;
}Stack,*Pstack;

//栈的初始化
void InitStack(Pstack stack){
	stack->Top=NULL;
	stack->Bottom=NULL;
	//这里有点像链表里面的初始化操作
	stack->Top=(Node *) malloc(sizeof(Node));
	if(stack->Top==NULL){
		printf("栈分配内存失败！\n");
		exit(-1);
	}
	//空栈是让他俩相等
	stack->Bottom=stack->Top;
	stack->Top->next=NULL;
}

//节点的初始化
Node *createNode(int data){
	Node *node=(Node *) malloc(sizeof(Node));
	if(node==NULL){
		printf("节点分配内存失败！\n");
		exit(-1);
	}
	node->data=data;
	node->next=NULL;
	return node;
}

//栈的写入操作
void push(Stack *stack,int data){
	//创建一个节点
	Node *newNode= createNode(data);
	//让新节点的指针域指向栈顶，这样就可以让原本最后一个节点与新节点连起来
	//然后再让栈顶指向新节点的地址
	//在栈中，栈底的指针一般保持不懂，只有栈顶的指针在移动
	newNode->next=stack->Top;
	stack->Top=newNode;
	return;
}

//遍历栈
void printStack(Stack *stack){
	Node *p=stack->Top;
	//判断栈是否为空
	if(stack->Bottom==stack->Top){
		printf("栈为空！\n");
		return;
	}
	//这里当p遍历到bottom所指向节点时退出循环
	//即链表的头结点，所以这里与链表遍历时推出的的循环条件还是不一样的
	while(p!=stack->Bottom){
		printf("(%d)",p->data);
		p=p->next;
		if(p!=stack->Bottom){
			printf("->");
		}
	}
	printf("\n");
	return;
}

//判断栈此时是否是空栈
int empty(Stack *stack){
	if(stack->Top==stack->Bottom){
		return 0;
	} else {
		return 1;
	}
}

//删除栈顶元素，并且返回所删除的元素
int pop(Stack *stack,int *data){
	//判断栈是否为空
	if(empty(stack)==0){
		printf("栈为空！\n");
		return 0;
	}
	Node *p=stack->Top;
	*data=p->data;
	stack->Top=p->next;
	free(p);
	return 1;
}

//清空真个栈中的有效数据，保留头结点
void clear(Stack *stack){
	//当链表为空的时候退出循环
	while(empty(stack)!=0){
		//删除栈顶元素，但是不返回
		Node *p=stack->Top;
		stack->Top=p->next;
		free(p);
	}
}

int main(){
	Stack stack;
	int a=0;
	InitStack(&stack);
	push(&stack,1);
	push(&stack,2);
	push(&stack,5);
	push(&stack,4);
	printStack(&stack);
	if(pop(&stack,&a)==1){
		printStack(&stack);
	}
	clear(&stack);
	printStack(&stack);
	return 0;
}

