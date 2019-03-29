//
// Created by Administrator on 2019-03-28.
//

#ifndef VCPLOGGER_LOG_UTIL_H
#define VCPLOGGER_LOG_UTIL_H

#include <android/log.h>
#include <string>

const static std::string TAG_LLOGGER = "VCP_LLOGGER";
const static std::string TAG_LLOGGER_TEST = "VCP_TEST";

#define LLOGV(...) \
    __android_log_print(ANDROID_LOG_VERBOSE, TAG_LLOGGER.c_str(), __VA_ARGS__)
#define LLOGD(...) \
    __android_log_print(ANDROID_LOG_DEBUG, TAG_LLOGGER.c_str(), __VA_ARGS__)
#define LLOGI(...) \
    __android_log_print(ANDROID_LOG_INFO, TAG_LLOGGER.c_str(), __VA_ARGS__)
#define LLOGW(...) \
    __android_log_print(ANDROID_LOG_WARN, TAG_LLOGGER.c_str(), __VA_ARGS__)
#define LLOGE(...) \
    __android_log_print(ANDROID_LOG_ERROR, TAG_LLOGGER.c_str(), __VA_ARGS__)
#define LLOGF(...) \
    __android_log_print(ANDROID_LOG_FATAL, TAG_LLOGGER.c_str(), __VA_ARGS__)

#define LLOGV_TEST(...) \
    __android_log_print(ANDROID_LOG_VERBOSE, TAG_LLOGGER_TEST.c_str(), __VA_ARGS__)

#endif //VCPLOGGER_LOG_UTIL_H
