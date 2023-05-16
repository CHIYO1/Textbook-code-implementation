/*
多重表应用：假设有5个学生和四门课程，建立多重链表使后续可以查找某个学生报了哪些课程，或者查询某门课程有哪些学生报名。
利用每个学生所报课程数据来初始化多重链表
*/

#include<stdio.h>
#include<stdlib.h>

//多重链表节点，指向下个班级的地址和下一个学生的地址
struct node {
	struct node* next_s;
	struct node* next_c;
	int Stu;
	int Cla;
};
typedef struct node* PtrtoNode;

//创建多重链表，函数输入值为学生报名课程信息数组，课程母表，学生母表
void Multi_list(int S[5][4],PtrtoNode St[5], PtrtoNode C[4]);
void Multi_list(int S[5][4], PtrtoNode St[5], PtrtoNode C[4]) {
	for (int i = 0; i < 5; i++) {
		St[i] = NULL;
	}
	for (int j = 0; j < 4; j++) {
		C[j] = NULL;
	}

	//下面代码不知道为什么无法改变数组St和C的值,

	PtrtoNode Sp, Cp;//分别用来后续循环某学生对应链表和某课程对应链表
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			//等于1时证明i学生报了j课程
			if (S[i][j] == 1) {
				if (St[i] == NULL) {
					St[i] = (PtrtoNode)malloc(sizeof(PtrtoNode));
					St[i]->Cla = j;
					St[i]->next_c = NULL;
					St[i]->next_s = NULL;
					St[i]->Stu = i;
					Sp = St[i];
				}
				else {
					Sp = St[i];
					//令标记指针到达某学生链表末尾
					while (Sp->next_c) {
						Sp = Sp->next_c;
					}
					Sp->next_c = (PtrtoNode)malloc(sizeof(PtrtoNode));//创建双链表节点
					Sp = Sp->next_c;
					Sp->next_c = NULL;
					Sp->Stu = i;
					Sp->Cla = j;
					Sp->next_s = NULL;
				}

				if (C[j] == NULL) {
					C[j] = Sp;
				}
				else {
					Cp = C[j];
					//令标记指针到达某课程链表末尾
					while (Cp->next_s) {
						Cp = Cp->next_s;
					}
					Cp->next_s= Sp;
				}
			}
		}
	}
}

void Find_s(PtrtoNode St[5],int i);//查找某个学生报了哪些课程
void Find_s(PtrtoNode St[5],int i) {
	PtrtoNode Sp;
	Sp = St[i];
	printf("学生 %d 报名了这些课程：\n", i);
	while (Sp) {
		printf("课程%d  ", (Sp->Cla));
		Sp = Sp->next_c;
	}
	printf("\n");
}

void Find_c(PtrtoNode C[4], int j);//查找某门课程有哪些学生报名
void Find_c(PtrtoNode C[4], int j) {
	PtrtoNode Cp;
	Cp = C[j];
	printf("课程 %d 有这些学生报名： \n", j);
	while (Cp) {
		printf("学生%d  ", (Cp->Stu));
		Cp = Cp->next_s;
	}
	printf("\n");
}

//测试用主函数
int main(void) {
	//用数组的形式记录学生是否报了某个课程，报了记为1，没报记为0
	int S[5][4] = {
		{1,0,1,0},
		{0,1,0,1},
		{1,0,1,0},
		{1,0,1,1},
		{0,1,1,0}
	};
	PtrtoNode Students[5];
	PtrtoNode Class[4];
	Multi_list(S, Students, Class);
	Find_c(Class, 2);
	Find_s(Students, 1);
	return 0;
}

