//
// Created by 鸢一折纸 on 2021/5/11.
//

//#ifndef WEB_SERVER_DEVELOPING_CONDITION_H
//#define WEB_SERVER_DEVELOPING_CONDITION_H

#pragma once

#include "MutexLock.h"
#include "noncopyable.h"
#include <pthread.h>


class Condition : public noncopyable {
public:
    explicit Condition(MutexLock &mutex) : mutex_(mutex) {
        pthread_cond_init(&cond_, NULL);
    }

    ~Condition() {
        pthread_cond_destroy(&cond_);
    }

    void wait() {
        pthread_cond_wait(&cond_, mutex_.getMutex());
    }

    void notify() {
        pthread_cond_signal(&cond_);
    }

    void notifyAll() {
        pthread_cond_broadcast(&cond_);
    }

private:
    MutexLock &mutex_;
    pthread_cond_t cond_;
};


//#endif //WEB_SERVER_DEVELOPING_CONDITION_H
