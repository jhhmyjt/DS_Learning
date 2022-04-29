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

typedef struct StackNode {
    char c;
    struct StackNode *next;
} StackNode, LinkStack;

typedef char **HuffmanCode;//哈夫曼编码编码表

void PrintMain();

void CreateHuffmanTree(HTree **HT, int n);//构建哈夫曼树
void Traverse(const HTree *HT, int n);    //遍历所有叶子结点
int GetPathLength(const HTree *HT, int i);    //获取结点路径长度
int GetWPL(const HTree *HT, int n);           //获取WPL
HuffmanCode CreateHuffmanCode(HTree *HT, int n);

void ShowHuffmanCode(HuffmanCode HCode, int n);

//栈的相关操作
void Push(LinkStack **S, char c);

char Pop(LinkStack **S);

int GetStackLength(LinkStack *S);

int main() {
    HTree *HT = NULL;
    int n;
    int choose;
    HuffmanCode HCode = NULL;
    printf("Input n:\n");
    scanf("%d", &n);
    printf("Create Huffman Tree.\n");
    CreateHuffmanTree(&HT, n);
    Traverse(HT, n);
    PrintMain();
    scanf("%d", &choose);
    switch (choose) {
        case 1:
            printf("WPL = %d\n", GetWPL(HT, n));
            break;
        case 2:
            HCode = CreateHuffmanCode(HT, n);
            ShowHuffmanCode(HCode, n);
            break;
        default:
            printf("Unknown choose.\n");
    }
    return 0;
}

void PrintMain() {
    printf("===============Menu================\n");
    printf("1. Get WPL.\n");
    printf("2. Create Huffman code and show.\n");
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
    int n1 = 1, n2 = 2;
    for (int i = n + 1; i < nodeCount + 1; ++i) {
        //将n1赋值为一个没有双亲的结点（未构成二叉树）的位置
        for (int j = 1; j < i; ++j) {
            if ((*HT + j)->parent == 0 && j != n2) {
                n1 = j;
                break;
            }
        }
        //将n2赋值为一个没有双亲的结点（未构成二叉树）的位置
        for (int j = 1; j < i; ++j) {
            if ((*HT + j)->parent == 0 && j != n1) {
                n2 = j;
                break;
            }
        }
        //将n1位置结点权值和其他位置结点进行比较，保证其为权值最小的两个之一
        for (int j = 1; j < i; ++j) {
            //过滤已经构成二叉树的结点和另一个预选结点位置
            if ((*HT + j)->parent != 0 || j == n2) {
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
        printf("Node %d, weight: %d\n", i, (HT + i)->weight);
    }
}

//获取结点路径长度
int GetPathLength(const HTree *HT, int i) {
    int result = 0;
    int parent = (HT + i)->parent;
    while (parent != 0) {
        result++;
        parent = (HT + parent)->parent;
    }
    return result;
}

//获取WPL
int GetWPL(const HTree *HT, int n) {
    int result = 0;
    for (int i = 1; i < n + 1; ++i) {
        result += GetPathLength(HT, i) * (HT + i)->weight;
    }
    return result;
}

HuffmanCode CreateHuffmanCode(HTree *HT, int n) {
    //申请n+1个编码存储空间，第0位不用
    HuffmanCode HCode = (HuffmanCode) malloc(sizeof(HuffmanCode) * (n + 1));
    if (!HCode) {
        return NULL;
    }
    //求1~n叶子结点的编码值
    for (int i = 1; i < n + 1; ++i) {
        int parent = (HT + i)->parent;
        int index = i;
        LinkStack *S = NULL;
        Push(&S, '\0'); //给编码字符串末尾赋值
        while (parent != 0) {
            if ((HT + parent)->lChild == index) {
                Push(&S, '0');
            } else {
                Push(&S, '1');
            }
            index = (HT + index)->parent;
            parent = (HT + parent)->parent;
        }
        int len = GetStackLength(S);
        HCode[i] = (char *) malloc(sizeof(char *) * (len + 1));
        int j = 0;
        while (S != NULL) {
            HCode[i][j] = Pop(&S);
            j++;
        }
    }
    return HCode;
}

void ShowHuffmanCode(HuffmanCode HCode, int n) {
    for (int i = 1; i < n + 1; ++i) {
        printf("%s\n", HCode[i]);
    }
}

void Push(LinkStack **S, char c) {
    StackNode *p = (StackNode *) malloc(sizeof(StackNode));
    if (!p) {
        printf("error.\n");
        return;
    }
    p->c = c;
    p->next = *S;
    (*S) = p;
}

char Pop(LinkStack **S) {
    char result;
    StackNode *p = *S;
    (*S) = (*S)->next;
    result = p->c;
    free(p);
    return result;
}

int GetStackLength(LinkStack *S) {
    StackNode *p = S;
    int count = 0;
    while (p) {
        count++;
        p = p->next;
    }
    return count;
}