//打印出目录中所以文件的名字。格式：深度为Di的文件的名字将被第Di次跳格（Tab）缩进后打印出来（利用树的先序遍历）
//利用后序遍历按上面格式打印文件名字和对应文件大小，文件大小向右对齐打印

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef const char* ElementType;
typedef struct TreeNode* PtrToNode;
typedef struct Data Data;

struct Data {
	ElementType Name;
	int Size;
};

struct TreeNode {
	Data Element;
	PtrToNode FirstChild;
	PtrToNode NextSibling;
};

//创造测试要用的树
PtrToNode CreateTree(void);
PtrToNode CreateTree(void) {
	int i = 0;
	char ch;
	PtrToNode t= (PtrToNode)malloc(sizeof(struct TreeNode));
	printf("输入这个节点的名字：\n");
	t->Element.Name = (const char*)malloc(10 * sizeof(char));
	scanf_s("%s", t->Element.Name, 10);
	printf("输入这个节点的大小：\n");
	scanf_s("%d", &t->Element.Size);

	printf("%s是否有子节点：(有子节点的话输入1，没有则输入N)\n",t->Element.Name);
	if (scanf("%d", &i)) {
		t->FirstChild = CreateTree();
	}
	else {
		while (ch=getchar()!='\n') {
		}
		t->FirstChild = NULL;
	}

	printf("%s是否有兄弟节点：（有的话输入1，否则输入N）\n", t->Element.Name);
	if (scanf("%d", &i)) {
		t->NextSibling = CreateTree();
	}
	else {
		while (ch = getchar() != '\n') {
		}
		t->NextSibling = NULL;
	}
	return t;
}

//打印节点(用于第一个任务)
void PrintNode(PtrToNode p, int n);//输入节点地址和节点深度
void PrintNode(PtrToNode p, int n) {
	for (int i = 0; i < n; i++) {
		printf("   ");
	}
	printf("%-8s", p->Element.Name);
	for (int j = 0; j < (5 - n); j++) {
		printf("   ");
	}
	printf("%3d\n", p->Element.Size);
}

//打印目录
void ListDir(PtrToNode root,int Depth);
void ListDir(PtrToNode root,int Depth) {
	PrintNode(root, Depth);
	if (root->FirstChild) {
		ListDir(root->FirstChild, Depth + 1);
	}
	if (root->NextSibling) {
		ListDir(root->NextSibling, Depth);
	}
}

//打印节点（用于第二个任务）
void PrintTree(PtrToNode p, int n, int size);
void PrintTree(PtrToNode p, int n, int size) {
	for (int i = 0; i < n; i++) {
		printf("   ");
	}
	printf("%-8s", p->Element.Name);
	for (int j = 0; j < (5 - n); j++) {
		printf("   ");
	}
	printf("%3d\n", size);
}

//打印文件大小
int SizeDirectory(PtrToNode root,int Depth);
int SizeDirectory(PtrToNode root,int Depth) {
	int TotalSize1 = 0;
	int TotalSize2 = 0;
	if (root->FirstChild) {
		TotalSize1=SizeDirectory(root->FirstChild, Depth + 1);
	}
	TotalSize1 += root->Element.Size;
	PrintTree(root, Depth, TotalSize1);
	if (root->NextSibling) {
		TotalSize2 = SizeDirectory(root->NextSibling, Depth);
	}
	return TotalSize1 + TotalSize2;
}

//测试用主函数
int main(void) {
	PtrToNode Tree=CreateTree();
	ListDir(Tree, 0);
	SizeDirectory(Tree, 0);
	return 0;
}
