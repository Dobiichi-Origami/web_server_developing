//
// Created by 鸢一折纸 on 2021/5/12.
//

#include "../include/Epoll.h"
#include "../include/Util.h"
#include <iostream>
#include <vector>
#include <sys/epoll.h>
#include <cstdio>


std::unordered_map<int, std::shared_ptr<HttpData>> Epoll::httpDataMap;
const int Epoll::MAX_EVENTS = 10000;
epoll_event *Epoll::events;

const uint32_t Epoll::DEFAULT_EVENTS = (EPOLLIN | EPOLLET | EPOLLONESHOT);

TimerManager Epoll::timerManager;


// 初始化epoll的各项属性
int Epoll::init(int max_events) {
    int epoll_fd = ::epoll_create(max_events);
    if (epoll_fd == -1) {
        std::cout << "epoll create error" << std::endl;
        exit(-1);
    }
    events = new epoll_event[max_events];   // 为epoll创建用户态下用于接受内核态的epoll_event事件的缓存
    return epoll_fd;
}

// 添加文件描述符
int Epoll::addFd(int epoll_fd, int fd, __uint32_t events, std::shared_ptr<HttpData> httpData) {
    epoll_event event;  // 初始化epoll_event
    event.events = events;  // 设置该event的监听事件列表
    event.data.fd = fd; // 并且把携带的数据设置为用户描述符
    httpDataMap[fd] = httpData; // 在httpDataMap中设置该文件描述符的数据
    int ret = ::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event); // 往epoll中添加该文件描述符对应的事件

    if (ret < 0) {  //
        std::cout << "epoll add error" << std::endl;
        httpDataMap[fd].reset();
        return -1;
    }

    return 0;
}

int Epoll::modFd(int epoll_fd, int fd, __uint32_t events, std::shared_ptr<HttpData> httpData) {
    epoll_event event;
    event.events = events;
    event.data.fd = fd;

    httpDataMap[fd] = httpData;
    int ret = ::epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event); // 和addFd相比只有这一行的参数2改变了

    if (ret < 0) {
        std::cout << "epoll mod error" << std::endl;
        httpDataMap[fd].reset();
        return -1;
    }

    return 0;
}

// 一样，但不完全一样
int Epoll::delFd(int epoll_fd, int fd, __uint32_t events) {
    epoll_event event;
    event.events = events;
    event.data.fd = fd;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event);   // 删除文件描述符指定的事件监听
    if (ret < 0) {
        std::cout << "epoll del error" << std::endl;
        return -1;
    }
    auto it = httpDataMap.find(fd); // epoll里删完了还不算，要在httpDataMap里面一块删除了才可以
    if (it != httpDataMap.end()) {
        httpDataMap.erase(it);
    }
    return 0;
}

void Epoll::handleConnection(const ServerSocket &serverSocket) {

    std::shared_ptr<ClientSocket> tempClient(new ClientSocket); // 创建一个指定特定客户端的套接字

    while (serverSocket.accept(*tempClient) > 0) {  // 当我们正式创建一个链接
        int ret = setNonblocking(tempClient->fd);
        if (ret < 0) {
            std::cout << "setNonblocking error" << std::endl;
            tempClient->close();
            continue;
        }

        std::shared_ptr<HttpData> sharedHttpData(new HttpData); // 初始化一个HttpData，并且在下面设置它的属性
        sharedHttpData->request_ = std::shared_ptr<HttpRequest>(new HttpRequest);
        sharedHttpData->response_ = std::shared_ptr<HttpResponse>(new HttpResponse);

        std::shared_ptr<ClientSocket> sharedClientSocket(new ClientSocket);
        sharedClientSocket.swap(tempClient);    // 交换两个共享指针的值
        sharedHttpData->clientSocket_ = sharedClientSocket;
        sharedHttpData->epoll_fd = serverSocket.epoll_fd;

        addFd(serverSocket.epoll_fd, sharedClientSocket->fd, DEFAULT_EVENTS, sharedHttpData);
        // 将这个Http链接加入到epoll事件监听中，监听默认事件。
        // 并且把对应的httpData指针放入httpDataMap中

        timerManager.addTimer(sharedHttpData, TimerManager::DEFAULT_TIME_OUT);
        // 为这个Http链接添加计时器
    }
}

// 轮询
std::vector<std::shared_ptr<HttpData>> Epoll::poll(const ServerSocket &serverSocket, int max_event, int timeout) {
    int event_num = epoll_wait(serverSocket.epoll_fd, events, max_event, timeout);  // 接受需要处理的事件，返回值为需要处理的事件数目
    if (event_num < 0) {
        std::cout << "epoll_num=" << event_num << std::endl;
        std::cout << "epoll_wait error" << std::endl;
        std::cout << errno << std::endl;
        exit(-1);
    }

    std::vector<std::shared_ptr<HttpData>> httpDatas;

    for (int i = 0; i < event_num; i++) {
        int fd = events[i].data.fd;

        if (fd == serverSocket.listen_fd) { // 如果是监听端口有事件要处理，那必然是有新的链接请求，当场处理了
            handleConnection(serverSocket);
        } else {
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLRDHUP) || (events[i].events & EPOLLHUP)) {    // 如果出错，或者客户端或自己挂起了链接
                auto it = httpDataMap.find(fd);
                if (it != httpDataMap.end()) {  // 抬出去，清空定时器，清除位于HttpDataMap中的记录，定时器析构释放HttpData指针对应的对象
                    it->second->closeTimer();
                }
                continue;
            }

            auto it = httpDataMap.find(fd);
            if (it != httpDataMap.end()) {
                if ((events[i].events & EPOLLIN) || (events[i].events & EPOLLPRI)) {    // 只管输入和紧急事件可读两种
                    httpDatas.push_back(it->second);
                    it->second->closeTimer();
                    httpDataMap.erase(it);
                }
            } else {
                std::cout << "长连接第二次连接未找到" << std::endl;
                ::close(fd);
                continue;
            }
        }
    }

    return httpDatas;
}