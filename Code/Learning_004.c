//
// Created by Duyou on 2022/4/15.
// Located at Learning_004.c in CLion Project: DS_Learning.
//

//单链表的两种创建方式：前插法和尾插法

#include "stdio.h"
#include "stdlib.h"

typedef struct LNode {
    int a;
    struct LNode *next;
} LNode, ListLink;

ListLink *CreateList_H(int n);//头插法
ListLink *CreateList_R(int n);//尾插法
void PrintList(const ListLink *L);//打印链表的所以元素

int main() {
    printf("Create list by 1.head or 2.return\n");
    int choose;
    int n;
    ListLink *L;
    scanf("%d", &choose);
    switch (choose) {
        case 1:
            printf("Please input the quantity of list\n");
            scanf("%d", &n);
            L = CreateList_H(n);
            PrintList(L);
            break;
        case 2:
            printf("Please input the quantity of list\n");
            scanf("%d", &n);
            L = CreateList_R(n);
            PrintList(L);
            break;
    }
    return 0;
}

//头插法
ListLink *CreateList_H(int n) {
    ListLink *L = (ListLink *) malloc(sizeof(LNode));
    L->next = NULL;
    for (int i = 0; i < n; ++i) {
        printf("input number %d\n", i + 1);
        LNode *p = (LNode *) malloc(sizeof(LNode));
        scanf("%d", &(p->a));
        p->next = L->next;
        L->next = p;
    }
    return L;
}

//尾插法
ListLink *CreateList_R(int n) {
    ListLink *L = (ListLink *) malloc(sizeof(LNode));
    L->next = NULL;
    LNode *pt = L;
    for (int i = 0; i < n; ++i) {
        printf("input number %d\n", i + 1);
        LNode *p = (LNode *) malloc(sizeof(LNode));
        //将新创建的p指针域制空，防止指针乱指
        p->next = NULL;
        scanf("%d", &(p->a));
        pt->next = p;
        pt = pt->next;
    }
    return L;
}

//打印链表的所以元素
void PrintList(const ListLink *L) {
    if (!L) {
        printf("List is not exist\n");
    } else if (!(L->next)) {
        printf("List is empty\n");
    } else {
        printf("The list:\n");
        LNode *p = L->next;
        while (p) {
            printf("%d\n", p->a);
            p = p->next;
        }
    }
}