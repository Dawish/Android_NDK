//
// Created by Administrator on 2018/3/10.
//

#include <jni.h>
#include <string>
#include <android/log.h>
#import "danxx_ndk_JniH.h"

// log标签
#define  TAG    "JNI_ERROR:"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_JniH_getString(JNIEnv *env, jclass type) {

    // TODO
    LOGI("hahha");
    std::string str = "String from JniH";
    LOGI("==============hahha==============");
    return env->NewStringUTF(str.c_str());
}