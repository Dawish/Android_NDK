//
// Created by danxingxi on 2021/1/24.
//

#ifndef ANDROID_NDK_TYPE_C_H
#define ANDROID_NDK_TYPE_C_H

#include "Log.h"
#define square(x) ((x) * (x))
#define MAX_ARRAY_LENGTH 20

#ifdef __cplusplus
extern "C" {
#endif

int showType(void);

char getName(void);

#ifdef __cplusplus
}
#endif

#endif //ANDROID_NDK_TYPE_C_H