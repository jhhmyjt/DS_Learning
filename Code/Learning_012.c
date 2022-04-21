//
// Created by Duyou on 2022/4/19.
// Located at Learning_012.c in CLion Project: DS_Learning.
//

//循环队列，队列的顺序结构实现

#include "stdio.h"
#include "stdlib.h"

#define MAXSIZE 100

typedef struct {
    int *base;  //存储空间的基地址
    int front;  //队列的头指针，始终指向队列头元素
    int rear;   //队列的尾指针，始终指向队列尾元素的下一个
} SqQueue;

SqQueue InitQueue();

void EnQueue(SqQueue *Q, int a);

void DeQueue(SqQueue *Q);

int GetHead(const SqQueue *Q);

void QueueTraverse(const SqQueue *Q);

int main() {
    SqQueue Q;
    int n;
    int a;
    Q = InitQueue();
    printf("Enter the queue.\n");
    printf("Input the quantity:\n");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        printf("the number %d:\n", i + 1);
        scanf("%d", &a);
        EnQueue(&Q, a);
    }
    QueueTraverse(&Q);
    printf("Delete the top %d.\n", GetHead(&Q));
    DeQueue(&Q);
    QueueTraverse(&Q);
    return 0;
}

SqQueue InitQueue() {
    SqQueue Q;
    Q.base = (int *) malloc(sizeof(int) * MAXSIZE);
    if (Q.base) {
        printf("Init queue.Size: %d\n", MAXSIZE);
        Q.front = 0;      //front和rear初始置为0，插入时rear+1，删除时front+1
        Q.rear = 0;       //只有当front==0而rear==MAXSIZE时是真溢出
    } else {
        printf("Init failure.\n");
    }
    return Q;
}

void EnQueue(SqQueue *Q, int a) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {  //当rear指针在循环上加一等于front指针时说明队列已满
        printf("Queue is full.\n");
    } else {
        //插入元素队尾，rear+1
        *(Q->base + Q->rear) = a;
        Q->rear = (Q->rear + 1) % MAXSIZE;    //循环队列，在计算front和rear长度时要对总长MAXSIZE取模
        printf("Enter %d\n", *(Q->base + Q->rear - 1));
    }
}

void DeQueue(SqQueue *Q) {
    if (Q->front == Q->rear) {
        printf("Queue is empty.\n");
    } else {
        //在队首删除元素，front+1
        Q->front = (Q->front + 1) % MAXSIZE;
    }
}

int GetHead(const SqQueue *Q) {
    if (Q->front == Q->rear) {
        printf("Queue is empty. Return 0.\n");
        return 0;
    } else {
        return *(Q->base + Q->front);
    }
}

void QueueTraverse(const SqQueue *Q) {
    int p = Q->front;
    while (p % MAXSIZE != Q->rear) {
        printf("%d ", *(Q->base + p));
        p = (p + 1) % MAXSIZE;
    }
    printf("\n");
}