//
// Created by Administrator on 2019-03-28.
//
#include "logcat_mom.h"

#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <thread>
#include <stdio.h>

#include "log_utils.h"

void readIn(FILE *fp)
{
    LLOGV("%s start", __func__);

    /*
    int flags = fcntl(0, F_GETFL);
    // turn off blocking flag
    flags |= O_NONBLOCK;
    // set up non-blocking read
    int resultFcntl = fcntl(0, F_SETFL, flags); //avoid coverity static - without checking return value
    int n;
    char buf[512] = {0};
    while ((n = read(cinFd, buf, 512)) > 0) {
        LLOGV("read lol(%d) msg %s", n, buf);
    }
    */
    char buf[1024] = {0};
    while (1) {
        fgets(buf, 1024, fp);
        LLOGV("! %s\n", buf);
    }
    LLOGV("%s end", __func__);
}

void readIn(int cinFd)
{
    LLOGV("%s start", __func__);
    int n;
    char buf[512] = {0};
    while ((n = read(cinFd, buf, 512)) > 0) {
        LLOGV("read lol(%d) msg %s", n, buf);
    }
    LLOGV("%s end", __func__);
}
int32_t LogcatMom::popen_test2() {
    LLOGV("%s start", __func__);

    auto waitpid_status = [](int &status) -> void {
            if (WIFEXITED(status)) {
                LLOGD("normal termination, exit status(%d)", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                LLOGE("abnormal termination, sig num(%d)", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                LLOGE("child stopped, sig num(%d)", WSTOPSIG(status));
            }
        };

    FILE *fp = popen("/system/bin/logcat", "r");

    std::thread t1(readIn, fp);

    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    pclose(fp);
    LLOGV("%s end", __func__);

    return 0;
}

int32_t LogcatMom::pipe_test() {
    LLOGD("%s start", __func__);
    int n;
    int fd[2];
    const int MAXLINE = 512;
    pid_t pid;
    char line[MAXLINE];
    if (pipe(fd) < 0)
        LLOGV_TEST("pipe error");

    dup2(fd[1], STDOUT_FILENO);
    dup2(fd[0], STDIN_FILENO);

    if ((pid = fork()) < 0) {
        LLOGV_TEST("fork error");
    } else if (pid == 0) { /* child */
        close(fd[0]);
        write(STDOUT_FILENO, "hello world\n", 12);
    } else { /* parent */
        close(fd[1]);
        n = read(STDIN_FILENO, line, MAXLINE);
        LLOGV_TEST("parent read %s (%d)", line, n);
    }
    LLOGV("exit");
    return 0;
}

int32_t LogcatMom::popen_test() {
    LLOGV("%s start", __func__);

    int32_t pipefds[2];
    int32_t ret_val = 0;

    ret_val = pipe(pipefds);
    switch(ret_val) {
        case 0:
            LLOGV("created pipe fds ");
            break;
        case EFAULT:
        case EMFILE:
        case ENFILE:
            LLOGE("pipe error %s", std::strerror(errno));
            break;
    }
    LLOGD("pipe0(%d), pipe1(%d)", pipefds[0], pipefds[1]);

    pid_t pid = fork();

    char msg_buf[512] = "hello @child";
    write(STDOUT_FILENO, msg_buf, 512);

    char* logcat_args[] = {"/system/bin/logcat", nullptr};
    if (execv(logcat_args[0], logcat_args) == -1) {
        LLOGE("exec fail %s", std::strerror(errno));
    }
    write(STDOUT_FILENO, msg_buf, 512);

    int n;
    {
        char buf[512] = {0};
        while ((n = read(STDIN_FILENO, buf, 512)) > 0) {
            LLOGV("read lol(%d) msg %s", n, buf);
            break;
        }
    }
    /*
     * set flag non blocking
    int flags = fcntl(pipefds[0], F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(pipefds[0], F_SETFL, flags);
    */

    int status;
    if (waitpid(pid, &status, 0) != pid) {
        LLOGE("waitpid error %s", std::strerror(errno));
    }
}
int32_t LogcatMom::pipe_exec_test() {
    LLOGV("%s start", __func__);

    auto waitpid_status = [](int &status) -> void {
            if (WIFEXITED(status)) {
                LLOGD("normal termination, exit status(%d)", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                LLOGE("abnormal termination, sig num(%d)", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                LLOGE("child stopped, sig num(%d)", WSTOPSIG(status));
            }
        };

    int32_t pipefds[2];
    if (pipe(pipefds) != 0) {
        LLOGE("pipe error %s", std::strerror(errno));
        return -1;
    }
    LLOGD("pipe0(%d), pipe1(%d)", pipefds[0], pipefds[1]);
    if (dup2(pipefds[0], STDIN_FILENO) == -1) {
        LLOGE("pipe error %s", std::strerror(errno));
        return -1;
    }
    if (dup2(pipefds[1], STDIN_FILENO) == -1) {
        LLOGE("pipe error %s", std::strerror(errno));
        return -1;
    }

    int flags = fcntl(pipefds[1], F_GETFD);
    flags &= (~FD_CLOEXEC);
    flags = fcntl(pipefds[1], F_GETFD);

    pid_t pid = fork();
    if (pid < 0) {
        LLOGE("fail - fork %s", std::strerror(errno));
    } else if (pid == 0) { //child
        LLOGI("catmom bears logcat - exec");
        close(pipefds[0]);

        /* FIXME
         * test code - pipe/exec
         */
        char msg_buf[512] = "hello @child";
        write(pipefds[1], msg_buf, 512);

        char* logcat_args[] = {"/system/bin/logcat",  nullptr};
        if (execv(logcat_args[0], logcat_args) == -1) {
            LLOGE("exec fail %s", std::strerror(errno));
        }
        LLOGV("exit child");
        return 0;

    } else { //parent
        LLOGV("child(%d) parent(%d)", pid, getpid());
        close(pipefds[1]);

        /* read thread
         */
        //std::thread t1(readIn, pipefds[0]);
       /*
         * set flag non blocking
        int flags = fcntl(pipefds[0], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(pipefds[0], F_SETFL, flags);
        */

        int status;
        if (waitpid(pid, &status, 0) != pid) {
            LLOGE("waitpid error %s", std::strerror(errno));
        }
        waitpid_status(status);

   }
    LLOGV("%s end", __func__);
    return 0;
}
int32_t LogcatMom::init() {
    LLOGV("%s start", __func__);

    auto waitpid_status = [](int &status) -> void {
            if (WIFEXITED(status)) {
                LLOGD("normal termination, exit status(%d)", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                LLOGE("abnormal termination, sig num(%d)", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                LLOGE("child stopped, sig num(%d)", WSTOPSIG(status));
            }
        };

    int32_t pipefds[2];
    if (pipe(pipefds) != 0) {
        LLOGE("pipe error %s", std::strerror(errno));
        return -1;
    }
    LLOGD("pipe0(%d), pipe1(%d)", pipefds[0], pipefds[1]);
    if (dup2(pipefds[0], STDIN_FILENO) == -1) {
        LLOGE("pipe error %s", std::strerror(errno));
        return -1;
    }
    if (dup2(pipefds[1], STDIN_FILENO) == -1) {
        LLOGE("pipe error %s", std::strerror(errno));
        return -1;
    }

    int flags = fcntl(pipefds[1], F_GETFD);
    flags &= (~FD_CLOEXEC);
    flags = fcntl(pipefds[1], F_GETFD);

    pid_t pid = fork();
    if (pid < 0) {
        LLOGE("fail - fork %s", std::strerror(errno));
    } else if (pid == 0) { //child
        LLOGI("catmom bears logcat - exec");
        close(pipefds[0]);

        /* FIXME
         * test code - pipe/exec
         */
        char msg_buf[512] = "hello @child";
        write(pipefds[1], msg_buf, 512);

        char* logcat_args[] = {"""/system/bin/logcat",  nullptr};
        if (execv(logcat_args[0], logcat_args) == -1) {
            LLOGE("exec fail %s", std::strerror(errno));
        }
        LLOGV("exit child");
        return 0;

    } else { //parent
        LLOGV("child(%d) parent(%d)", pid, getpid());
        close(pipefds[1]);

        /* read thread
         */
        std::thread t1(readIn, pipefds[0]);
       /*
         * set flag non blocking
        int flags = fcntl(pipefds[0], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(pipefds[0], F_SETFL, flags);
        */

        int status;
        if (waitpid(pid, &status, 0) != pid) {
            LLOGE("waitpid error %s", std::strerror(errno));
        }
        waitpid_status(status);

   }
    LLOGV("%s end", __func__);
    return 0;
}
