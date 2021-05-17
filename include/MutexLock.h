//
// Created by 鸢一折纸 on 2021/5/10.
//

//#ifndef WEB_SERVER_DEVELOPING_MUTEXLOCK_H
//#define WEB_SERVER_DEVELOPING_MUTEXLOCK_H

#pragma once

#include <pthread.h>
#include "noncopyable.h"

class MutexLock: public noncopyable {   // 封装pthread_mutex类，继承noncopyable

public:
    MutexLock() {   // 构造互斥锁
        pthread_mutex_init(&mutex_, NULL);
    }
    ~MutexLock() {  // 析构互斥锁
        pthread_mutex_destroy(&mutex_);
    }
    void lock() {   // 上锁
        pthread_mutex_lock(&mutex_);
    }
    void unlock() { // 解锁
        pthread_mutex_unlock(&mutex_);
    }
    pthread_mutex_t *getMutex() {   // 获得锁本身
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
};


class MutexLockGuard: public noncopyable {  // 对锁的操作再封装，实现了自动上锁和自动释放锁的功能
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
