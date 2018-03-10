#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
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