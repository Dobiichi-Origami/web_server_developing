//
// Created by 鸢一折纸 on 2021/5/10.
//

#include "../include/Util.h"

#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <sys/stat.h>

using std::string;

string &ltrim(string &str) {    //去除左边的制表符
    if (str.empty()) {
        return str;
    }

    str.erase(0, str.find_first_not_of(" \t"));
    return str;
}

string &rtrim(string &str) {    //去除右边的制表符
    if (str.empty()) {
        return str;
    }

    str.erase(str.find_last_not_of(" \t") + 1);
    return str;
}

string &trim(string &str) {     //去除两边的制表符
    if (str.empty()) {
        return str;
    }

    ltrim(str);
    rtrim(str);
    return str;
}

int setNonblocking(int fd) {    //将文件描述符设置为不可阻塞的状态
    int old_option = fcntl(fd, F_GETFL);    //获得原有的描述符状态标记
    int new_option = old_option | O_NONBLOCK;   //设置非阻塞操作位，这样子客户端接上套接字时才能进行写操作。
    fcntl(fd, F_SETFL, new_option);     //把新的状态标记设置回去
    return old_option;      //返回原有的状态标记
}

void handle_for_sigpipe() {     //处理sigpipe信号
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));  //初始化sigaction结构体
    sa.sa_handler = SIG_IGN;    //设置忽略性处理方式，sa_handler是一个int
    sa.sa_flags = 0;    //把所有选项位置零
    if (sigaction(SIGPIPE, &sa, NULL))  //为该进程设置处理方式
        printf("%s\n", strerror(errno));
}

int check_base_path(char *basePath) {
    struct stat file;   //创建文件状态描述符
    if (stat(basePath, &file) == -1) {  //将指定地址的文件的状态读入file描述符中
        return -1;
    }

    if (!S_ISDIR(file.st_mode) || access(basePath, R_OK) == -1) {   //判断是否是一个目录，以及能否读取这个目录下的内容。两者中有一项不符合即报错
        return -1;
    }

    return 0;
}

