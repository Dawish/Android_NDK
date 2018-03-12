#include <jni.h>
#include <string>
#include <string.h>
#include "JniStringH.h"

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

    //将jstring转换成const char*指针，使用const修饰符表示其内容不可被修改
    const char* c1=env->GetStringUTFChars(jstr_, NULL);
    //计算新字符串的长度
    int size = strlen(c1);
    //创建一个新的字符串，这里长度+1是为了使字符串有结尾标记'\0'
    char * n_char=new char[size+1];
    //利用C标准库提供的字符串操作方法对字符串进行连接，这里需要include"string.h"头文件
    strcpy(n_char,c1);

    //将生成的新字符串转换成UTF的jstring
    jstring rs = env->NewStringUTF(n_char);

    //删除刚刚分配的内存 避免引起内存泄漏
    delete [] n_char;

    //通知JVM虚拟机Native代码不在持有字符串的引用，说明白点,就是告诉虚拟机我不使用它了，你可以回收了。
    //因为在JVM中如果对象被引用，那么对象将不会被回收。
    //这里为什么要传递jstring和生成的char*呢？是因为char*有可能是jstring的拷贝，如果是拷贝，那么char*就应该被删除。
    env->ReleaseStringUTFChars(jstr_,c1);

    jclass strClass1 = (env)->FindClass("Ljava/lang/String;");
    std::string strTemp = JniStringH ::getHString(rs);
    return rs;
}


