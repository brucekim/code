#include <jni.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include "log_utils.h"
#include "logcat_mom.h"

using namespace std;


extern "C"

JNIEXPORT jstring JNICALL
Java_com_lotte_vcplogger_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    LLOGD("test");
    LogcatMom catmom = LogcatMom::getInstance();
    catmom.init();
    //catmom.pipe_test();

    return env->NewStringUTF(hello.c_str());
}
