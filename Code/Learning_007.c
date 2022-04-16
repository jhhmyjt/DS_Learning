//
// Created by Duyou on 2022/4/15.
// Located at Learning_007.c in CLion Project: DS_Learning.
//

//两个集合的并集问题
//方案：使用顺序结构。因为集合大小是固定的，并且没有排序的要求，不用修改元素

#include "stdio.h"
#include "stdlib.h"

#define MaxSize 10

typedef struct SqList {
    int *elem; //集合元素首地址
    int length; //集合长度
} SqList;

void PrintList(const SqList *L);

SqList *CreateList(int a[], int n);

SqList *ConnectList(SqList *L1, SqList *L2);

int main() {
    int a[5] = {1, 3, 4, 2, 5};
    int b[5] = {2, 7, 4, 1, 8};
    SqList *L1 = CreateList(a, 5);
    SqList *L2 = CreateList(b, 5);
    PrintList(L1);
    PrintList(L2);
    printf("Connect two lists.\n");
    PrintList(ConnectList(L1, L2));
    return 0;
}

void PrintList(const SqList *L) {
    printf("List:\n");
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", *(L->elem + i));
    }
    printf("\n");
}

SqList *CreateList(int a[], int n) {
    SqList *L = (int *) malloc(sizeof(int) * MaxSize);
    L->length = n;
    L->elem = a;
    return L;
}

SqList *ConnectList(SqList *L1, SqList *L2) {
    for (int i = 0; i < L2->length; ++i) {
        int flag = 0; //声明状态遍历
        for (int j = 0; j < L1->length; ++j) {
            if (*(L1->elem + j) == *(L2->elem + i)) {
                flag = 1;
                break;
            }
        }
        if (flag) {   //flag为1则L1中存在与L2相同的元素，该元素跳过
            continue;
        } else {     //flag为0则没有相同，将该元素插入L1中
            *((L1->elem) + (L1->length)) = *(L2->elem + i);
            L1->length++;
        }
    }
    return L1;
}