#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

//队列的数组实现
#ifndef _Queue_h
struct QueueRecord;
typedef QueueRecord* Queue;

void Error(void);
int IsEmpty(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(ElementType X, Queue Q);
void Dequeue(Queue Q);
ElementType Front(Queue Q);
ElementType FrontAndDequeue(Queue Q);

# endif 

#define MinQueueSize (5)

struct QueueRecord {
	int Capacity;//容量
	int Front;//队头
	int Rear;//队尾
	int Size;//队伍长度
	ElementType* Array;
};

//测试用

int main(void) {
	int A[20] = { 1,2,3,4,5,6,7,8,9,10};
	Queue Q = CreateQueue(10);
	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	for (int i = 0; i < 10; i++) {
		Enqueue(A[i], Q);
		printf("Front=%d   Q->front=%d   Q->rear=%d  Q->Size=%d \n", Front(Q), Q->Front, Q->Rear,Q->Size);
	}
	printf("...\n\n");
	MakeEmpty(Q);
	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	for (int i = 0; i < 10; i++) {
		Enqueue(A[i], Q);
		printf("Front=%d   Q->front=%d   Q->rear=%d  Q->Size=%d\n", Front(Q), Q->Front, Q->Rear, Q->Size);
	}
	printf("...\n\n");
	for (int i = 0; i < 10; i++) {
		Dequeue(Q);
		if (Q->Size == 0) {
			printf(",,,,   Q->front=%d   Q->rear=%d  Q->Size=%d\n", Q->Front, Q->Rear, Q->Size);
			break;
		}
		printf("Front=%d   Q->front=%d   Q->rear=%d  Q->Size=%d\n", Front(Q), Q->Front, Q->Rear, Q->Size);
	}
	printf("...\n\n");
	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	printf("...\n\n");
	for (int i = 0; i < 10; i++) {
		Enqueue(A[i], Q);
		printf("Front=%d   Q->front=%d   Q->rear=%d  Q->Size=%d\n", Front(Q), Q->Front, Q->Rear, Q->Size);
	}
	printf("...\n\n");
	for (int i = 0; i < 10; i++) {
		printf("Front=%d   Q->front=%d   Q->rear=%d  Q->Size=%d\n", FrontAndDequeue(Q), Q->Front, Q->Rear, Q->Size);
	}
	printf("...\n\n");

	if (IsEmpty(Q)) {
		printf("空队列\n");
	}
	DisposeQueue(Q);
	Enqueue(1,Q);
	
	return 0;
}

void Error(void) {
	printf("出错了");
}

int IsEmpty(Queue Q) {
	return Q->Size == 0;
}

Queue CreateQueue(int MaxElements) {
	Queue Q=(Queue)malloc(sizeof(struct QueueRecord));
	Q->Capacity = MaxElements;
	Q->Front = Q->Rear = 0;
	Q->Size = 0;
	Q->Array = (ElementType*)malloc(MaxElements * sizeof(ElementType));
	if (Q == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	return Q;
}

void DisposeQueue(Queue Q) {
	if (Q->Size != 0) {
		free(Q->Array);
	}
	free(Q);
	Q = NULL;
}

void MakeEmpty(Queue Q) {
	if (Q == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	if (Q->Size != 0) {
		Q->Size = 0;
		Q->Front = Q->Rear = 0;
	}
}

void Enqueue(ElementType X, Queue Q) {
	if (Q == NULL) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	if (Q->Size >= Q->Capacity) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	else {
		if (Q->Rear == Q->Capacity - 1) {
			Q->Array[Q->Rear] = X;
			Q->Rear = 0;
		}
		else {
			Q->Array[Q->Rear++] = X;
		}
		Q->Size++;
	}
}

void Dequeue(Queue Q) {
	if (Q == NULL || Q->Size == 0) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	if (Q->Front==Q->Capacity-1) {
		Q->Front = 0;
	}
	else {
		Q->Front++;
	}
	Q->Size--;
}

ElementType Front(Queue Q) {
	if (Q->Size == 0 || IsEmpty(Q)) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	return Q->Array[Q->Front];
}

ElementType FrontAndDequeue(Queue Q) {
	if (Q->Size == 0 || IsEmpty(Q)) {
		atexit(Error);
		exit(EXIT_FAILURE);
	}
	Dequeue(Q);
	if (Q->Front == 0) {
		return Q->Array[Q->Capacity - 1];
	}
	else {
		return Q->Array[Q->Front - 1];
	}
}
