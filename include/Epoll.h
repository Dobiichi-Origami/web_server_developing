//
// Created by 鸢一折纸 on 2021/5/12.
//

//#ifndef WEB_SERVER_DEVELOPING_EPOLL_H
//#define WEB_SERVER_DEVELOPING_EPOLL_H

#pragma onceonce

#include "HttpData.h"
#include "Socket.h"
#include "Timer.h"

#include <sys/epoll.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>


class Epoll {

public:
    static int init(int max_events);    // 初始化Epoll事件处理器

    static int addFd(int epoll_fd, int fd, __uint32_t events, std::shared_ptr<HttpData>);

    static int modFd(int epoll_fd, int fd, __uint32_t events, std::shared_ptr<HttpData>);

    static int delFd(int epoll_fd, int fd);

    static std::vector<std::shared_ptr<HttpData>> poll(const ServerSocket &serverSocket, int max_event, int timeout);

    static void handleConnection(const ServerSocket &serverSocket);

public:
    static std::unordered_map<int, std::shared_ptr<HttpData>> httpDataMap;
    static const int MAX_EVENTS;
    static epoll_event *events;
    static TimerManager timerManager;
    const static __uint32_t DEFAULT_EVENTS;

};


//#endif //WEB_SERVER_DEVELOPING_EPOLL_H
