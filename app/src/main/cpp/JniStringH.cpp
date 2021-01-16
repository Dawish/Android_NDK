//
// Created by Administrator on 2018/3/10.
//

#include <jni.h>
#include <string>
#include <string.h>
#import "JniStringH.h"
#include "Log.h"
#include<malloc.h>


std::string JniStringH::getHString(std::string inPutStr) {

    std::string resultStr;

    LOGI("getHString开始拼接字符串");

    std::string tempStr = "JNI_JNI_JNI_JNI_HHHH:";

    resultStr.append(tempStr);

    resultStr.append(inPutStr);

    LOGI("getHString开始拼符串拼接完成");

    return resultStr;
}
