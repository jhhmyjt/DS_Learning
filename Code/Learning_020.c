//
// Created by Duyou on 2022/5/2.
// Located at Learning_020.c in CLion Project: DS_Learning.
//
//图的邻接矩阵实现

#include "stdio.h"
#include "stdlib.h"

#define MaxInt 32767    //极大值，∞
typedef int VerType;   //顶点的数据类型
typedef int ArcType;    //边的权值类型

typedef struct {
    VerType *vex;   //存储顶点信息的一维数组（如使用字符类型则要用数组形式）
    ArcType **arc;  //存储边的二维数组
    int vexNum;     //图的当前结点数
    int arcNum;     //图的当前边数
} AMGraph;

void CreateUDN(AMGraph *AMG, int vexNum, int arcNum);

void ShowUDN(AMGraph *AMG, int vexNum);

int main() {
    AMGraph AMG = {
            NULL,
            NULL,
            0,
            0
    };
    int vexNum;
    int arcNum;
    printf("Input vexNum:\n");
    scanf("%d", &vexNum);
    printf("Input arcNum:\n");
    scanf("%d", &arcNum);
    CreateUDN(&AMG, vexNum, arcNum);
    ShowUDN(&AMG, vexNum);
    return 0;
}

void CreateUDN(AMGraph *AMG, int vexNum, int arcNum) {
    if (!AMG) {
        printf("AMG is null.\n");
        return;
    }
    //输入顶点数和边数
    AMG->vexNum = vexNum;
    AMG->arcNum = arcNum;
    //给顶点数组赋值
    AMG->vex = (VerType *) malloc(sizeof(VerType) * (AMG->vexNum));
    int i, j;
    for (i = 0; i < AMG->vexNum; ++i) {
        printf("Vex %d:\n", i + 1);
        scanf("%d", AMG->vex + i);
    }
    //初始化邻接矩阵
    AMG->arc = (ArcType **) malloc(sizeof(ArcType *) * (AMG->vexNum));
    for (i = 0; i < AMG->vexNum; ++i) {
        AMG->arc[i] = (ArcType *) malloc(sizeof(ArcType) * (AMG->vexNum));
        for (j = 0; j < AMG->vexNum; ++j) {
            AMG->arc[i][j] = MaxInt;
        }
    }
    for (int k = 0; k < AMG->vexNum; ++k) {
        printf("%d ", AMG->vex[k]);
    }
    printf("\n");
    //构建邻接矩阵
    for (int k = 0; k < AMG->arcNum; ++k) {
        int a, b;    //边依附的两个顶点在顶点数组的下标
        printf("Index:\n");
        scanf("%d", &a);
        scanf("%d", &b);
        if (a + 1 > AMG->vexNum || b + 1 > AMG->vexNum) {
            printf("Index error.\n");
            return;
        }
        //输入边的权值
        printf("Weight:\n");
        scanf("%d", &(AMG->arc[a][b]));
        //对于无向图，给其对称位置赋值
        AMG->arc[b][a] = AMG->arc[a][b];
    }
}

void ShowUDN(AMGraph *AMG, int vexNum) {
    for (int i = 0; i < vexNum; ++i) {
        printf("%d ", AMG->vex[i]);
    }
    printf("\n");
    for (int i = 0; i < vexNum; ++i) {
        for (int j = 0; j < vexNum; ++j) {
            printf("%d\t", AMG->arc[i][j]);
        }
        printf("\n");
    }
}