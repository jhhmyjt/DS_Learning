//
// Created by Duyou on 2022/4/27.
// Located at Learning_019.c in CLion Project: DS_Learning.
//

//哈夫曼树实现及应用

#include "stdlib.h"
#include "stdio.h"

typedef struct {
    int weight;
    int parent;
    int lChild;
    int rChild;
} HTNode, HTree;

void CreateHuffmanTree(HTree **HT, int n);//构建哈夫曼树
void Traverse(const HTree *HT, int n);    //遍历所有叶子结点

int main() {
    HTree *HT = NULL;
    int n;
    printf("Input n:\n");
    scanf("%d", &n);
    printf("Create Huffman Tree.\n");
    CreateHuffmanTree(&HT, n);
    Traverse(HT, n);
    return 0;
}

//构建哈夫曼树
void CreateHuffmanTree(HTree **HT, int n) {
    //初始化：申请内存空间、初始化数值、获取各结点权值
    if (n < 1) {
        printf("Error, n<1\n");
        return;
    }
    int nodeCount = 2 * n - 1;//结点个数
    *HT = (HTree *) malloc(sizeof(HTNode) * (nodeCount + 1));
    //将各结点数值初始为0
    for (int i = 1; i < nodeCount + 1; ++i) {
        (*HT + i)->parent = 0;
        (*HT + i)->lChild = 0;
        (*HT + i)->rChild = 0;
    }
    //为结点赋予权值
    printf("Input weigth.\n");
    //输入前n个结点的叶子的权值
    for (int i = 1; i < n + 1; ++i) {
        printf("Node %d weigth:\n", i);
        scanf("%d", &((*HT + i)->weight));
    }
    //构建哈夫曼树
    //在1和i-1之间进行选择，选择权值最低的结点作为第i个结点的左右孩子
    for (int i = n + 1; i < nodeCount + 1; ++i) {
        int n1, n2;
        for (int j = 1; j < i; ++j) {
            if ((*HT + j)->parent == 0) {
                n1 = j;
                break;
            }
        }
        for (int j = 1; j < i; ++j) {
            if ((*HT + j)->parent == 0 && j != n1) {
                n2 = j;
                break;
            }
        }
        for (int j = 1; j < i; ++j) {
            if ((*HT + j)->parent != 0) {
                continue;
            }
            if ((*HT + j)->weight < (*HT + n1)->weight) {
                n1 = j;
            }
        }
        for (int j = 1; j < i; ++j) {
            if ((*HT + j)->parent != 0 || j == n1) {
                continue;
            }
            if ((*HT + j)->weight < (*HT + n2)->weight) {
                n2 = j;
            }
        }
        //将n1，n2结点作为i结点的左右孩子
        (*HT + n1)->parent = i;
        (*HT + n2)->parent = i;
        //修改i结点的孩子和权值
        (*HT + i)->lChild = n1;
        (*HT + i)->rChild = n2;
        (*HT + i)->weight = (*HT + n1)->weight + (*HT + n2)->weight;
    }
}

void Traverse(const HTree *HT, int n) {
    if (!HT) {
        printf("Empty.\n");
        return;
    }
    printf("Traverse:\n");
    for (int i = 1; i < 2 * n; ++i) {
        printf("Node %d, Value: %d\n", i, (HT + i)->weight);
    }
}