//
// Created by Duyou on 2022/4/19.
// Located at Learning_010.c in CLion Project: DS_Learning.
//

//栈的顺序存储实现

#include "stdio.h"
#include "stdlib.h"

#define MAXSIZE 100 //顺序栈初始空间分配大小

typedef struct {
    int *base;      //栈底指针，始终指向栈底
    int *top;       //栈顶指针，初值指向栈底，每插入第一新元素top+1，每删除一个元素top-1（因此top始终指向的是栈顶元素的上一个位置）
    int stackSize;  //栈可用最大容量
} SqStack;

SqStack InitStack();//初始化一个空栈
void Push(SqStack *S, int a);//将a压入栈中
int Pop(SqStack *S);    //弹出栈顶元素
int GetTop(const SqStack *S); //取栈顶元素
void StackTraverse(const SqStack *S);//从栈底到栈顶依次访问

int main() {
    SqStack S;
    int n;
    int a;
    S = InitStack();
    printf("Push to stack.\n");
    printf("Input the quantity:\n");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        printf("Input the number %d:\n", i + 1);
        scanf("%d", &a);
        Push(&S, a);
    }
    StackTraverse(&S);
    printf("The top is %d\n", GetTop(&S));
    printf("Pop the top %d.\n", Pop(&S));
    StackTraverse(&S);
    return 0;
}

//初始化一个空栈
SqStack InitStack() {
    SqStack S;
    S.base = (int *) malloc(sizeof(int) * MAXSIZE);
    if (!S.base) {
        printf("Init failure.\n");
        return S;
    } else {
        printf("Init SqStack.\n");
        S.top = S.base;
        S.stackSize = MAXSIZE;
        return S;
    }
}

//将a压入栈中
void Push(SqStack *S, int a) {
    if (!S || !(S->base)) {
        printf("Not exist.\n");
    } else if (S->top - S->base == S->stackSize) {
        printf("Stack is full.\n");
    } else {
        printf("Push %d into stack.\n", a);
        *(S->top) = a;
        (S->top)++;
    }
}

//弹出栈顶元素
int Pop(SqStack *S) {
    if (!S || !(S->base)) {
        printf("Not exist. return 0.\n");
        return 0;
    } else {
        int res = *(S->top - 1);
        S->top--;
        return res;
    }
}

//取栈顶元素
int GetTop(const SqStack *S) {
    if (!S || !(S->base)) {
        printf("Not exist. Return 0.\n");
        return 0;
    } else {
        return *(S->top - 1);
    }
}

//从栈底到栈顶依次访问
void StackTraverse(const SqStack *S) {
    if (!S || !(S->base)) {
        printf("Not exist.\n");
    } else if (S->top == S->base) {
        printf("Stack is empty.\n");
    } else {
        int *p = S->base;
        while (p != S->top) {
            printf("%d ", *p);
            p++;
        }
        printf("\n");
    }
}