//
// Created by 鸢一折纸 on 2021/5/12.
//

#include "../include/ThreadPool.h"
#include <iostream>
#include <pthread.h>
#include <sys/prctl.h>


ThreadPool::ThreadPool(int thread_s, int max_queue_s) : max_queue_size(max_queue_s), thread_size(thread_s),
    condition_(mutex_), started(0), shutdown_(0) {  // 构造线程池，初始化一堆变量
    if (thread_s <= 0 || thread_s > MAX_THREAD_SIZE) {  // 排除异常情况
        thread_size = 4;
    }

    if (max_queue_s <= 0 || max_queue_s > MAX_QUEUE_SIZE) { // 同上
        max_queue_size = MAX_QUEUE_SIZE;
    }

    threads.resize(thread_size);    // 将vector大小设置为不小于这个大小的最小的2的幂次

    for (int i = 0; i < thread_size; i++) { // 在每个元素空间中初始化一个线程id，它们的工作都是执行自带的worker函数的内容
        if (pthread_create(&threads[i], NULL, worker, this) != 0) {
            std::cout << "ThreadPool init error" << std::endl;
            throw std::exception();
        }
        started++;  // 线程数加一
    }
}

ThreadPool::~ThreadPool() {}

bool ThreadPool::append(std::shared_ptr<void> arg, std::function<void (std::shared_ptr<void>)> fun) {

    if (shutdown_) {    // 如果已经关闭线程池
        std::cout << "ThreadPool has shutdown" << std::endl;
        return false;
    }

    MutexLockGuard guard(this->mutex_); // 上锁，此时只能有一个线程操作线程池
    if (request_queue.size() > max_queue_size) {    // 如果请求分配的任务数量挤爆了请求等待队列
        std::cout << max_queue_size;
        std::cout << "ThreadPool too many requests" << std::endl;
        return false;
    }

    ThreadTask threadTask;  // 初始化任务体
    threadTask.arg = arg;
    threadTask.process = fun;

    request_queue.push_back(threadTask);    // 塞进请求等待队列里
    condition_.notify();    // 让一个线程出来干活
    return true;    // 退出后该锁被释放
}

void ThreadPool::shutdown(bool graceful) {  // 关闭线程池
    MutexLockGuard guard(this->mutex_); // 上锁
    if (shutdown_) {
        std::cout << "has shutdown" << std::endl;
    }
    shutdown_ = graceful ? graceful_mode : immediate_mode;  // 决定关闭的资源模式
    condition_.notifyAll(); // 由于程序设计的原因，这里用notify()是一个效果

    for (int i = 0; i < thread_size; i++) {
        if (pthread_join(threads[i], NULL) != 0) {  // 一个一个的回收线程资源
            std::cout << "pthread_join error" <<std::endl;
        }
    }
}

void *ThreadPool::worker(void *args) {
    ThreadPool *pool = static_cast<ThreadPool *>(args);
    // 退出线程
    if (pool == nullptr)
        return NULL;
    prctl(PR_SET_NAME,"EventLoopThread");

    // 执行线程主方法
    pool->run();
    return NULL;
}

void ThreadPool::run() {
    while (true) {
        ThreadTask  requestTask;
        {   // 这里加上大括号是为了限制guard的生命周期在这个大括号里，实现对这一系列操作的原子操作
            // 一次只允许一个工作线程获取任务
            // 如果获取不到说明没有任务，其他的工作线程也会被阻挡在临界区外
            // 最终也只会有一个线程在condition_上等待
            // clever
            MutexLockGuard guard(this->mutex_);
            // 无任务 且未shutdown 则条件等待, 注意此处应使用while而非if
            // 因为在多处理器体系和一些操作系统的实现中，pthread_cond_signal这个函数的语义是『至少唤醒一个线程』
            // 最终导致其实不只有一个线程被唤醒
            // 如果这些线程执行的是不同的任务（也有可能是执行相同任务但是持有不同锁的多个线程），那么它们都会从wait中被唤醒进入执行状态
            // 此时就可能会发生资源的争抢，需要你while循环判断资源是否可用，如果是if则无法实现循环检查
            while (request_queue.empty() && !shutdown_) {
                condition_.wait();
            }

            // 如果现在立刻要关，或者是慷慨模式先处理完再关但是队列里面已经什么都没有了
            if ((shutdown_ == immediate_mode) || (shutdown_ == graceful_mode && request_queue.empty())) {
                break;  // 直接结束任务
            }
            // 不然就一个个处理队列里面的任务
            requestTask = request_queue.front();
            request_queue.pop_front();
        }
        requestTask.process(requestTask.arg);
    }
}