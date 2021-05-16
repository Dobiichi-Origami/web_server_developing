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

class HttpData : public std::enable_shared_from_this<HttpData> {    // 继承enable_shared_from_this以后，
    // 该对象可以调用shared_from_this函数来构造一个指向自身的shared_ptr对象，替代this作为参数传入。
    // 这么做是因为如果你期望用shared_ptr来替代this管理对象的话，在函数内部你无法构造出一个指向自身的、会引起原本计数增加的shared_ptr，和在外面对一个指针对象调用两次make_shared是一个效果。
    // 这个时候这个函数就有用了

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
