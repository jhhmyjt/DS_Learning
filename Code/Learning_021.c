//
// Created by Duyou on 2022/5/2.
// Located at Learning_021.c in CLion Project: DS_Learning.
//
//图的邻接表实现

#include "stdio.h"
#include "stdlib.h"

typedef struct ArcNode {
    int adjvex;     //该顶点的位置
    int weigth;     //边的权值
    struct ArcNode *nextArc;    //下一个邻接顶点
} ArcNode;

typedef struct VNode {
    int data;       //顶点数值
    ArcNode *firstArc;//指向当前顶点边表的第一个结点
} VNode, AdjList;

typedef struct {
    AdjList *adjList;   //顶点表的头指针，顶点表使用不定长的顺序表存储结构
    int vexNum;         //当前顶点数
    int arcNum;         //当前边数
} ALGraph;

void CreateUDG(ALGraph *G);

void ShowUDG(const ALGraph *G);

int main() {
    ALGraph G;
    CreateUDG(&G);
    ShowUDG(&G);
    return 0;
}

void CreateUDG(ALGraph *G) {
    if (!G) {
        printf("error.\n");
        return;
    }
    printf("Input vexNum and arcNum:\n");
    scanf("%d", &G->vexNum);
    scanf("%d", &G->arcNum);
    //给顶点表申请空间
    G->adjList = (AdjList *) malloc(sizeof(VNode) * (G->vexNum));
    //给顶点赋值并初始化边表
    for (int i = 0; i < G->vexNum; ++i) {
        printf("Vex %d:\n", i + 1);
        scanf("%d", &(G->adjList[i].data));
        G->adjList[i].firstArc = NULL;
    }
    for (int i = 0; i < G->arcNum; ++i) {
        int a, b, w;    //邻接顶点下标
        printf("Index:\n");
        scanf("%d", &a);
        scanf("%d", &b);
        if (a >= G->vexNum || b >= G->vexNum) {
            printf("Index error.\n");
            return;
        }
        printf("Weigth:\n");
        scanf("%d", &w);
        //申请一个边结点插入到a顶点边表后
        ArcNode *p1 = (ArcNode *) malloc(sizeof(ArcNode));
        p1->weigth = w;
        p1->adjvex = b;
        p1->nextArc = G->adjList[a].firstArc;
        G->adjList[a].firstArc = p1;
        //申请一个新边结点插入到b顶点后
        ArcNode *p2 = (ArcNode *) malloc(sizeof(ArcNode));
        p2->weigth = w;
        p2->adjvex = a;
        p2->nextArc = G->adjList[b].firstArc;
        G->adjList[b].firstArc = p2;
    }
}

void ShowUDG(const ALGraph *G) {
    if (!G) {
        printf("Error.\n");
        return;
    }
    for (int i = 0; i < G->vexNum; ++i) {
        printf("Vex %d, Value: %d, Adjacency Vertex:\n", i + 1, G->adjList[i].data);
        ArcNode *p = G->adjList[i].firstArc;
        while (p) {
            printf("Vertex index:%d\tWeigth:%d\n", p->adjvex, p->weigth);
            p = p->nextArc;
        }
    }
}