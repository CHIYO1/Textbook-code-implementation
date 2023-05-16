#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int Elemtype;
# include<stdio.h>
# include<stdlib.h>

/*
//顺序表的实现
struct List {
    int list[40];
    int n;
};

void FatalEorror(void);//超出范围时的错误提示
void FatalEorror(void) {
    printf("Out of space!!!");
}

int IsEmpty(struct List list);//检查是否为空表，若为空则返回1；否则返回0
int IsEmpty(struct List list) {
    if (list.n == 0) {
        return OK;
    }
    return ERROR;
}

int PrintList(struct List list);//打印表中元素和表中元素个数
int PrintList(struct List list) {
    if (IsEmpty(list)) {
        printf("EMPTY\n");
        return 0;
    }
    for (int i = 0; i < list.n; i++) {
        printf("%d ", list.list[i]);
    }
    printf("\n%d\n", list.n);
    return 0;
}

struct List SetList(int list[], int n);//创建表
struct List SetList(int list[], int n) {
    struct List list1;
    for (int i = 0; i < n; i++) {
        list1.list[i] = list[i];
    }
    list1.n = n;
    return list1;
}

struct List MakeEmpty(struct List list);//初始化表
struct List MakeEmpty(struct List list) {
    if (!IsEmpty(list)) {
        list.n = 0;
    }
    return list;
}

int Find(struct List list, int key);//返回关键字首次出现的位置
int Find(struct List list, int key) {
    if (IsEmpty(list)) {
        return ERROR;
    }
    for (int i = 0; i < list.n; i++) {
        if (list.list[i] == key) {
            return i;
        }
    }
    return ERROR;
}

//在表中某个位置插入某个元素
struct List Insert(struct List list, int location, int key);//需要返回表才能改变表中内容，怀疑是编译器函数数据传递方式问题？
struct List Insert(struct List list, int location, int key) {    
    if (list.n == 40 && location>list.n) {//无法正常终止程序？？？
        atexit(FatalEorror);
        exit(EXIT_FAILURE);
    }
    for (int i = list.n - 1; i >= location; i--) {
        list.list[i + 1] = list.list[i];
    }
    list.list[location] = key;//"list.list" 时缓冲区溢出。???
    list.n += 1;
    return list;
}

struct List Delete(struct List a, int location);//删除表中某个位置的元素
struct List Delete(struct List a, int location) {
    if (location >= a.n) {
        atexit(FatalEorror);
        exit(EXIT_FAILURE);
    }
    for(int i=location;i<a.n;i++){
        a.list[i] = a.list[i + 1];
    }
    a.n -= 1;
    return a;
}

int FindKth(struct List list, int location);//返回某个位置上的元素
int FindKth(struct List list, int location) {
    if (location >= list.n) {
        atexit(FatalEorror);
        exit(EXIT_FAILURE);
    }
    return list.list[location];
}


//测试用
int main(void) {
    int num[5] = { 0,1,2,3,4 };
    int k;
    struct List list1 = SetList(num, 5);
    PrintList(list1);
    k = FindKth(list1, 3);
    printf("%d", k);
    return 0;

}

*/

//链表实现
struct Node {
    Elemtype val;
    struct Node* next;
};

typedef struct Node Sqlist;

void FatalEorror(void);//超出范围时的错误提示
void FatalEorror(void) {
    printf("Out of space!!!");
}

Sqlist* Setlist(Elemtype a[],int n);//初始化链表
Sqlist* Setlist(Elemtype a[],int n) {
    Sqlist* head = (Sqlist*)malloc(sizeof(Sqlist));
    if (n == 0) {
        head->next= NULL;
        return head;
    }
    Sqlist* q;
    q = head;
    for (int i = 0; i < n; i++) {
        Sqlist* p = (Sqlist*)malloc(sizeof(Sqlist));
        p->val = a[i];
        q->next = p;
        q = p;
        q->next = NULL;
    }
    return head;
}

int IsEmpty(Sqlist* q);//检查链表是否为空表
int IsEmpty(Sqlist* q) {
    if (q->next == NULL) {
        return OK;
    }
    return ERROR;
}

void PrintList(Sqlist* q);//打印链表
void PrintList(Sqlist* q) {
    if (IsEmpty(q)) {
        printf("NULL\n");
        //exit(EXIT_SUCCESS);//不知道为什么无法只结束本函数，而会终止整个程序
    }
    else {
        Sqlist* p = q->next;
        while (p) {
            printf("%d  ", p->val);
            p = p->next;
        }
        printf("\n");
    }
}

int Find(Sqlist* q, Elemtype key);//查找目标元素在第几个位置
int Find(Sqlist* q, Elemtype key) {
    if (IsEmpty(q)) {
        return ERROR;
    }
    int n=1;
    Sqlist* p = q->next;
    while (p) {
        if (p->val == key) {
            return n;
        }
        p = p->next;
        n++;
    }
    return FALSE;
}

void Insert(Sqlist* q, int location, Elemtype key);//在某位置插入某元素
void Insert(Sqlist* q, int location, Elemtype key) {
    int n = 0;
    Sqlist* p = q->next;
    Sqlist* m;
    if (location == 1) {
        m = (Sqlist*)malloc(sizeof(Sqlist));
        m->val = key;
        m->next = q->next;
        q->next = m;
    }
    while (p) {
        n++;
        if (n == location-1) {
            m = (Sqlist*)malloc(sizeof(Sqlist));
            m->val = key;
            m->next = p->next;
            p->next = m;
            break;
        } 
        p = p->next;
    }
    if (n < location-1) {
        atexit(FatalEorror);
        exit(EXIT_SUCCESS);
    }
}

void Delete(Sqlist* q, int location);//删除某位置上的元素
void Delete(Sqlist* q, int location) {
    int n=1;
    Sqlist* p = q->next;
    Sqlist* s=q;
    while (p) {
        if (n == location) {
            s->next = p->next;
            free(p);
            break;
        }
        p = p->next;
        s = s->next;
        n++;
    }
    if (IsEmpty(q) || n < location || location == 0) {
        atexit(FatalEorror);
        exit(EXIT_FAILURE);
    }
}

void Clean(Sqlist* q);//清空链表中元素
void Clean(Sqlist* q) {
    Sqlist* p = q->next;
    Sqlist* s;
    while (p) {
        s = p;
        p = p->next;
        free(s);
    }
    q->next = NULL;
}

int main(void) {
    int a[5] = {0,1,2,3,4};
    Sqlist* list1;
    list1 = Setlist(a,5);
    PrintList(list1);
    Clean(list1);
    PrintList(list1);
    return 0;
}