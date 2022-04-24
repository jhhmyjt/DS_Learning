//
// Created by Duyou on 2022/4/21.
// Located at Learning_018.c in CLion Project: DS_Learning.
//


#include "stdio.h"
#include "stdlib.h"

typedef struct BiTNode {
    char a;
    struct BiTNode *lChild;
    struct BiTNode *rChild;
} BiTNode, BiTree;

BiTree *InitBiTree();   //初始化二叉树
void PreBuildBiTree(BiTree **B);  //先序构建二叉树
void InOrderTraverse(const BiTree *B);//中序遍历
void PreOrderTraverse(const BiTree *B);//先序遍历
void PostOrderTraverse(const BiTree *B);//后序遍历

int main() {
    BiTree *B;
    B = InitBiTree();
    printf("Build BiTree:\n");
    PreBuildBiTree(&B);
    printf("Traverse BiTree:\n");
    PreOrderTraverse(B);
    return 0;
}

//中序遍历
void InOrderTraverse(const BiTree *B) {
    //使用二叉树的递归定义对其进行遍历
    //中序遍历，先遍历左子，再访问根，最后遍历右子
    if (B) {//当前结点非空
        //先遍历左子
        InOrderTraverse(B->lChild);//从当前结点左子进入下一层遍历
        //遍历根，对其进行操作
        printf("%c ", B->a);
        //遍历右子
        InOrderTraverse(B->rChild);//从当前结点右子进入下一层遍历
    }
}

//先序遍历
void PreOrderTraverse(const BiTree *B) {
    if (B) {
        printf("%c ", B->a);
        PreOrderTraverse(B->lChild);
        PreOrderTraverse(B->rChild);
    }
}

//后序遍历
void PostOrderTraverse(const BiTree *B) {
    if (B) {
        PostOrderTraverse(B->lChild);
        PostOrderTraverse(B->rChild);
        printf("%c ", B->a);
    }
}

//初始化二叉树
BiTree *InitBiTree() {
    //创建一个空二叉树
    BiTree *B = NULL;
    printf("Init done.\n");
    return B;
}

//先序构建二叉树
//这里使用二级指针以修改指针变量
//比如用先序构建一个1，2，3这样的二层满二叉树需要依次输入: 1,2,#.#.3,#,#
//大致过程：先赋值1给根，后从左进入下一层递归，先赋值2给第二层左根，再从第二层左进入下一递归，输入#，赋值结点为NULL退出该层递归回到第二层，再
//从第二层右边进入下一递归，输入为#，赋值NULL退出递归回到第二层。此时第二层递归结束回到第一层，从第一层右边进入递归，先赋值3给根，再从
//左边进入下一层，输入#，赋值NULL退出递归到第二层，从第二层右边进入下一层递归，输入#，赋值NULL退出递归到第二层。第二层递归完成退出到第一层
//第一层递归也完成，退出结束所有递归。
void PreBuildBiTree(BiTree **B) {
    char ch;
    scanf("%c", &ch);
    getchar();//清空IO缓冲区中的\n
    if (ch == '#') {//#代表该结点为空
        B = NULL;
        printf("add empty node.\n");
    } else {
        //B不为空，则按照根，左，右的顺序构建二叉树
        *B = (BiTNode *) malloc(sizeof(BiTNode));
        (*B)->a = ch;
        (*B)->rChild = NULL;
        (*B)->lChild = NULL;
        printf("Add %c\n", (*B)->a);
        PreBuildBiTree(&((*B)->lChild));
        PreBuildBiTree(&((*B)->rChild));
    }
}