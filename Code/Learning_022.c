//
// Created by Duyou on 2022/5/3.
// Located at Learning_022.c in CLion Project: DS_Learning.
//

//查找算法

#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int *key;       //存储空间基地址，0号地址不用
    int length;     //表长度
} SSTable;

SSTable *CreateSSTable();

int Search_Seq(SSTable *S, int key, int dir);  //顺序查找，返回查找的下标值，未找到返回0，dir为查找方向1为正，0为逆
int Search_Bin(SSTable *S, int key);           //二分查找，查找成功返回值下标，否则返回0
void Menu();


int main() {
    SSTable *S = CreateSSTable();
    int key;
    int dir;
    int choose;
    Menu();
    scanf("%d", &choose);
    switch (choose) {
        case 1:
            printf("Input key:\n");
            scanf("%d", &key);
            printf("Input dir:\n");
            scanf("%d", &dir);
            printf("Result: %d\n", Search_Seq(S, key, dir));
            break;
        case 2:
            printf("Input key:\n");
            scanf("%d", &key);
            printf("Result: %d\n", Search_Bin(S, key));
            break;
        default:
            printf("Error.\n");
            break;
    }
    return 0;
}

void Menu() {
    printf("====================Search====================\n");
    printf("1. Sequential search\n");
    printf("2. binary search\n");
}

SSTable *CreateSSTable() {
    SSTable *ST = (SSTable *) malloc(sizeof(SSTable));
    printf("Create table:\n");
    printf("Input the quantity:\n");
    scanf("%d", &(ST->length));
    ST->key = (int *) malloc(sizeof(int) * (ST->length + 1));
    for (int i = 1; i < ST->length + 1; ++i) {
        printf("Number %d:\n", i);
        scanf("%d", &(ST->key[i]));
    }
    return ST;
}

//顺序查找，返回查找的下标值，未找到返回0，dir为查找方向1为正，0为逆
int Search_Seq(SSTable *S, int key, int dir) {
    if (!S) {
        return -1;
    }
    if (dir) {
        for (int i = 1; i < S->length + 1; ++i) {
            if (S->key[i] == key) {
                return i;
            }
        }
        return 0;
    } else {
        //令0号位置为要查找的key值，这样不需要判断边界，当查找到边界时key值相等。
        S->key[0] = key;
        int i;
        for (i = S->length; S->key[i] != key; --i) {
            //不进行任何判断，当key值相等，要么查找成功，i为下标值；要么查找失败，i为0
        }
        return i;
    }
}

//二分查找，查找成功返回值下标，否则返回0
int Search_Bin(SSTable *S, int key) {
    if (!S) {
        return -1;
    }
    int low = 1;
    int high = S->length;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (key == S->key[mid]) {
            return mid;
        } else if (key < S->key[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return 0;
}
