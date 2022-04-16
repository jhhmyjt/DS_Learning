//
// Created by Duyou on 2022/4/15.
// Located at Learning_008.c in CLion Project: DS_Learning.
//

//非递减有序列表的归并问题。
//建立一个空表，将A和B中的元素依次放入空表中。
//使用链式存储结构，因为链式存储可以不创建新的表结点空间

#include "stdlib.h"
#include "stdio.h"

typedef struct LNode {
    int a;
    struct LNode *next;
} LNode, LinkList;

LinkList *CreateList(int n);

void PrintList(const LinkList *L);

LinkList *ConnectList(LinkList *L1, LinkList *L2);

int main() {
    LinkList *L1;
    LinkList *L2;
    int n;
    printf("Create list 1:\n");
    scanf("%d", &n);
    L1 = CreateList(n);
    PrintList(L1);
    printf("Create list 2:\n");
    scanf("%d", &n);
    L2 = CreateList(n);
    PrintList(L2);
    printf("Connect two lists.\n");
    PrintList(ConnectList(L1, L2));
    return 0;
}

//尾插法创建链表
LinkList *CreateList(int n) {
    printf("Create list.\n");
    LinkList *L = (LinkList *) malloc(sizeof(LNode));
    L->next = NULL;
    LNode *pc = L;
    for (int i = 0; i < n; ++i) {
        LNode *p = (LNode *) malloc(sizeof(LNode));
        printf("The number %d:\n", i + 1);
        scanf("%d", &(p->a));
        p->next = NULL;
        pc->next = p;
        pc = p;
    }
    return L;
}

void PrintList(const LinkList *L) {
    if (!L) {
        printf("List is not exist\n");
    } else if (!(L->next)) {
        printf("List is empty\n");
    } else {
        printf("List:\n");
        LNode *p = L->next;
        while (p) {
            printf("%d ", p->a);
            p = p->next;
        }
        printf("\n");
    }
}

//合并两个有序表
LinkList *ConnectList(LinkList *L1, LinkList *L2) {
    if (!L1 || !L2) {
        printf("one of the lists is not exists\n");
        return NULL;
    } else if (!(L1->next) || !(L2->next)) {
        printf("one of the lists is empty\n");
        return NULL;
    } else {
        LNode *p1 = L1->next;
        LNode *p2 = L2->next;
        LinkList *L3 = L1;    //将返回结果p3值为L1头指针
        LNode *p3 = L3;
        //循环放入元素
        while (p1 && p2) {
            if (p1->a <= p2->a) {
                //p1中的数值较小，放入L3中
                p3->next = p1;    //p3指向放入的p1
                p3 = p1;          //p3移动到下一个
                p1 = p1->next;    //p1移动到下一个
            } else {
                p3->next = p2;
                p3 = p2;
                p2 = p2->next;
            }
        }
        //循环结束，如果还有非空列表，将其放在p3后面
        if (p1) {
            p3->next = p1;
        } else {
            p3->next = p2;
        }
        //因为将L1的头指针给了L3，L2可以释放
        free(L2);
        return L3;
    }
}