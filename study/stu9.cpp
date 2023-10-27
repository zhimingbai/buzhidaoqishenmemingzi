//数组队列
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 5

typedef struct Queue {
	int *queueArray; // 存储队列元素的指针
	int front;       // 队列头部指针
	int rear;        // 队列尾部指针
	int size;        // 当前队列大小
	int capacity;    // 队列的容量
} Queue;

// 函数：初始化队列
void initializeQueue(Queue *q) {
	q->queueArray = (int *) malloc(INITIAL_SIZE * sizeof(int)); // 初始分配内存
	if (q->queueArray == NULL) {
		printf("内存分配失败，无法初始化队列。\n");
		exit(1);
	}
	q->front = -1;
	q->rear = -1;
	q->size = 0;
	q->capacity = INITIAL_SIZE;
}

// 函数：检查队列是否为空
bool isQueueEmpty(Queue *q) {
	if (q->front == -1) {
		return true;
	} else {
		return false;
	}
}

// 函数：入队操作
void enqueue(Queue *q, int item) {
	if (q->size == q->capacity) {
		// 队列已满，需要扩容
		int newCapacity = 2 * q->capacity;
		int *newQueue = (int *) realloc(q->queueArray, newCapacity * sizeof(int));
		if (newQueue == NULL) {
			printf("内存分配失败，无法扩容队列。\n");
			exit(1);
		}
		q->queueArray = newQueue;
		q->capacity = newCapacity;
	}
	
	if (isQueueEmpty(q)) {
		q->front = q->rear = 0;
	} else {
		q->rear++;
	}
	
	q->queueArray[q->rear] = item;
	q->size++;
	printf("入队：%d\n", item);
}

// 函数：出队操作
bool dequeue(Queue *q, int *item) {
	if (isQueueEmpty(q)) {
		printf("队列为空，无法出队。\n");
		return false;
	} else if (q->front == q->rear) {
		//即队列中只有一个元素的情况。
		//这是由于队列在出队时需要维护头部和尾部指针，
		//以确保它们正确地指向队列的前部和后部。
		/*
		  在这里，如果只有一个元素，那么q->front 和 q->rear都赋值成-1
		  此时，如果在进行入队操作，并不会进行自动扩容
		  而是直接覆写原本存在arr[0]里面的元素。
		  这样就不会造成数组的内存泄露。
		 */
		*item = q->queueArray[q->front];
		q->front = q->rear = -1;
	} else {
		*item = q->queueArray[q->front];
		q->front++;
	}
	q->size--;
	return true;
}

// 函数：查看队首元素
bool peek(Queue *q ,int *item) {
	if (isQueueEmpty(q)) {
		printf("队列为空，无法查看队首元素。\n");
		return false;
	}else {
		*item = q->queueArray[q->front];
		return true;
	}
}

// 函数：释放队列内存
void freeQueue(Queue *q) {
	free(q->queueArray);
}

int main() {
	// 初始化队列
	Queue myQueue;
	int item = 0;
	initializeQueue(&myQueue);
	
	// 测试入队操作
	enqueue(&myQueue, 10);
	enqueue(&myQueue, 20);
	enqueue(&myQueue, 30);
	enqueue(&myQueue, 40);
	enqueue(&myQueue, 50);
	
	// 查看队首元素
	if (peek(&myQueue, &item)) {
		printf("队首元素：%d\n", item);
	}
	
	// 测试出队操作
	if (dequeue(&myQueue, &item)) {
		printf("出队：%d\n", item);
	}
	if (dequeue(&myQueue, &item)) {
		printf("出队：%d\n", item);
	}
	if (dequeue(&myQueue, &item)) {
		printf("出队：%d\n", item);
	}
	if (dequeue(&myQueue, &item)) {
		printf("出队：%d\n", item);
	}
	if (dequeue(&myQueue, &item)) {
		printf("出队：%d\n", item);
	}
	// 查看队首元素
	if (peek(&myQueue, &item)) {
		printf("队首元素：%d\n", item);
	}
	enqueue(&myQueue, 10);
	enqueue(&myQueue, 20);
	enqueue(&myQueue, 30);
	enqueue(&myQueue, 40);
	if (peek(&myQueue, &item)) {
		printf("队首元素：%d\n", item);
	}
	// 释放队列内存
	freeQueue(&myQueue);
	return 0;
}

