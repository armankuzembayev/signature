#pragma once

#include <atomic>
#include <thread>
#include <vector>
#include <functional>

#include "SharedQueue.h"

class ThreadPool {
public:
    ThreadPool();

    template<typename FunctionType>
    void submit(FunctionType f);

    ~ThreadPool();

private:
    void workerThread();

    std::atomic<bool> done;
    std::unique_ptr<SharedQueue<std::function<void()>>> workerQueue;
    std::vector<std::thread> threads;
};

template<typename FunctionType>
void ThreadPool::submit(FunctionType f) {
    workerQueue->push(std::function<void()>(f));
}
