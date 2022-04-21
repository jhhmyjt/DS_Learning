//
// Created by Duyou on 2022/4/20.
// Located at Learning_013.c in CLion Project: DS_Learning.
//

//队列的链表实现

#include "stdlib.h"
#include "stdio.h"

typedef struct QNode {
    int a;
    struct QNode *next;
} QNode, QPointer;
//与链栈不同，链队需要另外的头指针和尾指针来指示插入和删除操作，而且一般链队需要头结点
typedef struct {
    QPointer *front;
    QPointer *rear;
} LinkQueue;

LinkQueue InitQueue();

void EnQueue(LinkQueue *Q, int a);

void DeQueue(LinkQueue *Q);

int GetHead(const LinkQueue *Q);

void QueueTraverse(const LinkQueue *Q);

int main() {
    LinkQueue Q;
    int n;
    int a;
    Q = InitQueue();
    printf("Enter the queue.");
    printf("Input the quantity:\n");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        printf("Number %d:\n", i + 1);
        scanf("%d", &a);
        EnQueue(&Q, a);
    }
    QueueTraverse(&Q);
    printf("Delete the top number: %d\n", GetHead(&Q));
    DeQueue(&Q);
    QueueTraverse(&Q);
    return 0;
}

LinkQueue InitQueue() {
    LinkQueue Q;
    QPointer *p = (QPointer *) malloc(sizeof(QPointer));//声明一个结点作为头结点
    if (!p) {
        printf("Init failure.\n");
    } else {
        printf("Queue init done.\n");
        p->next = NULL;
        Q.front = p;    //队列的头指针始终指向链表的头结点
        Q.rear = p;     //队列的尾指针始终指向链表的尾元素，初始指向头结点
    }
    return Q;
}

void EnQueue(LinkQueue *Q, int a) {
    QNode *p = (QNode *) malloc(sizeof(QNode));
    if (!p) {
        printf("Enter failure.\n");
    } else {
        //在链表的尾部插入元素
        p->a = a;
        p->next = NULL;
        Q->rear->next = p;
        Q->rear = p;
        printf("Enter %d done.\n", Q->rear->a);
    }
}

void DeQueue(LinkQueue *Q) {
    if (Q->rear == Q->front) {
        printf("Queue is empty.\n");
    } else {
        QNode *p = Q->front->next;//p指向要被释放的结点
        Q->front->next = p->next;//头结点的next指向被释放结点的next
        //如果这是最后一个元素，队尾指针指向的空间被释放，队尾指针重新指向头结点
        if (Q->rear == p) {
            Q->rear = Q->front;
        }
        printf("Free %d done.\n", p->a);
        free(p);
    }
}

int GetHead(const LinkQueue *Q) {
    return Q->front->next->a;
}

void QueueTraverse(const LinkQueue *Q) {
    if (Q->rear == Q->front) {
        printf("Queue is empty.\n");
    } else {
        printf("Traverse the queue:\n");
        QNode *p = Q->front->next;
        while (p != Q->rear) {
            printf("%d ", p->a);
            p = p->next;
        }
        printf("%d\n", Q->rear->a);
    }
}