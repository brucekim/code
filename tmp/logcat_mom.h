//
// Created by Administrator on 2019-03-28.
//

#ifndef VCPLOGGER_LOGCAT_MOM_H
#define VCPLOGGER_LOGCAT_MOM_H

#include <future>
#include <stdint.h>
#include <poll.h>

class LogcatMom {
private:
    LogcatMom() {};
public:
    static LogcatMom getInstance() {
        static LogcatMom inst;
        return inst;
    }

    int32_t init();
    int32_t pipe_test();
    int32_t popen_test2();
    int32_t pipe_exec_test();
};

#endif //VCPLOGGER_LOGCAT_MOM_H
