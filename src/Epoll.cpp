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


int Epoll::init(int max_events) {
    int epoll_fd = ::epoll_create(max_events);
    if (epoll_fd == -1) {
        std::cout << "epoll create error" << std::endl;
        exit(-1);
    }
    events = new epoll_event[max_events];
    return epoll_fd;
}

int Epoll::addFd(int epoll_fd, int fd, __uint32_t events, std::shared_ptr<HttpData> httpData) {
    epoll_event event;
    event.events = events;
    event.data.fd = fd;
    httpDataMap[fd] = httpData;
    int ret = ::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);

    if (ret < 0) {
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
    int ret = ::epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event);

    if (ret < 0) {
        std::cout << "epoll mod error" << std::endl;
        httpDataMap[fd].reset();
        return -1;
    }

    return 0;
}

int Epoll::delFd(int epoll_fd, int fd, __uint32_t events) {
    epoll_event event;
    event.events = events;
    event.data.fd = fd;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event);
    if (ret < 0) {
        std::cout << "epoll del error" << std::endl;
        return -1;
    }
    auto it = httpDataMap.find(fd);
    if (it != httpDataMap.end()) {
        httpDataMap.erase(it);
    }
    return 0;
}

void Epoll::handleConnection(const ServerSocket &serverSocket) {

    std::shared_ptr<ClientSocket> tempClient(new ClientSocket);

    while (serverSocket.accept(*tempClient) > 0) {
        int ret = setNonblocking(tempClient->fd);
        if (ret < 0) {
            std::cout << "setNonblocking error" << std::endl;
            tempClient->close();
            continue;
        }

        std::shared_ptr<HttpData> sharedHttpData(new HttpData);
        sharedHttpData->request_ = std::shared_ptr<HttpRequest>(new HttpRequest);
        sharedHttpData->response_ = std::shared_ptr<HttpResponse>(new HttpResponse);

        std::shared_ptr<ClientSocket> sharedClientSocket(new ClientSocket);
        sharedClientSocket.swap(tempClient);
        sharedHttpData->clientSocket_ = sharedClientSocket;
        sharedHttpData->epoll_fd = serverSocket.epoll_fd;

        addFd(serverSocket.epoll_fd, sharedClientSocket->fd, DEFAULT_EVENTS, sharedHttpData);
        timerManager.addTimer(sharedHttpData, TimerManager::DEFAULT_TIME_OUT);
    }
}

std::vector<std::shared_ptr<HttpData>> Epoll::poll(const ServerSocket &serverSocket, int max_event, int timeout) {
    int event_num = epoll_wait(serverSocket.epoll_fd, events, max_event, timeout);
    if (event_num < 0) {
        std::cout << "epoll_num=" << event_num << std::endl;
        std::cout << "epoll_wait error" << std::endl;
        std::cout << errno << std::endl;
        exit(-1);
    }

    std::vector<std::shared_ptr<HttpData>> httpDatas;

    for (int i = 0; i < event_num; i++) {
        int fd = events[i].data.fd;

        if (fd == serverSocket.listen_fd) {
            handleConnection(serverSocket);
        } else {
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLRDHUP) || (events[i].events & EPOLLHUP)) {
                auto it = httpDataMap.find(fd);
                if (it != httpDataMap.end()) {
                    it->second->closeTimer();
                }
                continue;
            }

            auto it = httpDataMap.find(fd);
            if (it != httpDataMap.end()) {
                if ((events[i].events & EPOLLIN) || (events[i].events & EPOLLPRI)) {
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