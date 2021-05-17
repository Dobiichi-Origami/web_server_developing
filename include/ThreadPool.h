//
// Created by 鸢一折纸 on 2021/5/12.
//

//#ifndef WEB_SERVER_DEVELOPING_THREADPOOL_H
//#define WEB_SERVER_DEVELOPING_THREADPOOL_H

#pragma once

#include "noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include <vector>
#include <list>
#include <functional>
#include <pthread.h>
#include <memory>


const int MAX_THREAD_SIZE = 1024;   // 线程数上限
const int MAX_QUEUE_SIZE = 10000;   // 最大队上限

typedef enum {  // 枚举类型
    immediate_mode = 1,
    graceful_mode = 2
} ShutdownMode;

struct ThreadTask { // 线程任务结构体
    std::function<void(std::shared_ptr<void>)> process; // 封装一个函数对象，作为所需执行任务的指代
    std::shared_ptr<void> arg;  // 这里是任务的参数
};


class ThreadPool {  // 线程池对象

public:
    ThreadPool(int thread_s, int max_queue_s);

    ~ThreadPool();

    bool append(std::shared_ptr<void> arg, std::function<void(std::shared_ptr<void>)> fun); // 往线程池里头添加任务，分配线程

    void shutdown(bool graceful);

private:
    static void *worker(void *args);

    void run();

private:
    MutexLock mutex_;   // 我们自己封装的互斥锁对象
    Condition condition_;   // 我们自己封装的互斥条件对象

    int thread_size;    // 线程数
    int max_queue_size; // 最大等待队列数
    int started;    //
    int shutdown_;
    std::vector<pthread_t> threads;
    std::list<ThreadTask> request_queue;
};

//#endif //WEB_SERVER_DEVELOPING_THREADPOOL_H
