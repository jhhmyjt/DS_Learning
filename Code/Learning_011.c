//
// Created by Duyou on 2022/4/19.
// Located at Learning_011.c in CLion Project: DS_Learning.
//

//栈的链表实现

#include "stdlib.h"
#include "stdio.h"

//不同普通单链表，链栈不需要头结点。因为栈只需要在栈顶插入和删除，将链表的头部作为栈顶较为方便
typedef struct StackNode {
    int a;
    struct StackNode *next;
} StackNode, LinkStack;

LinkStack *InitStack(); //初始化一个空栈
LinkStack *Push(LinkStack *S, int a);

LinkStack *Pop(LinkStack *S);

int GetTop(const LinkStack *S);

void StackTraverse(const LinkStack *S);

int main() {
    LinkStack *S;
    int n;
    int a;
    S = InitStack();
    printf("Push to stack.\n");
    printf("Input the quantity:\n");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        printf("The number %d:\n", i + 1);
        scanf("%d", &a);
        S = Push(S, a);
    }
    StackTraverse(S);
    printf("\nPop the top %d.\n", GetTop(S));
    S = Pop(S);
    StackTraverse(S);
    return 0;
}

//初始化一个空栈
LinkStack *InitStack() {
    //不需要头结点，栈顶指针指向NULL
    printf("Init stack.\n");
    LinkStack *S = NULL;
    return S;
}

LinkStack *Push(LinkStack *S, int a) {
    StackNode *p = (StackNode *) malloc(sizeof(StackNode));
    if (!p) {
        printf("Push failure.\n");
    } else {
        p->a = a;
        p->next = S;
        S = p;
        printf("Push %d.\n", a);
        return S;
    }
}

LinkStack *Pop(LinkStack *S) {
    if (!S) {
        printf("Stack is empty. Return 0.\n");
        return NULL;
    } else {
        StackNode *p = S;
        S = p->next;
        free(p);
        return S;
    }
}

int GetTop(const LinkStack *S) {
    if (!S) {
        printf("Stack is empty. Return 0.\n");
        return 0;
    } else {
        return S->a;
    }
}

void StackTraverse(const LinkStack *S) {
    //递归从栈底到栈顶依次打印元素
    if (!S) {

    } else {
        StackTraverse(S->next);
        printf("%d ", S->a);
    }
}
