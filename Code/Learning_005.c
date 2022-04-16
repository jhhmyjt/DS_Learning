//
// Created by Duyou on 2022/4/15.
// Located at Learning_005.c in CLion Project: DS_Learning.
//

//带尾指针循环链表的创建和合并

#include "stdlib.h"
#include "stdio.h"

typedef struct LNode {
    int a;
    struct LNode *next;
} LNode, ListLink;

ListLink *CreateList_R(int n);//尾插法创建链表
ListLink *ConnectList(ListLink *L1, ListLink *L2);//将两个循环链表合并，返回合并后的链表
void PrintList(const ListLink *L);//打印链表所以元素

int main() {
    int n;
    ListLink *L1;
    ListLink *L2;
    printf("Create the first list\n");
    printf("Input the quantity:\n");
    scanf("%d", &n);
    L1 = CreateList_R(n);
    PrintList(L1);
    printf("Create the second list\n");
    printf("Input the quantity:\n");
    scanf("%d", &n);
    L2 = CreateList_R(n);
    PrintList(L2);
    printf("Connect the two lists\n");
    PrintList(ConnectList(L1, L2));
    return 0;
}

//尾插法创建链表
ListLink *CreateList_R(int n) {
    //头结点
    LNode *L = (LNode *) malloc(sizeof(LNode));
    L->next = NULL;
    //返回的尾指针
    LNode *res = L;
    for (int i = 0; i < n; ++i) {
        LNode *p = (LNode *) malloc(sizeof(LNode));
        p->next = NULL;
        printf("Input number %d\n", i + 1);
        scanf("%d", &(p->a));
        res->next = p;
        res = p;
    }
    res->next = L;
    return res;
}

//将两个循环链表合并，L2接在L1之后，返回合并后的链表
ListLink *ConnectList(ListLink *L1, ListLink *L2) {
    //总体是将L2的头结点放在L1的尾指针之后

    //先要确保链接后循环不断，因此先将L2的尾指针指向L1的头结点
    //提前存储L2的第一个元素结点（L2尾指针指向其他地方后无法获得L2的头结点
    LNode *p = L2->next->next;
    //L2头部的空结点可以释放
    LNode *p2 = L2->next;
    free(p2);//只是释放了变量L2->next指向的头部空结点数据的内存，但变量还在，指针指向的内存空了。因为下面L2->next要指向新的内存，要提前释放原本指向的内存空间
    //将L2的尾部next指向L1的头部建立循环
    L2->next = L1->next;
    //将L1尾部的next指向之前存储的L2第一个元素建立合并的链表
    L1->next = p;
    return L2;
}

//打印链表所以元素
void PrintList(const ListLink *L) {
    if (!L) {
        printf("List is not exist\n");
    } else if (!(L->next)) {
        printf("List is empty\n");
    } else {
        printf("List:\n");
        LNode *p = L->next->next;
        //循环单链表的循环判断条件，根据头尾指针的区别而不同，这里是尾指针，因此是p（第一个元素）不为尾指针（最后一个元素）的next
        while (p != L->next) {
            printf("%d ", p->a);
            p = p->next;
        }
        printf("\n");
    }
}