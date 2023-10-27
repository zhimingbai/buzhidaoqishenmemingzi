// 顺序表
#include <stdio.h>
#include <stdlib.h>
// 声明节点
typedef struct List {
	// 数据
	int *data;
	// 已经存在的个数
	int quantity;
	// 一共能存的个数
	int number;
} arrayList;

// 初始化节点
int initList(arrayList *list) {
	list->number = 10;
	list->data = (int*)malloc(list->number * sizeof(int));
	if (list->data == NULL) {
		list->number = 0;
		return 0;
	}
	list->data[0] = 0;
	list->quantity = 0;
	return 1;
}
// insertList函数用于向顺序表中插入元素。
// 传入的参数包括顺序表指针list、要插入的数据data和插入的位置index。
void insertList(arrayList *list, int data, int index) {
	// 判断是否符合插入标准
	if ( index < 1 || index > list->quantity + 1) {
		printf("该插入是非法的\n");
		return;
	}
	// 判断是否需要进行扩容
	if (list->quantity >= list->number) {
		int newNumber = list->number * 2;
		int *newData = (int*)realloc(list->data, newNumber * sizeof(int));
		// 判断扩容是否失败
		if (newData == NULL) {
			
			printf("自动扩容失败\n");
			return;
		}
		// 写入新的数据
		list->data = newData;
		list->number = newNumber;
	}
	// 遍历，整体向后移一位
	for (int i = list->quantity - 1; i >= index - 1; i--) {
		list->data[i + 1] = list->data[i];
	}
	// 插入
	list->data[index - 1] = data;
	list->quantity++;
}

// 删除索引对应的元素
void deleteList(arrayList *list, int index) {
	// 判断索引是否越界
	if (index < 1 || index > list->quantity) {
		printf("不存在该索引，无法删除\n");
		return;
	}
	// 进行删除，从前往后遍历
	for (int i = index - 1; i <= list->quantity - 1; i++) {
		list->data[i] = list->data[i + 1];
	}
	list->quantity--;
}

// 获取元素
int getList(arrayList *list, int index) {
	// 判断索引是否越界
	if (index <= 0 || index > list->quantity) {
		printf("不存在该索引，无法获取该索引对应的数据\n");
		return 0;
	}
	// 寻找数据
	int data_1 = list->data[index - 1];
	return data_1;
}

// 查找元素的位置
int findList(arrayList *list, int data) {
	for (int i = 0; i <= list->quantity - 1; i++) {
		if (list->data[i] == data) {
			return i + 1;
		}
	}
	return 0;
}

// printList函数用于打印顺序表中的所有元素。
void printList(arrayList *list) {
	for (int i = 0; i <= list->quantity - 1; i++) {
		printf("%d ", list->data[i]);
	}
	printf("\n");
}


int main() {
	struct List list;
	if (initList(&list) == 1) {
		for(int i=0;i<40;i++){
			insertList(&list,(i+1)*10,i+1);
		}
		printList(&list);
		printf("%d\n",list.quantity);
		deleteList(&list,18);
		deleteList(&list,19);
		deleteList(&list,23);
		deleteList(&list,34);
		deleteList(&list,6);
		deleteList(&list,36);
		int data_1=getList(&list,18);
		if(data_1==0){
			printf("不存在\n");
		}else{
			printf("%d\n",data_1);
		}
		data_1=getList(&list,19);
		if(data_1==0){
			printf("不存在\n");
		}else{
			printf("%d\n",data_1);
		}
		int data_2=findList(&list,10);
		if(data_2==0){
			printf("不存在\n");
		}else{
			printf("%d\n",data_2);
		}
		data_2= findList(&list,90);
		if(data_2==0){
			printf("不存在\n");
		}else{
			printf("%d\n",data_2);
		}
		printList(&list);
		printf("%d\n",list.quantity);
	} else {
		printf("内存不足，初始化链表失败\n");
	}
	return 0;
}
