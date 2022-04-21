//
// Created by Duyou on 2022/4/20.
// Located at Learning_015.c in CLion Project: DS_Learning.
//

//栈的应用-括号匹配检验

#include "stdlib.h"
#include "stdio.h"

typedef struct StackNode {
    char c;
    struct StackNode *next;
} StackNode, LinkStack;

LinkStack *Init();

LinkStack *Push(LinkStack *S, char c);

LinkStack *Pop(LinkStack *S);

char GetTop(const LinkStack *S);

void CheckMatch(char c[]);

int main() {
    char a[20];
    printf("Input:\n");
    scanf("%s", &a);
    CheckMatch(a);
    return 0;
}

LinkStack *Init() {
    LinkStack *S = NULL;
    return S;
}

LinkStack *Push(LinkStack *S, char c) {
    StackNode *p = (StackNode *) malloc(sizeof(StackNode));
    if (!p) {
        return NULL;
    } else {
        p->c = c;
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

char GetTop(const LinkStack *S) {
    return S->c;
}

void CheckMatch(char c[]) {
    char *p = c;
    LinkStack *S;
    S = Init();
    int flag = 1; //flag为状态变量，1为配对成功状态
    while (*p != '\0' && flag) {
        if (*p == '[' || *p == '(') {
            //左括号入栈
            S = Push(S, *p);
            p++;
        } else if (*p == ']') {
            if (GetTop(S) == '[') {
                S = Pop(S);
                p++;
            } else {
                flag = 0;
            }
        } else if (*p == ')') {
            if (GetTop(S) == '(') {
                S = Pop(S);
                p++;
            } else {
                flag = 0;
            }
        }
    }
    if (!S && flag) {
        printf("correct.\n");
    } else {
        printf("failure.\n");
    }
}
