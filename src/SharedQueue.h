#pragma once

#include <queue>
#include <mutex>
#include <exception>

template<typename T>
class SharedQueue {
public:

    SharedQueue &operator=(const SharedQueue &) = delete;

    SharedQueue(const SharedQueue &other) = delete;

    SharedQueue() = default;

    void push(T item) {
        std::lock_guard<std::mutex> lock(m_);
        queue_.push(std::move(item));
    }

    bool try_and_pop(T &popped_item) {
        std::lock_guard<std::mutex> lock(m_);
        if (queue_.empty()) return false;

        popped_item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

private:
    std::queue<T> queue_;
    mutable std::mutex m_;
};
