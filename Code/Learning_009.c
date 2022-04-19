//
// Created by Duyou on 2022/4/16.
// Located at Learning_009.c in CLion Project: DS_Learning.
//

//稀疏多项式的运算
//使用链式结构存储，方便插入、删除操作
//多项式相加的运算规则：指数相同的项，系数相加，若其和不为0，作为和多项式的一项插入；对于指数不相同的，将较小的一项插入和多项式
//注意：该多项式必须是升序的形式

#include "stdio.h"
#include "stdlib.h"

typedef struct PNode {
    int exp;    //指数
    float coe;  //系数
    struct PNode *next;
} PNode, Polynomial;

Polynomial *CreatePolynomial(int n);//创建一个n项的多项式
Polynomial *AddPolynomial(Polynomial *Pol1, Polynomial *Pol2);//两个多项式相加
void PrintPolynomial(const Polynomial *Pol);

int main() {
    int n;
    Polynomial *Pol1;
    Polynomial *Pol2;
    printf("Create polynomial 1.\n");
    scanf("%d", &n);
    Pol1 = CreatePolynomial(n);
    PrintPolynomial(Pol1);
    printf("Create polynomial 2.\n");
    scanf("%d", &n);
    Pol2 = CreatePolynomial(n);
    PrintPolynomial(Pol2);
    printf("Add.\n");
    PrintPolynomial(AddPolynomial(Pol1, Pol2));
    return 0;
}

//创建一个n项的多项式
Polynomial *CreatePolynomial(int n) {
    Polynomial *Pol = (Polynomial *) malloc(sizeof(PNode));
    if (!Pol) {
        printf("Create failure.\n");
        return NULL;
    } else {
        Pol->next = NULL;
        printf("Create polynomial.\n");
        PNode *pc = Pol;
        for (int i = 0; i < n; ++i) {
            PNode *p = (PNode *) malloc(sizeof(PNode));
            if (!p) {
                printf("Add failure\n");
            } else {
                printf("The number %d, input the exponent and coefficient:\n", i + 1);
                scanf("%d %f", &(p->exp), &(p->coe));
                p->next = NULL;
                pc->next = p;
                pc = p;
            }
        }
        return Pol;
    }
}

//两个多项式相加
Polynomial *AddPolynomial(Polynomial *Pol1, Polynomial *Pol2) {
    if (!Pol1 || !Pol2) {
        printf("Polynomial is not exist.\n");
        return NULL;
    } else if (!(Pol1->next) || !(Pol2->next)) {
        printf("Polynomial is empty.\n");
        return NULL;
    } else {
        Polynomial *Pol3 = Pol1;
        PNode *p1 = Pol1->next;
        PNode *p2 = Pol2->next;
        PNode *p3 = Pol3;
        while (p1 && p2) {
            if (p1->exp == p2->exp) {//指数相同，系数相加
                float sum = p1->coe + p2->coe;
                if (0 == sum) {//系数和为0，该项抵消，分别删除p1和p2的当前结点并向后移动
                    PNode *pt;
                    pt = p1;
                    p1 = p1->next;
                    free(pt);
                    pt = p2;
                    p2 = p2->next;
                    free(pt);
                } else {//系数不为0，将p1结点的系数变为和结果，接在p3之后，p1向后移动；p2结点删除并向后移动
                    PNode *pt;
                    p1->coe = sum;
                    p3->next = p1;
                    p1 = p1->next;
                    p3 = p3->next;
                    pt = p2;
                    p2 = p2->next;
                    free(pt);
                }
            } else if (p1->exp < p2->exp) {//p1指数小，将p1放在p3后，p1向后移动
                p3->next = p1;
                p3 = p3->next;
                p1 = p1->next;
            } else {                    //p2指数小，将p2放在p3后，p2向后移动
                p3->next = p2;
                p3 = p3->next;
                p2 = p2->next;
            }
        }
        //循环结束后，将非空的部分放在p3后
        if (p1) {
            p3->next = p1;
        } else {
            p3->next = p2;
        }
        //释放多余的结点
        free(Pol2);
        return Pol3;
    }
}

void PrintPolynomial(const Polynomial *Pol) {
    if (!Pol) {
        printf("Polynomial is not exist.\n");
    } else if (!(Pol->next)) {
        printf("Polynomial is empty.\n");
    } else {
        printf("Polynomial:\n");
        PNode *p = Pol->next;
        while (p) {
            printf("%.2fX^%d ", p->coe, p->exp);
            p = p->next;
        }
        printf("\n");
    }
}