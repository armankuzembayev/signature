#include "ThreadPool.h"

using namespace std;

ThreadPool::ThreadPool() : done(false), threads(thread::hardware_concurrency()) {
    workerQueue = make_unique<SharedQueue<function<void()>>>();

    try {
        for (auto &t: threads) {
            t = thread(&ThreadPool::workerThread, this);
        }
    } catch (const exception &e) {
        done = true;
        throw runtime_error("Executing thread error");
    }
}

void ThreadPool::workerThread() {
    while (!done) {
        function<void()> task;
        if (workerQueue->try_and_pop(task)) {
            task();
        } else {
            this_thread::yield();
        }
    }
}

ThreadPool::~ThreadPool() {
    done = true;

    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
