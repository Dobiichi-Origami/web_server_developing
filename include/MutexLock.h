//
// Created by 鸢一折纸 on 2021/5/10.
//

//#ifndef WEB_SERVER_DEVELOPING_MUTEXLOCK_H
//#define WEB_SERVER_DEVELOPING_MUTEXLOCK_H

#pragma once

#include <pthread.h>
#include "noncopyable.h"

class MutexLock: public noncopyable {

public:
    MutexLock() {
        pthread_mutex_init(&mutex_, NULL);
    }
    ~MutexLock() {
        pthread_mutex_destroy(&mutex_);
    }
    void lock() {
        pthread_mutex_lock(&mutex_);
    }
    void unlock() {
        pthread_mutex_unlock(&mutex_);
    }
    pthread_mutex_t *getMutex() {
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
};


class MutexLockGuard: public noncopyable {
public:
    explicit MutexLockGuard(MutexLock &mutex): mutex_(mutex) {
        mutex_.lock();
    }

    ~MutexLockGuard() {
        mutex_.unlock();
    }

private:
    MutexLock &mutex_;
};

//#endif //WEB_SERVER_DEVELOPING_MUTEXLOCK_H
