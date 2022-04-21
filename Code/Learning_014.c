//
// Created by Duyou on 2022/4/20.
// Located at Learning_014.c in CLion Project: DS_Learning.
//

//栈的应用：进制转换
//使用链栈，链栈存储灵活，栈空，栈满易判断

#include "stdio.h"
#include "stdlib.h"

typedef struct StackNode {
    int a;
    struct StackNode *next;
} LinkStack, StackNode;

LinkStack *Init();

LinkStack *Push(LinkStack *S, int a);

LinkStack *Pop(LinkStack *S);

int GetTop(const LinkStack *S);

void ConvertToBin(int n);

int main() {
    int n;
    printf("This function convert decimal to binary. Input a non-negative integer:\n");
    scanf("%d", &n);
    ConvertToBin(n);
    return 0;
}

LinkStack *Init() {
    LinkStack *S = NULL;
    return S;
}

LinkStack *Push(LinkStack *S, int a) {
    StackNode *p = (StackNode *) malloc(sizeof(StackNode));
    if (!p) {
        return NULL;
    } else {
        p->a = a;
        p->next = S;
        S = p;
        return S;
    }
}

LinkStack *Pop(LinkStack *S) {
    if (!S) {
        return NULL;
    } else {
        StackNode *p = S;
        S = S->next;
        free(p);
        return S;
    }
}

int GetTop(const LinkStack *S) {
    return S->a;
}

void ConvertToBin(int n) {
    LinkStack *S;
    S = Init();
    //将余数压入栈中
    while (n != 0) {
        S = Push(S, n % 2);
        n /= 2;
    }
    int count = 1;
    //依次将余数弹出栈
    while (S) {
        printf("%d", GetTop(S));
        S = Pop(S);
        if (count % 4 == 0) {
            printf(",");
        }
        count++;
    }
    printf("\n");
}