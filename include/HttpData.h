//
// Created by 鸢一折纸 on 2021/5/11.
//

//#ifndef WEB_SERVER_DEVELOPING_HTTPDATA_H
//#define WEB_SERVER_DEVELOPING_HTTPDATA_H

#pragma once

#include "HttpParse.h"
#include "HttpResponse.h"
#include "Socket.h"
#include "Timer.h"
#include <memory>

class TimerNode;

class HttpData : public std::enable_shared_from_this<HttpData> {

public:
    HttpData() : epoll_fd(-1) {}

public:
    std::shared_ptr<HttpRequest> request_;
    std::shared_ptr<HttpResponse> response_;
    std::shared_ptr<ClientSocket> clientSocket_;
    int epoll_fd;

    void closeTimer();

    void setTimer(std::shared_ptr<TimerNode>);

private:
    std::weak_ptr<TimerNode> timer_;
};

//#endif //WEB_SERVER_DEVELOPING_HTTPDATA_H
