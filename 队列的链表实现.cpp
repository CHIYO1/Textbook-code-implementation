#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

//队列的链表实现
#ifndef _Queue_h
struct QueueRecord;
struct QueueNode;
typedef struct QueueRecord* Queue;
typedef struct QueueNode* Qnode;

void Error(void);
int IsEmpty(Queue Q);
Queue CreateQueue(void);
void DisposeQueue(Queue* Q);//销毁队列后要把原指针指向NULL,应该传入二级指针才能改变原指针！！！
void MakeEmpty(Queue Q);
void Enqueue(ElementType X, Queue Q);
void Dequeue(Queue Q);
ElementType Front(Queue Q);
ElementType FrontAndDequeue(Queue Q);
#endif

struct QueueRecord {
	Qnode front;
	Qnode Rear;
	int Size;
};

struct QueueNode {
	ElementType date;
	Qnode next;
};

int main(void) {
	int A[20] = { 1,2,3,4,5,6,7,8,9,10 };
	Queue Q = CreateQueue();
	/*
	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	for (int i = 0; i < 10; i++) {
		Enqueue(A[i], Q);
		printf("Front=%d     Q->rear->date=%d  Q->Size=%d \n", Front(Q), Q->Rear->date, Q->Size);
	}
	printf("...\n\n");
	MakeEmpty(Q);
	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	
	for (int i = 0; i < 10; i++) {
		Enqueue(A[i], Q);
		printf("Front=%d     Q->rear->date=%d  Q->Size=%d \n", Front(Q), Q->Rear->date, Q->Size);
	}
	printf("...\n\n");
	
	for (int i = 0; i < 10; i++) {
		Dequeue(Q);
		if (IsEmpty(Q)) {
			printf("  Q->Size=%d \n", Q->Size);
			break;
		}
		printf("Front=%d     Q->rear->date=%d  Q->Size=%d \n", Front(Q), Q->Rear->date, Q->Size);
	}
	printf("...\n\n");

	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	printf("...\n\n");
	*/
	for (int i = 0; i < 10; i++) {
		Enqueue(A[i], Q);
		printf("Front=%d     Q->rear->date=%d  Q->Size=%d \n", Front(Q), Q->Rear->date, Q->Size);
	}
	printf("...\n\n");
	for (int i = 0; i < 10; i++) {
		printf("   Q->rear->date=%d  Q->Size=%d   ", Q->Rear->date, Q->Size);
		printf("Front=%d    \n", FrontAndDequeue(Q));
		if (IsEmpty(Q)) {
			printf("Q->Size=%d\n", Q->Size);
		}
	}
	printf("...\n\n");

	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	DisposeQueue(&Q);
	printf("%p\n", Q);
	Enqueue(1, Q);

	return 0;
}


void Error(void) {
	printf("出错了\n");
}

int IsEmpty(Queue Q) {
	return Q->Size == 0;
}

Queue CreateQueue(void) {
	Queue Q = (Queue)malloc(sizeof(struct QueueRecord));
	if (Q == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	Q->front = Q->Rear = NULL;
	Q->Size = 0;
	return Q;
}

void DisposeQueue(Queue* Q) {
	if (!IsEmpty(*Q)) {
		MakeEmpty(*Q);
	}
	free(*Q);
	*Q = NULL;
}

void MakeEmpty(Queue Q) {
	if (Q == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	if (Q->Size != 0) {
		Qnode p;
		while (Q->front) {
			p = Q->front->next;
			free(Q->front);
			Q->front = p;
		}
	}
	Q->Size = 0;
}

void Enqueue(ElementType X, Queue Q) {
	if (Q == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	if (IsEmpty(Q)) {
		Q->front = Q->Rear = (Qnode)malloc(sizeof(struct QueueNode));
		Q->Rear->date = X;
		Q->Rear->next = NULL;
		Q->Size = 1;
	}
	else {
		Q->Rear->next = (Qnode)malloc(sizeof(struct QueueNode));
		Q->Rear = Q->Rear->next;
		Q->Rear->date = X;
		Q->Rear->next = NULL;
		Q->Size++;
	}
}

void Dequeue(Queue Q) {
	if (Q == NULL || IsEmpty(Q)) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	Qnode p = Q->front;
	Q->front = Q->front->next;
	free(p);
	Q->Size--;
}

ElementType Front(Queue Q) {
	if (Q == NULL || IsEmpty(Q)) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	return Q->front->date;
}

ElementType FrontAndDequeue(Queue Q) {
	int a = Front(Q);
	Dequeue(Q);
	return a;
}
