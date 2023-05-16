#include<stdio.h>
#include<stdlib.h>

#ifndef _SplayTree_H
struct Node;
typedef int ElementType;
typedef struct Node* SplayTree;
typedef struct Node* Position;

SplayTree MakeEmpty(SplayTree T);
SplayTree Insert(ElementType X, SplayTree T);
SplayTree Delete(ElementType X, SplayTree T);
Position Find(ElementType X, SplayTree T);
Position FindMin(SplayTree T);

void Error(void);
void PrintTree(SplayTree T,int n);
SplayTree SingleRotateWithLeft(Position P);
SplayTree SingleRotateWithRight(Position P);
SplayTree DoubleRotateWithLeft(Position P);
SplayTree DoubleRotateWithRight(Position P);
SplayTree Rotate(Position P);
#endif

struct Node {
	ElementType Data;
	Position Father;
	SplayTree Left;
	SplayTree Right;
};

//测试用函数
int main(void) {
	int A[32] = { 32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
	//int A[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	SplayTree T=NULL;
	for (int i = 0; i < 32; i++) {
		T = Insert(A[i], T);
	}
	PrintTree(T,0);
	printf("______________________________\n");
	//T = Delete(3, T);
	//PrintTree(T, 0);
	for (int j = 1; j < 10; j++) {
		T = Find(j, T);
		PrintTree(T, 0);
		printf("______________________________\n");
	}
	T=Find(9, T);
	PrintTree(T, 0);
	return 0;
}

void Error(void) {
	printf("出错了!!!\n");
}

SplayTree MakeEmpty(SplayTree T) {
	if (T) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

SplayTree Insert(ElementType X, SplayTree T) {
	if (T == NULL) {
		T = (SplayTree)malloc(sizeof(struct Node));
		if (!T) {
			atexit(Error);
			exit(EXIT_FAILURE);
		}
		T->Data = X;
		T->Father = NULL;
		T->Left = T->Right = NULL;
	}
	else {
		if (X < T->Data) {
			T->Left = Insert(X, T->Left);
			T->Left->Father = T;
		}
		else if (X > T->Data) {
			T->Right = Insert(X, T->Right);
			T->Right->Father = T;
		}
	}
	return T;
}

SplayTree Delete(ElementType X, SplayTree T) {
	if (T == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	else {
		if (X < T->Data) {
			T->Left=Delete(X, T->Left);
			T->Left->Father = T;
		}
		else if (X > T->Data) {
			T->Right=Delete(X, T->Right);
			T->Right->Father = T;
		}
		else {
			Position P;
			if (T->Left && T->Right) {
				T->Data = FindMin(T->Right)->Data;
				Delete(T->Data, T->Right);
			}
			else {
				if (T->Left) {
					P = T;
					T = T->Left;
					free(P);
				}
				else {
					P = T;
					T = T->Right;
					free(P);
				}
			}
		}
	}
	return T;
}

Position Find(ElementType X, SplayTree T) {
	if (T) {
		if (X < T->Data) {
			return Find(X, T->Left);
		}
		else if (X > T->Data) {
			return Find(X, T->Right);
		}
		else if (X == T->Data) {
			while (T->Father) {
				T = Rotate(T);
			}
			return T;
		}
	}
	else {
		return NULL;
	}
}

void PrintTree(SplayTree T,int n) {
	if (T == NULL) {
		printf("NULL\n");
	}
	else {
		if (T->Left) {
			PrintTree(T->Left, n + 1);
		}
		for (int i = 0; i < n; i++) {
			printf("   ");
		}
		printf("%d\n", T->Data);
		if (T->Right) {
			PrintTree(T->Right, n + 1);
		}
	}
}

Position FindMin(SplayTree T) {
	if (!T) {
		return NULL;
	}
	else {
		if (T->Left) {
			return FindMin(T->Left);
		}
		else {
			return T;
		}
	}
}

SplayTree SingleRotateWithLeft(Position P) {
	Position p;
	p = P->Father->Father;
	P->Father->Right = P->Left;
	if (P->Left) {
		P->Left->Father = P->Father;
	}
	P->Father->Father = P;
	P->Left = P->Father;
	P->Father = p;
	if (P->Father) {
		if (P->Data < P->Father->Data) {
			P->Father->Left = P;
		}
		else {
			P->Father->Right = P;
		}
	}
	return P;
}

SplayTree SingleRotateWithRight(Position P) {
	Position p;
	p = P->Father->Father;
	P->Father->Left = P->Right;
	if (P->Right) {
		P->Right->Father = P->Father;
	}
	P->Father->Father = P;
	P->Right = P->Father;
	P->Father = p;
	if (P->Father) {
		if (P->Data < P->Father->Data) {
			P->Father->Left = P;
		}
		else {
			P->Father->Right = P;
		}
	}
	return P;
}

SplayTree DoubleRotateWithLeft(Position P) {
	P = SingleRotateWithRight(P);
	return SingleRotateWithLeft(P);
}

SplayTree DoubleRotateWithRight(Position P) {
	P = SingleRotateWithLeft(P);
	return SingleRotateWithRight(P);
}

SplayTree Rotate(Position P) {
	if (P->Father->Father==NULL) {
		if (P->Data < P->Father->Data) {
			P = SingleRotateWithRight(P);
		}
		else {
			P = SingleRotateWithLeft(P);
		}
	}
	else {
		if (P->Data < P->Father->Father->Data) {
			if (P->Data < P->Father->Data) {
				P->Father = SingleRotateWithRight(P->Father);
				P = SingleRotateWithRight(P);
			}
			else {
				P = DoubleRotateWithRight(P);
			}
		}
		else {
			if (P->Data < P->Father->Data) {
				P = DoubleRotateWithLeft(P);
			}
			else {
				P->Father = SingleRotateWithLeft(P->Father);
				P = SingleRotateWithLeft(P);
			}
		}
	}
	return P;
}