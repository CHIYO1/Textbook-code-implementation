#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;

//链表实现
/*
struct Node {
	ElementType date;
	struct Node* next;
};
typedef struct Node* Stack;

void FatalError(void);//报错
int IsEmpty(Stack S);//判断是否为空栈
Stack CreatStack(void);//创建空栈
void DisposeStack(Stack S);//销毁栈
void MakeEmpty(Stack S);//清空栈
void Push(ElementType X, Stack S);//进栈
ElementType Top(Stack S);//返回栈顶元素
ElementType Pop(Stack S);//出栈并返回元素

int main(void) {
	Stack S;
	int a[5] = { 0,1,2,3,4 };
	S = CreatStack();
	for (int i = 0; i < 5; i++) {
		Push(a[i], S);
	}
	while (!IsEmpty(S)) {
		printf("%d\n", Top(S));
		printf("%d\n", Pop(S));
	}
	if (IsEmpty(S)) {
		printf("NULL\n");
	}
	for (int i = 0; i < 5; i++) {
		Push(a[i], S);
	}
	MakeEmpty(S);
	if (IsEmpty(S)) {
		printf("NULL\n");
	}
	DisposeStack(S);
	return 0;
}

void FatalError(void) {
	printf("Out of space!!!");
}

int IsEmpty(Stack S) {
	return S->next == NULL;
}

Stack CreatStack(void) {
	Stack S = (Stack)malloc(sizeof(struct Node));
	if (S == NULL) {
		atexit(FatalError);
		exit(EXIT_FAILURE);
	}
	S->next = NULL;
	return S;
}

void DisposeStack(Stack S) {
	if (IsEmpty(S)) {
		free(S);
	}
	else {
		Stack p, q;
		p = S;
		while (p) {
			q = p->next;
			free(p);
			p = q;
		}
	}
}

void MakeEmpty(Stack S) {
	if (!IsEmpty(S)) {
		Stack p, q;
		p = S->next;
		S->next = NULL;
		while (p) {
			q = p->next;
			free(p);
			p = q;
		}
	}
}

void Push(ElementType X, Stack S) {
	if (!S) {
		exit(EXIT_FAILURE);
	}
	Stack p;
	p = S->next;
	S->next= (Stack)malloc(sizeof(struct Node));
	if (S->next == NULL) {
		atexit(FatalError);
		exit(EXIT_FAILURE);
	}
	S->next->date = X;
	S->next->next = p;
}

ElementType Top(Stack S) {
	if (IsEmpty(S)) {
		exit(EXIT_FAILURE);
	}
	return S->next->date;
}

ElementType Pop(Stack S) {
	if (IsEmpty(S)) {
		exit(EXIT_FAILURE);
	}
	ElementType X;
	Stack p;
	p = S->next;
	S->next = p->next;
	X = p->date;
	free(p);
	return X;
}

*/


//数组实现
#define EmptyTOS (-1)
#define MinStackSize (5)

struct stack {
	int Capacity;
	int TopOfStack;
	ElementType* Array;
};
typedef struct stack* Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreatStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

int main(void) {
	Stack S;
	int a[5] = { 0,1,2,3,4 };
	S = CreatStack(10);
	for (int i = 0; i < 5; i++) {
		Push(a[i], S);
	}
	while (!IsEmpty(S)) {
		printf("%d\n", Top(S));
		Pop(S);
		//printf("%d\n", TopAndPop(S));
	}
	if (IsEmpty(S)) {
		printf("NULL\n");
	}
	for (int i = 0; i < 5; i++) {
		Push(a[i], S);
	}
	MakeEmpty(S);
	if (IsEmpty(S)) {
		printf("NULL\n");
	}
	DisposeStack(S);
	return 0;
}

int IsEmpty(Stack S) {
	return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S) {
	return S->TopOfStack == S->Capacity-1;
}

Stack CreatStack(int MaxElements) {
	Stack S;
	if (MaxElements < MinStackSize) {
		exit(EXIT_FAILURE);
	}
	S = (Stack)malloc(sizeof(struct stack));
	if (S == NULL) {
		exit(EXIT_FAILURE);
	}
	S->Capacity = MaxElements;
	S->TopOfStack = EmptyTOS;
	S->Array = (ElementType*)malloc(sizeof(ElementType) * MaxElements);
	if (S->Array == NULL) {
		exit(EXIT_FAILURE);
	}
	return S;
}

void DisposeStack(Stack S) {
	if (S != NULL) {
		free(S->Array);
		free(S);
	}
}

void MakeEmpty(Stack S) {
	S->TopOfStack = EmptyTOS;
}

void Push(ElementType X, Stack S) {
	if (S == NULL) {
		exit(EXIT_FAILURE);
	}
	if (S->TopOfStack == S->Capacity - 1) {
		exit(EXIT_FAILURE);
	}
	S->Array[++S->TopOfStack] = X;
}

ElementType Top(Stack S) {
	if (IsEmpty(S)) {
		exit(EXIT_FAILURE);
	}
	return S->Array[S->TopOfStack];
}

void Pop(Stack S) {
	if (IsEmpty(S)) {
		exit(EXIT_FAILURE);
	}
	S->TopOfStack--;
}

ElementType TopAndPop(Stack S) {
	if (IsEmpty(S)) {
		exit(EXIT_FAILURE);
	}
	return S->Array[S->TopOfStack--];
}

