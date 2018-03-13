#include <jni.h>
#include <string>
#include <string.h>
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


extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_getStringNativeFormJava(JNIEnv *env, jobject instance) {

    //    jclass GetObjectClass(jobject obj) 获取调用该方法的java类
    jclass  _jThis = env->GetObjectClass(instance);
    //获取java类中的成员变量id
    jfieldID  jfieldID1 = env->GetFieldID(_jThis,"name","Ljava/lang/String;");
    //获取java类中的string成员变量 返回jni中的字符串
    jstring  str = (jstring) env->GetObjectField(instance, jfieldID1);

    //把jni字符串str转换为java中的string
    char *chars = (char *) env->GetStringChars(str, NULL);
    char temp[20] = " success!";
    char *resultStr = strcat(chars,temp);

    return env->NewStringUTF(resultStr);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_getStringNativeFormJavaMethod(JNIEnv *env, jobject instance) {

    // TODO


    return env->NewStringUTF("haha");
}