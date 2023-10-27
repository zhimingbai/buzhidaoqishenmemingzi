//平衡二叉树基本操作
//以及前序遍历、中序遍历、后序遍历
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点的结构体
struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
};

// 创建一个新的二叉树节点
struct TreeNode *createNode(int data) {
	struct TreeNode *newNode = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// 插入一个新的二叉树节点到二叉树中
struct TreeNode *insertNode(struct TreeNode *root, int data) {
	// 如果当前节点为空（子树为空），创建一个新节点并返回
	if (root == NULL) {
		return createNode(data);
	} else {
		// 否则，根据插入节点的值与当前节点的值比较
		if (data < root->data) {
			// 如果插入节点的值小于当前节点的值，将节点插入到当前节点的左子树中
			root->left = insertNode(root->left, data);
		} else {
			// 如果插入节点的值大于等于当前节点的值，将节点插入到当前节点的右子树中
			root->right = insertNode(root->right, data);
		}
	}
	// 返回更新后的树的根节点
	return root;
}

// 查找二叉树中的一个节点
// 参数:
// - root: 二叉树的根节点
// - data: 要查找的数据值
// 返回值:
// - 如果找到了包含数据值的节点，返回该节点的指针
// - 如果未找到，返回 NULL
struct TreeNode *searchNode(struct TreeNode *root, int data) {
	// 如果当前节点为NULL，表示二叉树为空或已经搜索到了叶子节点，未找到匹配的数据值
	if (root == NULL) {
		return NULL;
	}
	
	// 如果当前节点的数据值与要查找的数据值相等，表示找到了匹配的节点，返回该节点的指针
	if (root->data == data) {
		return root;
	}
	
	// 如果要查找的数据值小于当前节点的数据值，向左子树递归查找
	// 注意：在二叉搜索树中，左子树的所有节点的值都小于当前节点的值
	if (data < root->data) {
		return searchNode(root->left, data);
	}
	// 如果要查找的数据值大于当前节点的数据值，向右子树递归查找
	// 注意：在二叉搜索树中，右子树的所有节点的值都大于当前节点的值
	else {
		return searchNode(root->right, data);
	}
}

// 查找二叉树中的最小节点
struct TreeNode *findMin(struct TreeNode *root) {
	// 如果传入的根节点为空，说明树为空，直接返回 NULL
	if (root == NULL) {
		return NULL;
	}
	// 从传入的根节点开始，一直沿着左子树往下遍历，直到找到没有左子树的节点
	// 这个过程保证了在二叉搜索树中，最小的节点一定是在最左侧的分支上
	while (root->left != NULL) {
		root = root->left;
	}
	// 返回最小节点，它是找到的最左侧的叶子节点
	return root;
}


// 删除二叉树中的一个节点
struct TreeNode *deleteNode(struct TreeNode *root, int data) {
	if (root == NULL) {
		// 如果根节点为空，返回根节点为空，表示没有找到要删除的数据
		return root;
	} else if (data < root->data) {
		// 如果要删除的数据比当前节点的数据小，递归地在左子树中查找并删除
		root->left = deleteNode(root->left, data);
	} else if (data > root->data) {
		// 如果要删除的数据比当前节点的数据大，递归地在右子树中查找并删除
		root->right = deleteNode(root->right, data);
	} else if(root->data==data){
		// 找到了要删除的节点
		
		if (root->left == NULL && root->right == NULL) {
			// 情况1：要删除的节点没有子节点（叶子节点）
			free(root); // 释放内存
			root = NULL; // 将当前节点设为NULL，表示已删除
		} else if (root->left == NULL) {
			// 情况2：要删除的节点只有右子树
			struct TreeNode *temp = root; // 保存当前节点的指针
			root = root->right; // 将当前节点替换为右子树
			free(temp); // 释放原节点的内存
		} else if (root->right == NULL) {
			// 情况3：要删除的节点只有左子树
			struct TreeNode *temp = root; // 保存当前节点的指针
			root = root->left; // 将当前节点替换为左子树
			free(temp); // 释放原节点的内存
		} else {
			// 情况4：要删除的节点既有左子树又有右子树
			// 找到右子树中的最小值节点，将其值复制到当前节点，然后删除右子树中的最小值节点
			/*
			 * 简单解释一下为什么要这样做，因为这里的这个是一个平衡二叉树，什么意思呢？
			 * 就是说我的左子节点一定比我的右节点要小，此时我找到右子树当中最小的节点就一定比左子树所有节点都大
			 * 同时也会比根节点大，为什么？因为比根节点小的都存到左子树里面了
			 * 那么此时我要删除根节点就要找到右子树里面最小的节点放到根节点的位置
			 */
			struct TreeNode *temp = findMin(root->right); // 找到右子树中的最小值节点
			root->data = temp->data; // 将当前节点的值替换为最小值节点的值
			root->right = deleteNode(root->right, temp->data); // 递归地删除右子树中的最小值节点
		}
	}
	return root;
}


/*
 * 众所周知，每一次递归，系统都会使用一个叫函数调用栈的数据结构来跟踪每次函数调用的信息
 * 每个函数调用都会在栈中创建一个帧（frame），该帧包含了该函数的局部变量、参数值等信息。
 * 当函数调用结束时，它的帧会被弹出栈，控制权会返回到调用该函数的地方。
 * 这就能够很容易解释为什么在遍历到NULL的时候还能够返回上一级
 * 如果还有不明白的地方，详细请看我写的笔记有关递归方面的笔记
 */
/**
 * 前序遍历二叉树并打印节点数据
 *
 * @param root 二叉树的根节点
 *
 * 该函数用于前序遍历二叉树，从根节点开始，首先访问根节点，然后递归地访问左子树，最后递归地访问右子树。
 * 在遍历的过程中，它会打印每个节点的数据值。
 */
void printPreOrder(struct TreeNode *root) {
	// 如果根节点为空，表示空树或者递归到了叶子节点的空子树，返回并结束递归。
	if (root == NULL) {
		return;
	}
	
	// 打印当前节点的数据值，表示前序遍历的访问顺序。
	printf("%d ", root->data);
	
	// 递归遍历左子树，继续前序遍历左子树的节点。
	printPreOrder(root->left);
	
	// 递归遍历右子树，继续前序遍历右子树的节点。
	printPreOrder(root->right);
}

/**
 * 中序遍历二叉树并打印节点数据
 *
 * @param root 二叉树的根节点
 *
 * 该函数用于中序遍历二叉树，从根节点开始，先递归地遍历左子树，然后访问根节点，最后递归地遍历右子树。
 * 在遍历的过程中，它会打印每个节点的数据值。
 * 当然我们遍历之后发现只有中序遍历是从小到大遍历的
 */
void printInOrder(struct TreeNode *root) {
	// 如果根节点为空，表示空树或者递归到了叶子节点的空子树，返回并结束递归。
	if (root == NULL) {
		return;
	}
	
	// 递归遍历左子树，继续中序遍历左子树的节点。
	printInOrder(root->left);
	
	// 打印当前节点的数据值，表示中序遍历的访问顺序。
	printf("%d ", root->data);
	
	// 递归遍历右子树，继续中序遍历右子树的节点。
	printInOrder(root->right);
}

/**
 * 后序遍历二叉树并打印节点数据
 *
 * @param root 二叉树的根节点
 *
 * 该函数用于后序遍历二叉树，从根节点开始，先递归地遍历左子树，然后递归地遍历右子树，最后访问根节点。
 * 在遍历的过程中，它会打印每个节点的数据值。
 */
void printPostOrder(struct TreeNode *root) {
	// 如果根节点为空，表示空树或者递归到了叶子节点的空子树，返回并结束递归。
	if (root == NULL) {
		return;
	}
	
	// 递归遍历左子树，继续后序遍历左子树的节点。
	printPostOrder(root->left);
	
	// 递归遍历右子树，继续后序遍历右子树的节点。
	printPostOrder(root->right);
	
	// 打印当前节点的数据值，表示后序遍历的访问顺序。
	printf("%d ", root->data);
}

int main() {
	struct TreeNode *root = NULL;
	root = insertNode(root, 10);
	root = insertNode(root, 5);
	root = insertNode(root, 15);
	root = insertNode(root, 3);
	root = insertNode(root, 7);
	root = insertNode(root, 12);
	root = insertNode(root, 17);
	root = insertNode(root, 11);
	root = insertNode(root, 13);
	root = insertNode(root, 16);
	root = insertNode(root, 20);
	printf("二叉树的前序遍历： ");
	printPreOrder(root);
	printf("\n");
	printf("二叉树的中序遍历： ");
	printInOrder(root);
	printf("\n");
	printf("二叉树的后序遍历： ");
	printPostOrder(root);
	printf("\n");
	struct TreeNode *node = searchNode(root, 12);
	if (node != NULL) {
		printf("找到了包含数据的节点 %d\n", node->data);
	} else {
		printf("未找到节点\n");
	}
	root = deleteNode(root, 15);
	printf("删除 15 后二叉树的前序遍历： ");
	printPreOrder(root);
	printf("\n");
	printf("删除 15 后二叉树的中序遍历： ");
	printInOrder(root);
	printf("\n");
	printf("删除 15 后二叉树的后序遍历： ");
	printPostOrder(root);
	printf("\n");
	return 0;
}
