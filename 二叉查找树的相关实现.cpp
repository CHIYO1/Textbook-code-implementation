#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;

#ifndef _Tree_H

struct TreeNode;
typedef struct TreeNode* Position;
typedef struct TreeNode* SearchTree;

SearchTree MakeEmpty(SearchTree T);//清空查找树，返回空指针
Position Find(ElementType X, SearchTree T);//查找在树中查找元素X的位置
Position FindMin(SearchTree T);//查找树中最小元素的位置
Position FindMax(SearchTree T);//查找树中最大元素的位置
SearchTree Insert(ElementType X, SearchTree T);//在树中插入元素X，树中有相同节点时什么都不做,当树中没有节点时返回含一个节点的树
SearchTree Delete(ElementType X, SearchTree T);//在树中删除元素X
//如果目标节点没有或者只有一个子节点，则删除节点后将目标节点的非空节点或（如果是叶子节点）空节点返回给父节点
//如果目标有两个子节点，则将右子树中最小元素替代目标节点位置的元素，并对右子树进行递归删除最小元素（此时最小元素必然只有一个或没有子节点，按上述处理）
ElementType Retrieve(Position P);//返回树节点位置的对应元素
void PrintTree(SearchTree T);//按中序遍历的顺序打印查找树（从小到大输出元素）
void Error(void);//删除操作报错用函数

#endif

struct TreeNode {
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};
//测试用主函数
int main(void) {
	int A[10] = { 34,144,14,84,26,85,37,27,3,4};
	SearchTree T = NULL;
	Position P;
	for (int i = 0; i < 10; i++) {
		T = Insert(A[i], T);
	}
	printf("%d\n", Retrieve(FindMin(T)));
	printf("%d\n", Retrieve(FindMax(T)));
	P = Find(144, T);
	printf("%d\n", P->Element);
	for (int j = 0; j < 10; j++) {
		PrintTree(T);
		printf("\n");
		T = Delete(A[j], T);
	}
	if (!T) {
		printf("NULL\n");
	}
	for (int i = 0; i < 10; i++) {
		T = Insert(A[i], T);
	}
	T = MakeEmpty(T);
	if (!T) {
		printf("NULL\n");
	}
	T = Delete(4, T);
	return 0;
}

SearchTree MakeEmpty(SearchTree T) {
	if (T != NULL) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType X, SearchTree T) {
	if (T == NULL) {
		return NULL;
	}
	if (T->Element < X) {
		return Find(X, T->Right);
	}
	else if (T->Element > X) {
		return Find(X, T->Left);
	}
	else {
		return T;
	}
}

//递归实现
Position FindMin(SearchTree T) {
	if (T == NULL) {
		return T;
	}
	else if (T->Left ) {
		FindMin(T->Left);
	}
	else{
		return T;
	}
}
//非递归实现
Position FindMax(SearchTree T) {
	if (T != NULL) {
		while (T->Right) {
			T = T->Right;
		}
	}
	return T;
}

SearchTree Insert(ElementType X, SearchTree T) {
	if (T == NULL) {
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		T->Element = X;
		T->Left = T->Right = NULL;
	}
	else {
		if (T->Element > X) {
			T->Left = Insert(X, T->Left);
		}
		else if (T->Element < X) {
			T->Right = Insert(X, T->Right);
		}
	}
	return T;
}

SearchTree Delete(ElementType X, SearchTree T) {
	Position TmpCell;
	if (!T) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	else {
		if (T->Element > X) {
			T->Left = Delete(X, T->Left);//采用递归保留父节点位置（将删除后的子树返回）
		}
		else if (T->Element < X) {
			T->Right = Delete(X, T->Right);
		}
		else {     //找到目标元素
			if (T->Left && T->Right) {    //当目标节点有两个子树时
				TmpCell = FindMin(T->Right);
				T->Element = TmpCell->Element;
				T->Right = Delete(TmpCell->Element, T->Right);
			}
			else {    //当目标节点只有一个或没有子树时
				TmpCell = T;
				if (T->Left) {
					T = T->Left;
				}
				else {
					T = T->Right;
				}
				free(TmpCell);
			}
		}
	}
	return T;
}

ElementType Retrieve(Position P) {
	return P->Element;
}

void PrintTree(SearchTree T) {
	if (T->Left) {
		PrintTree(T->Left);
	}
	printf("%d ", T->Element);
	if (T->Right) {
		PrintTree(T->Right);
	}
}

void Error(void) {
	printf("Element not found!!!\n");
}

