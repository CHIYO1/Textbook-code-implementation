#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;

#ifndef _AvlTree_H
struct AvlNode;
typedef struct AvlNode* Position;
typedef struct AvlNode* AvlTree;

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
ElementType Retrieve(Position P);

static int Height(Position P);
int Max(int a, int b);
static Position SingleRotateWithLeft(Position K2);
static Position SingleRotateWithRight(Position K2);
static Position DoubleRotateWithLeft(Position K3);
static Position DoubleRotateWithRight(Position K3);
void Error(void);
void PrintTree(AvlTree T,int n);

#endif /* _AvlTree_H */

struct AvlNode {
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

//测试用主函数
int main(void) {
	int a[10] = { 1,2,3,4,5,6,7,8,9,10};
	AvlTree T=NULL;
	for (int i = 0; i < 10; i++) {
		T = Insert(a[i], T);
	}
	PrintTree(T,0);

	printf("__________________________________________\n");
	for (int i = 1; i < 11; i++) {
		T = Delete(i, T);
		PrintTree(T, 0);
		printf("__________________________________________\n");
	}
	return 0;
}

void Error(void) {
	printf("出错了!!!!/n");
}

AvlTree MakeEmpty(AvlTree T) {
	if (T != NULL) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType X, AvlTree T) {
	if (!T) {
		return NULL;
	}
	if (X < T->Element) {
		Find(X, T->Left);
	}
	else if (X > T->Element) {
		Find(X, T->Right);
	}
	else {
		return T;
	}
}

Position FindMin(AvlTree T) {
	if (!T) {
		return NULL;
	}
	if (!T->Left) {
		FindMin(T->Left);
	}
	else {
		return T;
	}
}

Position FindMax(AvlTree T) {
	if (T) {
		while (T->Right) {
			T = T->Right;
		}
	}
	return T;
}

AvlTree Insert(ElementType X, AvlTree T) {
	if (T == NULL) {
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		T->Element = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else if (X < T->Element) {
		T->Left=Insert(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (X < T->Left->Element) {
				T = SingleRotateWithLeft(T);
			}
			else {
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if (X > T->Element) {
		T->Right=Insert(X, T->Right);
		if (Height(T->Right)-Height(T->Left)==2) {
			if (X > T->Right->Element) {
				T = SingleRotateWithRight(T);
			}
			else{
				T = DoubleRotateWithRight(T);
			}
		}
	}
	else {
		return T;
	}
	T->Height = Max(Height(T->Left), Height(T->Right))+1;
	return T;
}

AvlTree Delete(ElementType X, AvlTree T) {
	if (T == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	if (X < T->Element) {
		T->Left = Delete(X, T->Left);
		if (Height(T->Right) - Height(T->Left) == 2) {
			if (Height(T->Right->Right) > Height(T->Right->Left)) {
				T = SingleRotateWithRight(T);
			}
			else {
				T = DoubleRotateWithRight(T);
			}
		}
	}
	else if (X > T->Element) {
		T->Right = Delete(X,T->Right);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (Height(T->Left->Left) > Height(T->Left->Right)) {
				T = SingleRotateWithLeft(T);
			}
			else {
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else {
		if (!T->Left || !T->Right) {
			Position p = T;
			if (T->Left == NULL) {
				T = T->Right;
			}
			else {
				T = T->Left;
			}
			free(p);
		}
		else {
			T->Element = FindMin(T->Right)->Element;
			T->Right = Delete(T->Element, T->Right);
		}
	}
	if (T) {
		T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	}
	return T;
}

ElementType Retrieve(Position P) {
	return P->Element;
}

static int Height(Position P) {
	if (!P) {
		return -1;
	}
	else {
		return P->Height;
	}
}

int Max(int a, int b) {
	return (a > b) ? a : b;
}

static Position SingleRotateWithLeft(Position K2) {
	Position K1;
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
	return K1;
}

static Position SingleRotateWithRight(Position K2) {
	Position K1;
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
	return K1;
}

static Position DoubleRotateWithLeft(Position K3) {
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

static Position DoubleRotateWithRight(Position K3) {
	K3->Right = SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);
}

void PrintTree(AvlTree T,int n) {
	if (!T) {
		printf("NULL\n");
	}
	else {
		if (T->Left) {
			PrintTree(T->Left, n + 1);
		}
		for (int k = 0; k < n; k++) {
			printf("    ");
		}
		printf("%d\n", T->Element);
		if (T->Right) {
			PrintTree(T->Right, n + 1);
		}
	}
}
