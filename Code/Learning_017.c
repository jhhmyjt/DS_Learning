//
// Created by Duyou on 2022/4/20.
// Located at Learning_017.c in CLion Project: DS_Learning.
//

//串的定长顺序存储结构

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAXSIZE 100

typedef struct {
    char *base;
    int length;
} HString;

HString Init();

void InsertStr(HString *S, char t[]);//在串的末尾插入字串
void PrintStr(const HString *S);

int Index_BF(HString *S, HString *T, int pos);
int Index_KMP(HString *S, HString *T, int pos);
int* GetNext(const HString*S);

int main() {
    HString S1;
    HString S2;
    char choose='\0';
    char ch[20]="";
    S1 = Init();
    S2 = Init();
    printf("Input a array to insert into S1:\n");
    scanf("%s", &ch);
    InsertStr(&S1, ch);
    PrintStr(&S1);
    printf("Input a array to insert into S2:\n");
    scanf("%s", &ch);
    InsertStr(&S2, ch);
    PrintStr(&S2);
    printf("Match S2 in S1. Choose the BF or KMP:(enter b or k to choose.) \n");
    scanf("%c",&choose);
    if(choose=='b'){
        printf("BF: S2's index in S1: %d\n", Index_BF(&S1, &S2, 0));
    } else if(choose=='k'){
//        printf("KMP: S2's index in S1: %d\n", Index_KMP(&S1, &S2, 1));
    } else{
        printf("Input error.\n");
    }
    return 0;
}

HString Init() {
    HString S;
    S.base = (char *) malloc(sizeof(char) * MAXSIZE);
    S.length = 0;
    printf("Init done.\n");
    return S;
}

//在串的末尾插入字串
void InsertStr(HString *S, char t[]) {
    if (strlen(t) + S->length >= MAXSIZE) {
        printf("Length over.\n");
    } else {
        char *pt = t;
        char *ps = S->base + S->length;
        while (*pt != '\0') {
            *ps = *pt;
            pt++;
            ps++;
            S->length++;
        }
        printf("Insert %s done.\n", t);
        char temp=getchar();
    }
}

void PrintStr(const HString *S) {
    for (int i = 0; i < S->length; ++i) {
        printf("%c", *(S->base + i));
    }
    printf("\n");
}

int Index_BF(HString *S, HString *T, int pos) {
    //BF匹配,返回t在s中从pos位置出发出现的第一个位置，不存在返回0
    int i = pos - 1;//i指针指向s串
    int j = 0;  //j指针指向t串
    while (i < S->length && j < T->length) {
        if (S->base[i] == T->base[j]) {
            //相同，指针后移
            i++;
            j++;
        } else {
            //匹配失败，匹配了j个元素，i回退到i-j+1
            i = i - j + 1;
            //j回到起点
            j = 0;
        }
    }
    if (j > T->length - 1) {
        return i - T->length + 1;
    } else {
        //匹配失败
        return 0;
    }
}
int Index_KMP(HString *S, HString *T, int pos){
    int i=pos;
    int j=1;    //此处i，j均是从1出发（和next数组匹配，next数组中0有特殊含义）
//    int *next= GetNext(T);
    int next[20];
    while (i<=S->length&&j<=T->length){
        if(j==0||S->base[i-1]==T->base[j-1]){
            //字符相等，继续匹配
            i++;
            j++;
        } else{
            //字符不相等，i不变，j跳过重复到next[j]
            j=next[j];
        }
    }
    if(j>T->length-1){
        return i-T->length;
    } else{
        return 0;
    }
}

int* GetNext(const HString*S){
    int *res=NULL;
    res=(int*) malloc(sizeof (int)*20);
    int i=1;//i为前缀指针
    int j=0;//j为后缀指针，指向后缀第一个元素
    res[0]=0;//第一位为0，第二位为0
    while (i<S->length){
        //i为前缀指针，从第一个元素开始到倒数第二个
        if(j==0||S->base[i]==S->base[j]){
            j++;
            i++;
            //元素相同指针向下一位，此时i指针指向的元素前面已经有j个元素重复了，赋值j给next数组
            res[i]=j;
        } else{
            j=res[j];
        }
    }
    return res;
}