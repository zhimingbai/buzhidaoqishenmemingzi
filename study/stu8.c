//链式队列
#include <stdio.h>
#include <stdlib.h>


//节点
typedef struct Node {
	int data;
	struct Node *next;
} Node;

//队列
typedef struct queue {
	//对头
	Node *front;
	//对尾
	Node *rear;
} Queue;

//初始化队列
Queue *initQueue() {
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

// 入队操作
void enqueue(Queue *queue, int data) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	
	if (queue->rear == NULL) {
		//这里判断是不是空对，然后第一次入队元素
		queue->front = queue->rear = newNode;
	} else {
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

//出队操作
int dequeue(Queue *queue) {
	if (queue->front == NULL) {
		printf("队列为空，出队失败\n");
		return 0;
	}
	int data = queue->front->data;
	Node *temp = queue->front;
	if (queue->front == queue->rear) {
		//这里判断此时对中是不是就这一个元素
		queue->front = queue->rear = NULL;
	} else {
		queue->front = queue->front->next;
	}
	//释放节点
	free(temp);
	return data;
}

//判断是否为空
int isEmpty(Queue *queue) {
	if (queue->front == NULL) {
		return 1;
	} else {
		return 0;
	}
}

// 查看队列的大小
int size(Queue *queue) {
	int count = 0;
	Node *current = queue->front;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

//遍历队列数据
void print(Queue *queue){
	Node *pNode=queue->front;
	while(pNode!=NULL){
		printf("(%d)",pNode->data);
		pNode=pNode->next;
	}
	printf("\n");
}

int main() {
	//初始化一个对
	Queue *queue = initQueue();
	
	// 入队操作
	enqueue(queue, 1);
	enqueue(queue, 2);
	enqueue(queue, 3);
	printf("当前队列内部的数据为:");	
	//遍历队
	print(queue);
	
	printf("队列的大小: %d\n", size(queue));
	printf("判断队列是否为空: %d\n", isEmpty(queue));
	printf("出队操作: %d\n", dequeue(queue));
	
	printf("队列的大小: %d\n", size(queue));
	printf("出队操作: %d\n", dequeue(queue));
	
	printf("队列的大小: %d\n", size(queue));
	printf("出队操作: %d\n", dequeue(queue));
	
	printf("队列的大小: %d\n", size(queue));
	
	printf("判断队列是否为空: %d\n", isEmpty(queue));	
	

	free(queue);
	
	return 0;
}
