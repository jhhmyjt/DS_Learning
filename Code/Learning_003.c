//
// Created by Duyou on 2022/4/14.
// Located at Learning_003.c in CLion Project: DS_Learning.
//

#include "stdio.h"
#include "stdlib.h"

//数据元素存储结构
typedef struct Book {
    char no[20];
    char name[20];
    double price;
} Book;

//创建单链表存储结构
typedef struct LNode {
    Book book;          //数据域
    struct LNode *next; //指针域
} LNode, LinkList;       //定义两个名称，LNode*定义指向任意结点的指针变量，LinkList定义单链表的头指针，其数据域为空

//单链表的基本操作
LinkList *InitList();//初始化单链表
Book *GetElem(LinkList *L, int i);//从单链表中取值
void Insert(LinkList *L, int i, const Book *book);//插入元素
void Delete(LinkList *L, int i);//删除元素
void PrintList(LinkList *L);//打印单链表所用元素
LinkList *Destroy(LinkList *L); //销毁链表


int main() {
    LinkList *L = InitList();
    if (!L) {
        printf("InitList failure\n");
        exit(-1);
    }
    Book book1 = {"10001", "book_01", 3.15};
    Book book2 = {"10002", "book_02", 5.15};
    Book book3 = {"10003", "book_03", 7.15};
    Insert(L, 1, &book1);
    Book *pb = GetElem(L, 1);
    printf("No.%s name is %s, price is %.2lf\n", pb->no, pb->name, pb->price);
    Insert(L, 2, &book2);
    PrintList(L);
    Insert(L, 1, &book3);
    PrintList(L);
    Delete(L, 2);
    PrintList(L);
    L = Destroy(L);
    PrintList(L);
    return 0;
}

//初始化单链表
LinkList *InitList() {
    LinkList *p = (LNode *) malloc(sizeof(LNode));
    if (p) {
        p->next = NULL;
        return p;
    } else {
        return NULL;
    }
}

//从单链表中取值
Book *GetElem(LinkList *L, int i) {
    LNode *p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        return NULL;
    }
    return &(p->book);
}

//插入元素
void Insert(LinkList *L, int i, const Book *book) {
    LNode *p = L;
    //查找到第i-1个元素
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) {
        printf("Error\n");
    } else {
        LNode *s = (LNode *) malloc(sizeof(LNode));
        s->book = *book;
        s->next = p->next;
        p->next = s;
        printf("Insert book_%s at %d\n", book->no, i);
    }
}

//删除元素
void Delete(LinkList *L, int i) {
    LNode *p = L;
    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1) {
        printf("Error\n");
    } else {
        LNode *n = p->next;
        p->next = n->next;
        free(n);
        printf("Delete book at %d.\n", j + 1);
    }
}

//打印单链表所用元素
void PrintList(LinkList *L) {
    if (!L) {
        printf("List is empty\n");
    } else {
        LNode *p = L->next;
        while (p) {
            printf("Book_%s,name: %s price: %.2lf\n", p->book.no, p->book.name, p->book.price);
            p = p->next;
        }
    }
}

LinkList *Destroy(LinkList *L) {
    LNode *p = NULL;
    while (L) {
        p = L;
        L = L->next;
        free(p);
    }
    return L;
}