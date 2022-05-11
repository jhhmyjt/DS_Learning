//
// Created by Duyou on 2022/5/9.
// Located at Learning_024.c in CLion Project: DS_Learning.
//

//排序算法

#include "stdio.h"
#include "stdlib.h"

typedef struct {
    int *key;   //数据数组首地址，其中0地址不存储数据，可作为哨兵使用
    int length; //顺序表长度
} SqList;

SqList *CreateList();

void TraverseList(const SqList *L);

void PrintMenu();

void MenuAction(int choose, SqList *L);

void InsertSort(SqList *L);

void BInsertSort(SqList *L);

void ShellSort(SqList *L);

void ShellInsert(SqList *L, int dt);

void BubbleSort(SqList *L);

void QuickSort(SqList *L);

void QSort(SqList *L, int low, int high); //递归排序函数

int Partition(SqList *L, int low, int high);    //将序列进行分组，形成一个初始排序二叉树，返回中轴位置

void SelectSort(SqList *L);

void HeadSort(SqList *L);

void HeadAdjust(SqList *L, int s, int m);  //调整s~m序列的堆

void CreateHeap(SqList *L);  //初建堆

void Merge(int *r, int *t, int low, int mid, int high); //将表r中low~mid和mid+1~high进行归并并将结果放在t中

void MSort(int *r, int *t, int low, int high);         //对r low~high进行归并排序并存放结果到t

void MergeSort(SqList *L);

int main() {
    SqList *L = NULL;
    int choose;
    char yes;
    int array[11] = {0, 49, 38, 65, 97, 76, 13, 27, 49, 55, 04};
    printf("Create new array?[y/n]\n");
    scanf("%c", &yes);
    if (yes == 'y' || yes == 'Y') {
        L = CreateList();
    } else {
        L = (SqList *) malloc(sizeof(SqList));
        L->key = array;
        L->length = 10;
    }
    PrintMenu();
    scanf("%d", &choose);
    MenuAction(choose, L);
    return 0;
}

void PrintMenu() {
    printf("=============Sort================\n");
    printf("1. Insert sort.\n");
    printf("2. Binary insert sort.\n");
    printf("3. Shell sort.\n");
    printf("============\n");
    printf("4. Bubble sort.\n");
    printf("5. Quick sort\n");
    printf("============\n");
    printf("6. Simple selection sort.\n");
    printf("7. Head sort.\n");
    printf("============\n");
    printf("8. Merge sort.\n");
}

void MenuAction(int choose, SqList *L) {
    printf("Before:\n");
    TraverseList(L);
    switch (choose) {
        case 1:
            InsertSort(L);
            printf("Use insertion sort.\n");
            break;
        case 2:
            BInsertSort(L);
            printf("Use binary insertion sort.\n");
            break;
        case 3:
            ShellSort(L);
            printf("Use Shell sort.\n");
            break;
        case 4:
            BubbleSort(L);
            printf("Use bubble sort.\n");
            break;
        case 5:
            QuickSort(L);
            printf("Use quick sort.\n");
            break;
        case 6:
            SelectSort(L);
            printf("use Selection sort.\n");
            break;
        case 7:
            HeadSort(L);
            printf("use heap sort.\n");
            break;
        case 8:
            MergeSort(L);
            printf("use merge sort.\n");
            break;
        default:
            printf("Error choose.\n");
            break;
    }
    printf("After:\n");
    TraverseList(L);
}

SqList *CreateList() {
    SqList *L = (SqList *) malloc(sizeof(SqList));
    printf("Input n:\n");
    scanf("%d", &(L->length));
    L->key = (int *) malloc(sizeof(int) * (L->length + 1));
    for (int i = 1; i < L->length + 1; ++i) {
        printf("Number %d:\n", i);
        scanf("%d", L->key + i);
    }
    return L;
}

void TraverseList(const SqList *L) {
    for (int i = 1; i < L->length + 1; ++i) {
        printf("%d ", *(L->key + i));
    }
    printf("\n");
}

void InsertSort(SqList *L) {
    //将1地址看作为第一个有序序列，从2地址开始循环n-1次，每次先判断该元素和前一元素大小，大则直接加入有序列表；反之要将该元素插入有序列表
    //插入时可以设置0地址为监视哨来判断数组边界，从后向前判断插入位置
    for (int i = 2; i <= L->length; ++i) {
        if (L->key[i] < L->key[i - 1]) {
            //该元素比前一元素小（前一元素是有序列表最后一位），将其插入
            //设置0地址
            L->key[0] = L->key[i];
            //i-1地址已经比较过了，直接后移
            L->key[i] = L->key[i - 1];
            //从i-2开始，比插入元素大的后移，直到插入
            int j;
            for (j = i - 2; L->key[0] < L->key[j]; --j) {
                L->key[j + 1] = L->key[j];
                //不需要判断数组边界，当到0地址时会自动结束循环
            }
            L->key[j + 1] = L->key[0];//在j+1处插入
            //如果插入元素是最小值，j会一直减到0
        }
    }
}

void BInsertSort(SqList *L) {
    //基本上和直接插入排序相同
    for (int i = 2; i <= L->length; ++i) {
        if (L->key[i] >= L->key[i - 1]) {
            //不操作依然有序，下一个
            continue;
        }
        //在1到i-1区间进行二分查找
        int low = 1;
        int high = i - 1;
        L->key[0] = L->key[i];
        while (low <= high) {
            int mid = (low + high) / 2;
            if (L->key[0] < L->key[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
                //不设置相等情况
                //最后low、high可以标记插入位置
            }
        }
        for (int j = i - 1; j >= high + 1; --j) {
            L->key[j + 1] = L->key[j];
        }
        L->key[high + 1] = L->key[0];
    }
}

void ShellSort(SqList *L) {
    int dt[3] = {5, 3, 1};//进行三趟排序，每趟dt为5、3、1
    for (int i = 0; i < 3; ++i) {
        ShellInsert(L, dt[i]);
    }
}

void ShellInsert(SqList *L, int dt) {
    //对L进行一趟增量为dt的希尔排序
    //从1+dt开始，1位置为初始有序序列，
    for (int i = 1 + dt; i <= L->length; ++i) {
        if (L->key[i] < L->key[i - dt]) {
            //将当前值和其同组（相差为dt）的上一值进行比较
            L->key[0] = L->key[i];    //0地址暂存插入值，无其他作用
            //对元素进行移动
            int j;
            //从该值的下一位开始进行移动，每次移动dt位
            for (j = i - dt; L->key[0] < L->key[j] && j > 0; j = j - dt) {
                L->key[j + dt] = L->key[j];
            }
            //在插入位置插入
            L->key[j + dt] = L->key[0];
        }
    }
}

void BubbleSort(SqList *L) {
    int flag = 1; //定义一个标记，记录是否发送交换
    for (int i = 1; i < L->length && flag; ++i) {
        flag = 0;
        for (int j = 1; j < L->length - i + 1; ++j) {
            if (L->key[j] > L->key[j + 1]) {
                //进行交换
                flag = 1;
                L->key[j] = L->key[j] ^ L->key[j + 1];
                L->key[j + 1] = L->key[j] ^ L->key[j + 1];
                L->key[j] = L->key[j] ^ L->key[j + 1];
            }
        }
    }
}

void QuickSort(SqList *L) {
    QSort(L, 1, L->length);
}

//递归排序函数
void QSort(SqList *L, int low, int high) {
    if (low < high) {
        //表长度大于一，进行分割
        //确定中轴位置
        QSort(L, low, Partition(L, low, high) - 1);    //递归左表
        QSort(L, Partition(L, low, high) + 1, high);     //递归右表
    }
}

//将序列进行分组，形成一个初始排序二叉树
int Partition(SqList *L, int low, int high) {
    //对表中low到high之间进行一次排序，将表分为两部分，左表都小，右表都大
    L->key[0] = L->key[low];  //设置左边第一位为中轴元素并存放在0位置
    while (low < high) {
        while (low < high && L->key[high] >= L->key[0]) {
            high--;
        }
        L->key[low] = L->key[high];   //将右表中小的放在左表low处（low处起始为中轴，中轴已存放在0位置）
        //接下来low移动
        while (low < high && L->key[low] <= L->key[0]) {
            low++;
        }
        L->key[high] = L->key[low];   //将左表中大的放在右表high处（此前high处的元素已经放在其他地方了）
    }
    //移动结束，将中轴放在中间位置
    L->key[low] = L->key[0];
    return low;
}

void SelectSort(SqList *L) {
    for (int i = 1; i < L->length; ++i) {
        int min = i; //设当前i为最小值
        for (int j = i + 1; j <= L->length; ++j) {
            if (L->key[j] < L->key[min]) {
                //j比min小
                min = j;
            }
        }
        if (min != i) {
            //使用异或操作符进行交换
            L->key[i] = L->key[i] ^ L->key[min];
            L->key[min] = L->key[i] ^ L->key[min];
            L->key[i] = L->key[i] ^ L->key[min];
        }
    }
}

void HeadSort(SqList *L) {
    CreateHeap(L);  //将1~n序列初始化成一个大根堆
    //将1位置（堆顶，最大元素）和i位置（最小元素）互换，最大元素沉入最后
    for (int i = L->length; i > 1; --i) {
        //进行交换
        L->key[1] = L->key[1] ^ L->key[i];
        L->key[i] = L->key[1] ^ L->key[i];
        L->key[1] = L->key[1] ^ L->key[i];
        //然后调整1~i-1
        HeadAdjust(L, 1, i - 1);
        //循环，依次将堆中最大元素（堆顶元素）沉入底部
    }
}

//调整s~m序列的堆
void HeadAdjust(SqList *L, int s, int m) {
    //s位置未不符合大根堆的结点，将其向堆下移动
    for (int i = 2 * s; i <= m; i *= 2) {//s*2是沿着s向下一层筛选
        if (i < m && L->key[i] < L->key[i + 1]) {
            i++;    //当左孩子i大于右孩时，i不变，i为要插入位置，否则i+1为插入位置
        }
        //如果要交换的结点值已经比两个孩子大则不需要交换了
        if (L->key[s] >= L->key[i]) {
            break;
        }
        //将i位置和s位置进行交换
        L->key[i] = L->key[i] ^ L->key[s];
        L->key[s] = L->key[i] ^ L->key[s];
        L->key[i] = L->key[i] ^ L->key[s];
        s = i;
    }
}

//初建堆
void CreateHeap(SqList *L) {
    for (int i = L->length / 2; i > 0; --i) {
        //从中间层向前一直到顶部对序列进行堆构建
        HeadAdjust(L, i, L->length);
    }
}

//将表r中low~mid和mid+1~high进行归并并将结果放在t中
void Merge(int *r, int *t, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = low;
    while (i <= mid && j <= high) {//其中没有表为空
        //将较小的放在新表t中
        if (r[i] <= r[j]) {
            t[k++] = r[i++];
        } else {
            t[k++] = r[j++];
        }
    }
    //将i，j中剩余的放入t中
    while (i <= mid) {
        t[k++] = r[i++];
    }
    while (j <= high) {
        t[k++] = r[j++];
    }
}

//对r low~high进行归并排序并存放结果到t
void MSort(int *r, int *t, int low, int high) {
    if (low == high) {
        t[low] = r[low];
    } else {
        int mid = (low + high) / 2;
        //开辟一个high长度的空间，前一半存储左表归并排序结果，后一半存储右表归并结果
        int *s = (int *) malloc(sizeof(int) * (high + 1));
        //归并排序左半并存储在s表的前半位置
        MSort(r, s, low, mid);
        //归并排序右半
        MSort(r, s, mid + 1, high);
        //将s表左右归并并存放在t中
        Merge(s, t, low, mid, high);
    }
}

void MergeSort(SqList *L) {
    MSort(L->key, L->key, 1, L->length);
}