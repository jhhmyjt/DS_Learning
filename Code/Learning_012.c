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
}SqQueue;

SqQueue InitQueue();
void EnQueue(SqQueue* Q,int a);
void DeQueue(SqQueue* Q);
int GetHead(const SqQueue* Q);
void QueueTraverse(const SqQueue* Q);

int main(){

    return 0;
}

SqQueue InitQueue(){
    SqQueue Q;
    Q.base=(int*) malloc(sizeof (int)*MAXSIZE);
    if(Q.base){
        printf("Init queue.Size: %d\n",MAXSIZE);
        Q.front=0;      //front和rear初始置为0，插入时rear+1，删除时front+1
        Q.rear=0;       //只有当front==0而rear==MAXSIZE时是真溢出
    } else{
        printf("Init failure.\n");
    }
    return Q;
}
void EnQueue(SqQueue* Q,int a){
    if((Q->rear+1)%MAXSIZE==Q->front){  //当rear指针在循环上加一等于front指针时说明队列已满
        printf("Queue is full.\n");
    } else{
        *(Q->base+Q->rear)=a;
        Q->rear=(Q->rear+1)%MAXSIZE;    //循环队列，在计算front和rear长度时要对总长MAXSIZE取模
    }
}
void DeQueue(SqQueue* Q){

}
int GetHead(const SqQueue* Q);
void QueueTraverse(const SqQueue* Q);