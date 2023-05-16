//设有20个数，范围在0到999之间
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//定义列表的结构
struct list {
	int sqlist[20];
	int num;
};
typedef struct list Sqlist;
//定义桶的结构
struct bucket {
	int date;
	struct bucket* next;
};
typedef struct bucket* Buck;

void Clear(Buck node);//导出后清理上次排序占用的内存
void Clear(Buck node) {
	Buck q, p;
	q = node;
	while (q) {
		p = q->next;
		free(q);
		q = p;
	}
}

//想利用函数改变数组的值得传入指针！！！！否则传入后创建的是局部变量，无法改变函数外的值！！！！

void Sorted(Sqlist* q);//基数排序
void Sorted(Sqlist* q) {
	Buck bucket[10];
	int mark;
	for (int i = 1; i <= 3; i++) {
		for (int n = 0; n < 10; n++) {
			bucket[n] = NULL;
		}
		for (int k = 0; k < q->num; k++) {
			//利用循环将列表的数读进桶中	
			//先按个位排序，然后十位，最后百位（因为假设范围为0-999）
			if (i == 1) {
				mark = q->sqlist[k] % 10;
			}
			else if (i == 2) {
				mark = (q->sqlist[k] / 10) % 10;
			}
			else if (i == 3) {
				mark = (q->sqlist[k] / 100) % 10;
			}
			//每次循环初始化桶元素为NULL
			if (bucket[mark] == NULL) {
				bucket[mark] = (Buck)malloc(sizeof(struct bucket));
				bucket[mark]->date = q->sqlist[k];
				bucket[mark]->next = NULL;
				continue;
			}
			else {
				Buck flag = bucket[mark];
				while (flag->next) {
					flag = flag->next;
				}
				flag->next = (Buck)malloc(sizeof(struct bucket));
				flag = flag->next;
				flag->date = q->sqlist[k];
				flag->next = NULL;
			}
		}
		//将桶中数有序导出
		int x = 0;//每次重新导出数据用
		for (int s = 0; s < 10; s++) {
			if (bucket[s] != NULL) {
				Buck ptr = bucket[s];
				while (ptr) {
					q->sqlist[x] = ptr->date;
					x++;
					ptr = ptr->next;
				}
			}
			Clear(bucket[s]);
		}
	}
}

//测试用
int main(void) {
	Sqlist list;
	int a[20] = { 234,635,225,32,56,1,50,767,567,35,23,89,4,8,93,38,73,67,842,29 };
	for (int i = 0; i < 20; i++) {
		list.sqlist[i] = a[i];
	}
	list.num = 20;
	Sorted(&list);
	for (int k = 0; k < 20; k++) {
		printf("%d ", list.sqlist[k]);
	}
	printf("\n");
	return 0;
}


