//
// Created by Duyou on 2022/4/14.
//

#include <stdio.h>
#include <assert.h>

typedef struct Complex {
    float realPart;
    float imagePart;
}Complex;

void Create(Complex* a, float real, float image);//复数构造函数
Complex Add(const Complex* a, const Complex* b);	//两复数相加，返回结果
Complex Sub(const Complex* a, const Complex* b);	//两复数相减，返回结果
float GetReal(const Complex* a);				//返回目标复数的实部
float GetImage(const Complex* a);				//返回目标复数的虚部

int main() {
    //定义复数变量
    Complex a;
    Complex b;
    //定义复数类型指针接受复数计算结果
    Complex res;
    //对复数初始化
    Create(&a, 3, 4);
    Create(&b, 6, 8);
    //获取复数的实部,虚部
    printf("Complex a: realpart is %.2f, imagepart is %.2f\n", a.realPart, a.imagePart);
    printf("Complex b: realpart is %.2f, imagepart is %.2f\n", GetReal(&b), GetImage(&b));
    //复数计算
    res = Add(&a, &b);
    printf("Result of complex a and complex b: real: %.2f, image: %.2f\n", GetReal(&res), GetImage(&res));
    res = Sub(&a, &b);
    printf("Result of complex a sub complex b: real: %.2f, image: %.2f\n", GetReal(&res), GetImage(&res));

    return 0;
}

//复数构造函数
void Create(Complex* a, float real, float image) {
    assert(a != NULL);
    a->imagePart = image;
    a->realPart = real;
}

//两复数相加，返回结果
Complex Add(const Complex* a, const Complex* b) {
    assert(a != NULL);
    assert(b != NULL);
    Complex res;
    Create(&res, GetReal(a) + GetReal(b), GetImage(a) + GetImage(b));
    return res;
}

//两复数相减，返回结果
Complex Sub(const Complex* a, const Complex* b) {
    assert(a != NULL);
    assert(b != NULL);
    Complex res;
    Create(&res, GetReal(a) - GetReal(b), GetImage(a) - GetImage(b));
    return res;
}

//返回目标复数的实部
float GetReal(const Complex* a) {
    assert(a != NULL);
    return a->realPart;
}

//返回目标复数的虚部
float GetImage(const Complex* a) {
    assert(a != NULL);
    return a->imagePart;
}