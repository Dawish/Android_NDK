//
// Created by Administrator on 2021/1/24.
//

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "Log.h"
#include "Type_c.h"


// 申明结构体
struct Good {
    int age;
    char name[50];
} good = {212, "good_name"};

// 有多成员的共用体，但是任何时候只能有一个成员带有值。
union Data {
    int i;
    float f;
    char  str[20];
};

int showStruct(void) {

    LOGD("%s", "showType");

//    struct Good myd;
//    myd.name = "dxx";
//    myd.age = 18;
    union Data data;
    LOGD("%s", "union");
    data.i = good.age;
    return data.i;
}

char* getGoodName(void) {
    struct Good good1;
    struct Good good2;

    good1.age = 21;
    strcpy(good1.name, "daxigua");

    good2.age = 22;
    strcpy(good2.name, "xiaoxigua");

    char *tN = NULL;
    tN = &good2.name;
    return tN;
}

void getName(void){

    char name[20]  = "asdasd";
    // char数组可以直接按index使用
    name[0] = 'd';
    name[1] = 'x';
    name[2] = 'x';
    LOGD("%s", name);

    // 赋值
    strcpy(name, "new");
    // 拼接内容
    strcat(name, "added");
    LOGD("%s", name);

    // char指针不可以直接按index使用
//    char *name2 = &name;
//    LOGD("%s", name2);
//    name2[0] = 'p';

}

int sum(int m, int n) {
    int i, sum = 0;
    for (i = m; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int pointSwitchValue(int a, int b){

    int temp;
    int *pa = &a, *pb = &b;
    printf("a=%d, b=%d\n", a, b);
    /*****开始交换*****/
    // 将a的值先保存起来
    temp = *pa;
    // 将b的值交给a
    *pa = *pb;
    // 再将保存起来的a的值交给b
    *pb = temp;

    return 0;
}

SIZE getSize() {
    SIZE mSize = 199;
    printf("SIZE = %d", mSize);
    return mSize;
}