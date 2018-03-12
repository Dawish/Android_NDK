#include <jni.h>
#include <string>
#include "JniStringH.h"
#include "StringUtil.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_stringFromJNI(
        JNIEnv *env, //JNIEnv的类型是一个指针，指向存储全部JNI函数指针的结构
        jobject     //这是非静态方法，这里表示this
) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_getHelloJni(JNIEnv *env, jobject instance) {

    return env->NewStringUTF("Hello Jni，欢迎来到我的世界...");
}


extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_getStringH(JNIEnv *env, jobject instance, jstring jstr_) {

    const char *str;
    str = env->GetStringUTFChars(jstr_, NULL);
    if (str == NULL){    /* str == NULL意味着JVM为native String分配内存失败 */
        return NULL;
    }

    std::string tempStr(str);

    std::string cs = JniStringH::getHString(tempStr);

    env->ReleaseStringUTFChars(jstr_, str);

    const char *p = cs.c_str();
    /* 构造新的Java.lang.String，如果JVM分配内存失败，则抛出OutOfMemoryError，并且返回NULL */
    return env->NewStringUTF(p);
}


