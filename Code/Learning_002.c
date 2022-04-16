//
// Created by Duyou on 2022/4/14.
//

#include<stdio.h>
#include<stdlib.h>

#define MaxSize 100

//定义图书信息结构
typedef struct Book {
    char no[20];
    char name[50];
    double price;
}Book;

//定义顺序表
typedef struct SqList {
    Book* elem;		//数组的首地址，数组使用动态分配
    int length;
}SqList;

void InitList(SqList* L);//顺序表的初始化
void DestroyList(const SqList* L);//顺序表销毁
void Insert(SqList* L, int i, const Book* b);//在第i个位置插入新元素
void Delete(SqList* L, int i);//删除第i位置元素
void PrintList(const SqList* L);	//打印顺序表所以元素
Book* GetElem(const SqList* L, int i);//获取序号为i的数


int main() {
    SqList list;
    Book book1 = { "1001","book_01",3.15 };
    Book book2 = { "1002","book_02",5.15 };
    Book book3 = { "1003","book_03",7.15 };
    InitList(&list);
    Insert(&list, 1, &book1);
    printf("Book no.%s, name is %s\n", GetElem(&list,1)->no,GetElem(&list,1)->name);
    Insert(&list, 2, &book2);
    PrintList(&list);
    Insert(&list, 1, &book3);
    PrintList(&list);
    Delete(&list, 1);
    PrintList(&list);
    DestroyList(&list);
    return 0;
}

//顺序表的初始化
void InitList(SqList* L) {
    L->elem = (Book*)malloc(sizeof(Book)*MaxSize);
    L->length = 0;
    printf("List initialization\n");
}

//顺序表销毁
void DestroyList(const SqList* L) {
    free(L->elem);
    printf("List destroy\n");
}

//在第i个位置插入新元素
void Insert(SqList* L, int i, const Book* b) {
    if (i<1 || i>L->length + 1) {
        printf("index error\n");
    }
    if (L->length == MaxSize) {
        printf("Length is max");
    }
    //移动元素
    for ( int j = L->length-1; j >=i-1; --j)
    {
        L->elem[j + 1] = L->elem[j];
    }
    //插入元素
    L->elem[i - 1] = *b;
    L->length++;
    printf("Insert book at %d\n", i);
}

//删除第i位置元素
void Delete(SqList* L, int i) {
    if (i<1 || i>L->length) {
        printf("index error\n");
    }
    //移动元素
    for (int j = i; j < L->length; ++j) {
        L->elem[j - 1] = L->elem[j];
    }
    L->length--;
    printf("Destroy book at %d\n", i);
}

//打印顺序表所以元素
void PrintList(const SqList* L) {
    for (int j = 0; j < L->length; j++)
    {
        printf("Book no.%s, name: %s, price: %.2lf\n", L->elem[j].no, L->elem[j].name, L->elem[j].price);
    }
}

//获取序号为i的数
Book* GetElem(const SqList* L, int i) {
    if (i<1 || i>L->length) {
        return NULL;
    }
    return L->elem + i-1;
}