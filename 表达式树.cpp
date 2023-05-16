#include<stdio.h>
#include<stdlib.h>

typedef char ELementType;
typedef struct TreeNode* PtrToNode;

struct TreeNode {
	ELementType data;
	PtrToNode lchild;
	PtrToNode rchild;
};

PtrToNode Create(const char* S);
PtrToNode Create(const char* S) {
	PtrToNode Stack[10];
	PtrToNode p;
	int i=0;
	while (*S!='\0') {
		p = (PtrToNode)malloc(sizeof(struct TreeNode));
		p->data = *S;
		p->lchild = p->rchild = NULL;
		if (*S == '+' || *S == '-' || *S == '*' || *S == '/') {
			p->rchild = Stack[--i];
			p->lchild = Stack[--i];
		}
		Stack[i++] = p;
		S++;
	}
	return Stack[0];//不能返回Stack[i],因为最后一次压入栈后i=1。
}

void PrintTree(PtrToNode p);
void PrintTree(PtrToNode p) {
	if (p->lchild) {
		PrintTree(p->lchild);
	}
	if (p->rchild) {
		PrintTree(p->rchild);
	}
	printf("%c", p->data);
}

int main(void) {
	const char* s = "ab+cde+**";
	PtrToNode T = Create(s);
	PrintTree(T);
	return 0;
}