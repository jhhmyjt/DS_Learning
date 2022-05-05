//
// Created by Duyou on 2022/5/4.
// Located at Learning_023.c in CLion Project: DS_Learning.
//

//二叉排序树

#include "stdlib.h"
#include "stdio.h"

typedef struct BSTNode {
    int a;  //结点元素
    struct BSTNode *lChild;
    struct BSTNode *rChild;
} BSTNode, BSTree;

BSTree *CreateBST();

void InsertBST(BSTree **T, int a);

BSTNode *SearchBST(BSTree *T, int a);

BSTNode *SearchBSTParent(BSTree *T, int a, BSTree *TP);

BSTNode *SearchBSTMAX(BSTree *T);    //查找该树的最大结点

void DeleteBST(BSTree **T, int a); //不增加深度删除二叉树中的结点

void TraverseBST(BSTree *T); //中序遍历二叉树

int main() {
    BSTree *T = CreateBST();
    TraverseBST(T);
    printf("\n");
    printf("Search:(-1 return)\n");
    int key = 0;
    while (-1 != key) {
        //输入-1结束查询，值为-1表示未找到
        scanf("%d", &key);
        printf("Result: %d\n", SearchBST(T, key) != NULL ? SearchBST(T, key)->a : -1);
    }
    while (1) {
        printf("Delete:\n");
        scanf("%d", &key);
        if (-1 == key || (!T)) {
            break;
        }
        DeleteBST(&T, key);
        TraverseBST(T);
        printf("\n");
    }
    return 0;
}

BSTree *CreateBST() {
    BSTree *T = NULL;
    int a = 0;
    printf("Create BST(-1 to end):\n");
    while (1) {
        printf("Insert:\n");
        scanf("%d", &a);
        //设置-1为结束标识
        if (-1 == a) {
            break;
        }
        InsertBST(&T, a);
    }
    return T;
}

void InsertBST(BSTree **T, int a) {
    if (!*T) {
        //树为空，创建一个新结点作为根结点插入空树
        BSTNode *p = (BSTNode *) malloc(sizeof(BSTNode));
        p->lChild = NULL;
        p->rChild = NULL;
        p->a = a;
        *T = p;
    } else if (a < (*T)->a) {
        //小，插入左子树
        InsertBST(&((*T)->lChild), a);
    } else if (a > (*T)->a) {
        //大，插入右子树
        InsertBST(&((*T)->rChild), a);
    }
    //相等则不插入
}

BSTNode *SearchBST(BSTree *T, int a) {
    //寻找，左小右大
    if (!T) {
        //树为空
        return NULL;
    }
    if (a < T->a) {
        //小，查找左子树
        return SearchBST(T->lChild, a);
    } else if (a > T->a) {
        //大，查找右子树
        return SearchBST(T->rChild, a);
    } else {
        //相等，查找成功
        return T;
    }
}

//查找a的双亲结点
BSTNode *SearchBSTParent(BSTree *T, int a, BSTree *TP) {
    //寻找，左小右大
    if (!T) {
        //树为空
        return NULL;
    }
    if (a < T->a) {
        //小，查找左子树
        return SearchBSTParent(T->lChild, a, T);
    } else if (a > T->a) {
        //大，查找右子树
        return SearchBSTParent(T->rChild, a, T);
    } else {
        //相等，查找成功
        return TP;
    }
}

//查找该树的最大结点
BSTNode *SearchBSTMAX(BSTree *T) {
    if (!T) {
        return NULL;
    }
    if (T->rChild) {
        //有右子树，继续查找
        return SearchBSTMAX(T->rChild);
    } else {
        //没有右子树了，该结点最大
        return T;
    }
}

void DeleteBST(BSTree **T, int a) {
    //先查找二叉树中是否有这个结点
    BSTNode *p = SearchBST(*T, a);
    if (!p) {
        //未找到
        printf("Not found.\n");
        return;
    }
    //f为该结点的双亲结点
    BSTNode *f = SearchBSTParent(*T, a, NULL);
    if (!f) {
        //f为空，该结点是树根结点
        if ((!p->lChild) && (!p->rChild)) {
            //该结点没有左右孩子，是树最后一个结点
            *T = NULL;
        } else if ((!p->lChild) && p->rChild) {
            *T = (*T)->rChild;
        } else if ((!p->rChild) && p->lChild) {
            *T = (*T)->lChild;
        } else {
            //该结点有左右孩子结点
            //先找到被删结点左子树中最大的
            BSTNode *pMax = SearchBSTMAX(p->lChild);
            //有两种情况，最大的就是被删结点的左子树，或者是右子树中最大的
            if (p->lChild == pMax) {
                //左子树中最大的是被删结点的左孩子，以左孩子为根的树没有右孩子。
                //替换结点作为树根，结点的右孩子为被删结点的右孩子
                *T = pMax;
                (*T)->rChild = p->rChild;
            } else {
                //左子树中最大的不是被删结点的左孩子。是左孩子为根的树的右树中
                //获取替换结点的双亲结点（该替换结点的左孩子要放在双亲结点上）
                BSTNode *pMaxParent = SearchBSTParent(p->lChild, pMax->a, NULL);
                pMaxParent->rChild = pMax->lChild;
                pMax->lChild = p->lChild;
                pMax->rChild = p->rChild;
                *T = pMax;
            }
        }
        free(p);
        return;
    }
    if ((!p->lChild) && (!p->rChild)) {
        //该结点没有左右孩子
        if (f->lChild == p) {
            //该结点是双亲的左孩子
            f->lChild = NULL;
        } else {
            f->rChild = NULL;
        }
    } else if ((!p->lChild) && p->rChild) {
        //该结点只有右孩子
        if (f->lChild == p) {
            f->lChild = p->rChild;
        } else {
            f->rChild = p->rChild;
        }
    } else if ((!p->rChild) && p->lChild) {
        //该结点只有左孩子
        if (f->lChild == p) {
            f->lChild = p->lChild;
        } else {
            f->rChild = p->lChild;
        }
    } else {
        //该结点有左右孩子结点
        //先找到被删结点左子树中最大的
        BSTNode *pMax = SearchBSTMAX(p->lChild);
        //有两种情况，最大的就是被删结点的左子树，或者是右子树中最大的
        if (p->lChild == pMax) {
            //左子树中最大的是被删结点的左孩子，以左孩子为根的树没有右孩子。
            //将被删结点的左孩子替换被删结点，被删结点的右孩子作为替换结点的右孩子
            if (f->lChild == p) {
                f->lChild = p->lChild;
            } else {
                f->rChild = p->lChild;
            }
            p->lChild->rChild = p->rChild;
        } else {
            //左子树中最大的不是被删结点的左孩子。是左孩子为根的树的右树中
            //获取替换结点的双亲结点（该替换结点的左孩子要放在双亲结点上）
            BSTNode *pMaxParent = SearchBSTParent(p->lChild, pMax->a, NULL);
            pMaxParent->rChild = pMax->lChild;
            pMax->lChild = p->lChild;
            pMax->rChild = p->rChild;
        }
    }
    free(p);
}

void TraverseBST(BSTree *T) {
    if (T) {
        TraverseBST(T->lChild);
        printf("%d ", T->a);
        TraverseBST(T->rChild);
    }
}