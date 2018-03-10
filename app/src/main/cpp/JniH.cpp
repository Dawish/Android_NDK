//
// Created by Administrator on 2018/3/10.
//

#include <jni.h>
#include <string>
#include <android/log.h>
#import "danxx_ndk_JniH.h"
#include "log.h"

#define  TAG    "JNI_ERROR:"


extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_JniH_getString(JNIEnv *env, jclass type) {

    // TODO
    LOGI("hahha");
    std::string str = "String from JniH";
    LOGI("==============hahha==============");
    return env->NewStringUTF(str.c_str());
}