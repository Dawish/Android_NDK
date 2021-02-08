//
// Created by Administrator on 2021/1/24.
//

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "Log.h"


// 申明结构体
struct Good {
    int age;
    char name;
};

int showStruct(void) {

    LOGD("%s", "showType");

    struct Good d;
    d.name = "dxx";
    d.age = 18;

    return d.age;
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