//
// Created by danxingxi on 2021/1/24.
//
// http://c.biancheng.net/view/1991.html C语言指针讲解

#ifndef ANDROID_NDK_TYPE_C_H
#define ANDROID_NDK_TYPE_C_H

#include "Log.h"
#define square(x) ((x) * (x))
#define MAX_ARRAY_LENGTH 20

#ifdef __cplusplus
extern "C" {
#endif

int showType(void);

void getName(void);

int sum(int m, int n);

int pointSwitchValue(int m, int n);

#ifdef __cplusplus
}
#endif

#endif //ANDROID_NDK_TYPE_C_H