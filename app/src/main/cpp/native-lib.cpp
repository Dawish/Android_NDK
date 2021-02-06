#include <jni.h>
#include "string.h"
#include <stdlib.h>
#include "JniStringH.h"
#include "StringUtil.h"
#include "A.h"
#include "Log.h"
#include <unistd.h>
#include <sys/stat.h>
#include<stdint.h>
#include "Type_c.h"

using namespace std;

extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_stringFromJNI(
        //JNIEnv的类型是一个指针，指向存储全部JNI函数指针的结构,是java和c++/c交互的桥梁
        // java每个线程在和C/C++互相调用的时候。其相应的JNIEnv 也是相互独立。
        // 参考： https://www.cnblogs.com/mfmdaoyou/p/7252031.html
        JNIEnv *env,
        //这是非静态方法，这里表示this
        jobject) {
    string hello = " -->Hello from C++";
    // 没使用new关键字创建对象，main函数结束后会自动回收对象
    A a = A();

    hello = a.getStr() + hello;

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
    if (str == NULL) {    /* str == NULL意味着JVM为native String分配内存失败 */
        return NULL;
    }

    std::string tempStr(str);

    std::string cs = JniStringH::getHString(tempStr);

    env->ReleaseStringUTFChars(jstr_, str);

    const char *p = cs.c_str();
    /* 构造新的Java.lang.String，如果JVM分配内存失败，则抛出OutOfMemoryError，并且返回NULL */
    return env->NewStringUTF(p);
}


//从java类中获取一个字符串
extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_getStringNativeFormJava(JNIEnv *env, jobject instance) {

    // jclass GetObjectClass(jobject obj) 获取调用该方法的java类
    jclass _jThis = env->GetObjectClass(instance);
    //获取java类中的成员变量id
    jfieldID jfieldID1 = env->GetFieldID(_jThis, "name", "Ljava/lang/String;");
    //获取java类中的string成员变量 返回jni中的字符串
    jstring str = (jstring) env->GetObjectField(instance, jfieldID1);

    //把jni字符串str转换为java中的string
    char *chars = (char *) env->GetStringUTFChars(str, NULL);
    char temp[20] = " success!";
    char *resultStr = strcat(chars, temp);

    return env->NewStringUTF(resultStr);
}

//访问java类中的一个方法
extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_getStringNativeFormJavaMethod(JNIEnv *env, jobject instance) {

    // TODO
    jclass jclass_ = env->GetObjectClass(instance);
    jmethodID jmethodID = env->GetMethodID(jclass_, "getName", "()Ljava/lang/String;");
    //调用java中的getName方法
    jstring jstring_ = (jstring) env->CallObjectMethod(instance, jmethodID);

    //把jni字符串str转换为java中的string
    char *chars = (char *) env->GetStringUTFChars(jstring_, NULL);
    char temp[30] = " FormJavaMethod success!";
    char *resultStr = strcat(chars, temp);

    return env->NewStringUTF(resultStr);
}

int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;//升序
}

//变量的前面表示取变量地址赋值给指针， 如：int a = 0; int *pa = &a;
//* (int *) 将指针转成int*，然后取该指针指向地址的值

extern "C"
JNIEXPORT void JNICALL
Java_danxx_ndk_MainActivity_getArray(JNIEnv *env, jobject instance, jintArray arrays_) {
    //把java数组转换为jni数组指针
    jint *arrays = env->GetIntArrayElements(arrays_, NULL);
    // TODO
    //获取数据长度
    int _len = env->GetArrayLength(arrays_);

    qsort(arrays, _len, sizeof(int), compare);

    env->ReleaseIntArrayElements(arrays_, arrays, 0);
}

//jni异常捕捉和抛出，抛出后java中可捕捉到
extern "C"
JNIEXPORT void JNICALL
Java_danxx_ndk_MainActivity_jniExceptionTest(JNIEnv *env, jobject instance) {

    // TODO
    jclass _class = env->GetObjectClass(instance);
    //故意制造异常
    jfieldID jfieldID1 = env->GetFieldID(_class, "name2", "Ljava/lang/String;");
    //ExceptionClear()：清除一个待决的异常。
    //ExceptionDescribe()：打印一个异常和堆栈跟踪信息。
    //ExceptionOccurred()：判断一个异常是否已被丢弃，但尚未清除。
    jthrowable jthrowable1 = env->ExceptionOccurred();
    if (jthrowable1 != NULL) {
        //清除异常，java中不会捕捉到
        env->ExceptionClear();
        //重新操作
        jfieldID1 = env->GetFieldID(_class, "name", "Ljava/lang/String;");
    }
    //获取java字符串
    jstring jstring1 = (jstring) env->GetObjectField(instance, jfieldID1);
    //获得java中utf-8字符串指针
    char *strChar = (char *) env->GetStringUTFChars(jstring1, NULL);
    //int strcmp(const char* __lhs, const char* __rhs)
    if (strcmp(strChar, "xixi")) {
        //故意抛出异常，让java中可以catch住 jclass FindClass(const char* name)
        jclass javaThrow = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(javaThrow, "参数错误！");

    }

}

extern "C"
JNIEXPORT jstring  JNICALL
Java_danxx_ndk_MainActivity_ndkReadFile(JNIEnv *env, jobject instance, jstring strPath_) {

    const char *strPath = env->GetStringUTFChars(strPath_, 0);

    LOGD("%s", "strPath");
    LOGD("%s", strPath);

    string str = "";
    int nRet = access(strPath, F_OK);
    if (nRet) {
        str = "File Not Exist.";
        LOGD("%s", "NDK read file not exist.");
    } else {
        LOGD("%s", "NDK read file exist.");
        FILE *pFile = fopen(strPath, "r");
        fseek(pFile, 0L, SEEK_END);
        int nFileSize = ftell(pFile);
        char *pszBuf = NULL;
        pszBuf = new char[nFileSize];
        if (pszBuf) {
            rewind(pFile);
            fread(pszBuf, nFileSize, 1, pFile);
            str = pszBuf;
            delete[]pszBuf;
            pszBuf = NULL;
        }
        fclose(pFile);
    }

    env->ReleaseStringUTFChars(strPath_, strPath);

    return env->NewStringUTF(str.data());

}
extern "C"
JNIEXPORT jstring JNICALL
Java_danxx_ndk_MainActivity_invokeC(JNIEnv *env, jobject thiz) {

    getName();

    int mSum = sum(1, 3);
    string mm = to_string(mSum);
    LOGD("%s", mm.c_str());

    return env->NewStringUTF("invokeC");
}