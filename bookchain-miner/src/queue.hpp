#pragma once

#include <memory>
#include <mutex>
#include <queue>

namespace bookchain {

template <typename T>
class ThreadsafeQueue {
public:
    void push(T& element);
    T pop();

    bool empty();

private:
    std::queue<T> _queue;
    std::mutex _queueMutex;
};

template <typename T>
using sharedTSQueue = std::shared_ptr<ThreadsafeQueue<T>>;

template <typename T>
void ThreadsafeQueue<T>::push(T& element) {
    std::lock_guard<std::mutex> guard(this->_queueMutex);
    this->_queue.push(element);
}

template <typename T>
T ThreadsafeQueue<T>::pop() {
    std::lock_guard<std::mutex> guard(this->_queueMutex);
    T queueItem = this->_queue.front();
    this->_queue.pop();
    return queueItem;
}

template <typename T>
bool ThreadsafeQueue<T>::empty() {
    std::lock_guard<std::mutex> guard(this->_queueMutex);
    return this->_queue.empty();
}

}  // namespace bookchain
