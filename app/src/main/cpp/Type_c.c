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
    char name[50];
};

extern int showType(void) {

    LOGD("%s", "showType");

    return sizeof(int);
}

extern char getName(void) {

    // 使用结构体
    struct Good mG1;
    mG1.age = 2;
    strcpy(mG1.name, "大西瓜");

    return mG1.name;
}
