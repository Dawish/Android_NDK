//
// Created by danxx on 2018/3/10.
//
#include <android/log.h>

#ifndef ANDROID_NDK_LOG_H
#define ANDROID_NDK_LOG_H

// log标签
#define TAG "Jni_Log"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG, __VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#endif //ANDROID_NDK_LOG_H
