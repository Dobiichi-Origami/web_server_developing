//
// Created by 鸢一折纸 on 2021/5/11.
//

//#ifndef WEB_SERVER_DEVELOPING_TIMER_H
//#define WEB_SERVER_DEVELOPING_TIMER_H

#pragma once

#include "MutexLock.h"
#include "HttpData.h"

#include <queue>
#include <deque>
#include <memory>

class HttpData;

class TimerNode {

public:
    TimerNode(std::shared_ptr<HttpData> httpData, size_t timeout);
    ~TimerNode();

    bool isDeleted() const { return deleted_; }

    size_t getExpireTime() { return expiredTime; }

    bool isExpired() {
        return expiredTime < current_msec;
    }

    std::shared_ptr<HttpData> getHttpData() { return httpData; }

    void deleted();

    static void current_time();

    static size_t current_msec; // 当前运行的时间数，以毫秒为单位

private:
    bool deleted_;
    size_t expiredTime;
    std::shared_ptr<HttpData> httpData;
};

struct TimerCmp {
    bool operator()(std::shared_ptr<TimerNode> &a, std::shared_ptr<TimerNode> &b) const {
        return a->getExpireTime() > b->getExpireTime();
    }
};

class TimerManager {
public:
    typedef std::shared_ptr<TimerNode> Shared_TimerNode;

    void addTimer(std::shared_ptr<HttpData> httpData, size_t timeout);

    void handle_expired_event();

    const static size_t DEFAULT_TIME_OUT;

private:
    std::priority_queue<Shared_TimerNode, std::deque<Shared_TimerNode>, TimerCmp> TimerQueue;
    MutexLock lock_;
};

//#endif //WEB_SERVER_DEVELOPING_TIMER_H
