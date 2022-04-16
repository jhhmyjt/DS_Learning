//
// Created by Duyou on 2022/4/15.
// Located at Learning_006.c in CLion Project: DS_Learning.
//

//双向链表（不循环）的创建、插入已经删除

#include "stdio.h"
#include "stdlib.h"

typedef struct LNode {
    int a;
    struct LNode *next;
    struct LNode *prior;
} LNode, ListLink;

ListLink *CreateList(int n);//尾插法创建有n个元素的双向链表
void Insert(ListLink *L, int i, int a);//在第i个元素之前插入新元素
void Delete(ListLink *L, int i);      //删除第i个元素
void PrintList(const ListLink *L);         //打印链表中的所有元素

int main() {
    ListLink *L;
    int n;
    int i;
    int a;
    printf("Create list:\n");
    scanf("%d", &n);
    L = CreateList(n);
    PrintList(L);
    printf("Insert at: \n");
    scanf("%d", &i);
    printf("Number:\n");
    scanf("%d", &a);
    Insert(L, i, a);
    PrintList(L);
    printf("Delete at: \n");
    scanf("%d", &i);
    Delete(L, i);
    PrintList(L);
    return 0;
}

//尾插法创建有n个元素的双向链表
ListLink *CreateList(int n) {
    ListLink *L = (ListLink *) malloc(sizeof(LNode));
    L->next = NULL;
    L->prior = NULL;
    LNode *pc = L;
    for (int i = 0; i < n; ++i) {
        LNode *p = (LNode *) malloc(sizeof(LNode));
        printf("The number %d:\n", i + 1);
        scanf("%d", &(p->a));
        p->prior = pc;
        p->next = NULL;
        pc->next = p;
        pc = p;
    }
    return L;
}

//在第i个元素之前插入新元素
void Insert(ListLink *L, int i, int a) {
    LNode *p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        printf("error\n");
    } else {
        LNode *pn = (LNode *) malloc(sizeof(LNode));
        pn->a = a;
        pn->prior = p->prior;
        p->prior->next = pn;
        pn->next = p;
        p->prior = pn;
    }
}

//删除第i个元素
void Delete(ListLink *L, int i) {
    LNode *p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        printf("error\n");
    } else {
        p->prior->next = p->next;
        p->next->prior = p->prior;
        free(p);
    }
}

//打印链表中的所有元素
void PrintList(const ListLink *L) {
    LNode *p = L->next;
    while (p) {
        printf("%d ", p->a);
        p = p->next;
    }
    printf("\n");
}