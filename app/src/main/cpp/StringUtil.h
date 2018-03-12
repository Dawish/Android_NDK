#ifndef ANDROID_NDK_STRINGUU_H
#define ANDROID_NDK_STRINGUU_H
#include <string>
#include <jni.h>

/**
 * java内部是使用16bit的unicode编码（UTF-16）来表示字符串的，无论中文英文都是2字节；
 * jni内部是使用UTF-8编码来表示字符串的，UTF-8是变长编码的unicode，一般ascii字符是1字节，中文是3字节；
 * c/c++使用的是原始数据，ascii就是一个字节了，中文一般是GB2312编码，用两个字节来表示一个汉字。
 */
class StringUtil {
    public:

        // C++字符串转换为java 字符串
        static jstring CStr2Jstring(JNIEnv *env, const char *pat);

        //java 字符串 转换为C++字符串
        static char *  JString2CStr(JNIEnv *env, jstring jstr);

};

#endif //ANDROID_NDK_STRINGUU_H