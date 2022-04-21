//
// Created by Duyou on 2022/4/20.
// Located at Learning_016.c in CLion Project: DS_Learning.
//

//栈的应用-表达式求值
//注：不包含表达式正确性验证，假设用户输入是正确的
//该程序只完成了逻辑主体，数据输入和处理未完成

#include "stdio.h"
#include "stdlib.h"

#define charToNumber(x) (x-'0')
#define numberToChar(x) (x+'0')

typedef struct StackNode{
    char c;
    struct StackNode*next;
}StackNode,LinkStack;

LinkStack *Init();

LinkStack *Push(LinkStack *S, char c);

LinkStack *Pop(LinkStack *S);

char GetTop(const LinkStack *S);

int IsNumber(char c);

int IsOperator(char c);

int JudgePriority(char c1,char c2);//判断栈顶c1和新操作符c2的优先级

int Operator(int a,int b,char c);//二元运算

void Calculator();

int main(){
//    char a[20];
//    printf("Input:\n");
//    scanf("%s",&a);
//    printf("Result: %d\n", Calculator(a));
    int n=10;
    printf("%c", numberToChar(n));
    return 0;
}

LinkStack *Init(){
    LinkStack *S=NULL;
    return S;
}

LinkStack *Push(LinkStack *S, char c){
    StackNode *p=(StackNode*) malloc(sizeof (StackNode));
    if(!p){
        return NULL;
    } else{
        p->c=c;
        p->next=S;
        S=p;
        return S;
    }
}

LinkStack *Pop(LinkStack *S){
    if(!S){
        return NULL;
    } else{
        StackNode *p=S;
        S=S->next;
        free(p);
        return S;
    }
}

char GetTop(const LinkStack *S){
    return S->c;
}

int IsNumber(char c){
    if(c>='0'&&c<='9'){
        return 1;
    } else{
        return 0;
    }
}

int IsOperator(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'){
        return 1;
    } else{
        return 0;
    }
}

//判断栈顶c1和新操作符c2的优先级，c1优先级大返回1，表示c1可出栈，c1和c2优先级相等，返回-1
int JudgePriority(char c1,char c2){
    if(c1=='+'||c1=='-'){
        if(c2=='+'||c2=='-'||c2==')'){
            return 1;
        }else{
            return 0;
        }
    }else if(c1=='*'||c1=='/'){
        if(c2=='('){
            return 0;
        } else{
            return 1;
        }
    } else if(c1=='('){
        if(c2==')'){
            return -1;
        } else{
            return 0;
        }
    }
    return 0;
}

//二元运算
int Operator(int a,int b,char c){
    if(c=='+'){
        return a+b;
    } else if(c=='-'){
        return a-b;
    } else if(c=='*'){
        return a*b;
    } else if(c=='/'){
        if(b==0){
            return 0;
        } else{
            return a/b;
        }
    }
    return 0;
}

//算术表达式计算
void Calculator(){
    LinkStack *OperandStack;
    LinkStack *OperatorStack;
    OperandStack=Init();
    OperatorStack=Init();
    while (*p!='\0'){
        if(IsNumber(*p)){
            OperandStack= Push(OperandStack,*p);
            p++;
        } else if(IsOperator(*p)){
            //先对操作数栈为空进行操作
            if(!OperatorStack){
                //
                OperatorStack= Push(OperatorStack,*p);
                p++;
            } else{
                if(JudgePriority(GetTop(OperatorStack),*p)==1){
                    //返回1，则栈顶操作符优先级高，出栈
                    //进行二元运算
                    int n1= charToNumber(GetTop(OperandStack));
                    OperandStack= Pop(OperandStack);
                    int n2= charToNumber(GetTop(OperandStack));
                    OperandStack= Pop(OperandStack);
                    OperandStack= Push(OperandStack, numberToChar(Operator(n1,n2,*p)));
                    OperatorStack= Pop(OperatorStack);
                    p++;
                } else if(JudgePriority(GetTop(OperatorStack),*p)==0){
                    //返回0，则栈顶优先级低，操作符入栈
                    OperatorStack= Push(OperatorStack,*p);
                    p++;
                } else if(JudgePriority(GetTop(OperatorStack),*p)==-1){
                    //()匹配
                    OperatorStack= Pop(OperatorStack);
                    p++;
                }
            }
        }
    }
    return charToNumber(GetTop(OperandStack));
}
