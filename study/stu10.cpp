//数组循环队列
#include <stdio.h>
#include <stdlib.h>
//设置最大值
#define MAX_SIZE 5
//创建结构体
typedef struct {
	int data[MAX_SIZE];
	int front;
	int rear;
} Queue;

//初始化队列
Queue *initQueue() {
	Queue *queue = (Queue *) malloc(sizeof(Queue));
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

//判断队列是否为满
//如果为满，则返回1，不满返回0
int isFull(Queue *queue) {
	if ((queue->rear + 1) % MAX_SIZE == queue->front) {
		return 1;
	} else {
		return 0;
	}
}

//判断队列是否为空
int isEmpty(Queue *queue) {
	if (queue->front == queue->rear) {
		//为空则返回1
		return 1;
	} else {
		//不为空则返回0
		return 0;
	}
}

//入队操作
int enQueue(Queue *queue, int data) {
	if (isFull(queue) == 1) {
		//若当前队列已满，则不进行入队操作
		return 0;
	} else {
		//执行入队操作
		queue->data[queue->rear] = data;
		queue->rear = (queue->rear + 1) % MAX_SIZE;
		return 1;
	}
}

//出队操作
int deQueue(Queue *queue) {
	if (isEmpty(queue) == 1) {
		//若当前队列为空，则不进行出队操作
		return -1;
	} else {
		//执行出队操作
		int data = queue->data[queue->front];
		queue->front = (queue->front + 1) % MAX_SIZE;
		return data;
	}
}

//遍历队列的操作
void printQueue(Queue *queue) {
	//要知道当前队列一共有多少个元素
	int length=(queue->rear-queue->front+MAX_SIZE)%MAX_SIZE;
	int index=queue->front;
	for (int i = 0; i < length; ++i) {
		printf("%d->",queue->data[index]);
		index=(index+1)%MAX_SIZE;
	}
	printf("NULL\n");
}

int main(){
	Queue *queue=initQueue();
	//int data;
	enQueue(queue,1);
	enQueue(queue,4);
	enQueue(queue,5);
	enQueue(queue,2);
	enQueue(queue,3);
	printQueue(queue);
	printf("%d\n",deQueue(queue));
	printf("%d\n",deQueue(queue));
	printf("%d\n",deQueue(queue));
	printf("%d\n",deQueue(queue));
	printQueue(queue);
	enQueue(queue,3);
	enQueue(queue,11);
	enQueue(queue,12);
	printQueue(queue);
	printf("%d\n",deQueue(queue));
	printf("%d\n",deQueue(queue));
	printf("%d\n",deQueue(queue));
	printQueue(queue);
	return 0;
}
