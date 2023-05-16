//检查一段字符串中是否每个括号（） [] {}都有对应的左右括号

#include<stdio.h>
#include<stdlib.h>
//引用栈的相关操作
#define EmptyTOS (-1)
#define MinStackSize (5)

typedef char ElementType;
struct stack {
	int Capacity;
	int TopOfStack;
	char* Array;
};
typedef struct stack* Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreatStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
ElementType Top(Stack S);
void Push(char X, Stack S);
void Pop(Stack S);
void FatalError(void);

//主要实现
int main(void) {
	char S[] = "][[{()}]][({})]";
	Stack A = CreatStack(10);
	if (S[0] == ')' || S[0] == '}' || S[0] == ']') {
		atexit(FatalError);
		exit(EXIT_FAILURE);
	}
	for (int i=0; S[i]!='\0'; i++) {
		if (S[i]== '['||S[i]=='('||S[i]=='{') {
			Push(S[i], A);
		}
		if (S[i] == ']') {
			if (Top(A) == '[') {
				Pop(A);
			}
			else {
				atexit(FatalError);
				exit(EXIT_FAILURE);
			}
		}
		if (S[i] == ')') {
			if (Top(A) == '(') {
				Pop(A);
			}
			else {
				atexit(FatalError);
				exit(EXIT_FAILURE);
			}
		}
		if (S[i] == '}') {
			if (Top(A) == '{') {
				Pop(A);
			}
			else {
				atexit(FatalError);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (!IsEmpty(A)) {
		atexit(FatalError);
		exit(EXIT_FAILURE);
	}
	printf("没问题\n");
	return 0;
}

int IsEmpty(Stack S) {
	return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S) {
	return S->TopOfStack == S->Capacity - 1;
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

void Pop(Stack S) {
	if (IsEmpty(S)) {
		exit(EXIT_FAILURE);
	}
	S->TopOfStack--;
}

ElementType Top(Stack S) {
	if (IsEmpty(S)) {
		exit(EXIT_FAILURE);
	}
	return S->Array[S->TopOfStack];
}

void FatalError(void) {
	printf("出错了\n");
}