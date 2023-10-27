#include <stdio.h>
#include <stdlib.h>

//结构体的初始化
typedef struct {
	int *base;
	int *top;
	int stacksize;
	int length;
} SqStack;

//栈的初始化
int initStack(SqStack *sqStack) {
	sqStack->stacksize = 10;
	//进行动态内存的赋值
	sqStack->base = (int *) malloc(sqStack->stacksize * sizeof(int));
	if (sqStack->base==NULL) {
		//如果初始化失败
		printf("初始化栈失败，请检查内存\n");
		return 0;
	}
	//剩余数据的初始化
	sqStack->top = sqStack->base;
	sqStack->length = 0;
	return 1;
}

//判断栈是否是空的，如果不是则返回栈顶的元素
int getTop(SqStack *sqStack, int *elem) {
	if (sqStack->base == sqStack->top) {
		//如果相等则表示栈是空的
		printf("此时的栈是空的\n");
		return 0;
	}
	//理论上来说这句等同于
	//*elem=*(sqStack->top-1);
	*elem = sqStack->base[sqStack->length - 1];
	return 1;
}

//在栈中插入元素
/*
  在顺序栈中插入元素的时候，同样要遵循顺序插入的原则，不能随机插入
 */
int insertSq(SqStack *sqStack, int elem) {
	//插入elem成为新的栈顶元素
	//判断栈是否已经写满了
	if (sqStack->length >= sqStack->stacksize) {
		//如果栈满了，进行自动扩容，通过动态内存的方式
		int newStacksize = sqStack->stacksize * 2;
		int *newBase;
		newBase = (int *) realloc(sqStack->base, newStacksize * sizeof(sqStack->base));
		if (!newBase) {
			//如果自动扩容失败
			printf("自动扩容失败，请检查内存");
			return 0;
		}
		//更新栈的数据
		sqStack->base = newBase;
		//更新栈顶的指针内存储的地址，防止栈顶元素丢了
		sqStack->top = sqStack->base + sqStack->stacksize;
		sqStack->stacksize = newStacksize;
	}
	/*
	  开始执行插入操作，两种方法，一种通过指针一种通过数组
	  按照我的习惯，我个人较倾向于通过数组，因为这样不容易出错
	  指针操作为
	  
	 */
	sqStack->length++;
	sqStack->base[sqStack->length - 1] = elem;
	sqStack->top++;
	return 1;
}

//若栈不为空，删除栈顶元素并且返回
int pop(SqStack *sqStack, int *elem) {
	if (sqStack->base == sqStack->top) {
		//此时栈为空
		printf("此时栈为空，不能进行删除操作");
		return 0;
	}
	*elem = sqStack->base[sqStack->length - 1];
	sqStack->base[sqStack->length - 1] = 0;
	sqStack->top--;
	sqStack->length--;
	return 1;
}

//遍历
void print(SqStack *sqStack) {
	for (int i = sqStack->length-1; i>=0; i--) {
		printf("(%d)", sqStack->base[i]);
	}
	printf("\n");
}

int main() {
	SqStack sqStack;
	int elem;
	initStack(&sqStack);
	for (int i = 1; i <= 50; i++) {
		insertSq(&sqStack, i);
	}
	print(&sqStack);
	
	pop(&sqStack, &elem);
	printf("%d\n",elem);
	
	getTop(&sqStack,&elem);
	printf("%d\n",elem);
	return 0;
}
