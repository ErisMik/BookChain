#pragma once

#include <deque>
#include <memory>
#include <mutex>

namespace bookchain {

template <typename T>
class ThreadsafeQueue {
public:
    void push(T& element);
    T front();
    T pop();

    void lock();
    void unlock();

    auto begin();
    auto end();

    bool empty();

private:
    std::deque<T> _queue;
    std::mutex _queueMutex;
};

template <typename T>
void ThreadsafeQueue<T>::push(T& element) {
    std::lock_guard<std::mutex> guard(this->_queueMutex);
    this->_queue.push_back(element);
}

template <typename T>
T ThreadsafeQueue<T>::front() {
    std::lock_guard<std::mutex> guard(this->_queueMutex);
    T queueItem = this->_queue.front();
    return queueItem;
}

template <typename T>
T ThreadsafeQueue<T>::pop() {
    std::lock_guard<std::mutex> guard(this->_queueMutex);
    T queueItem = this->_queue.front();
    this->_queue.pop_front();
    return queueItem;
}

template <typename T>
void ThreadsafeQueue<T>::lock() {
    this->_queueMutex.lock();
}

template <typename T>
void ThreadsafeQueue<T>::unlock() {
    this->_queueMutex.unlock();
}

template <typename T>
auto ThreadsafeQueue<T>::begin() {
    return this->_queue.begin();
}

template <typename T>
auto ThreadsafeQueue<T>::end() {
    return this->_queue.end();
}

template <typename T>
bool ThreadsafeQueue<T>::empty() {
    std::lock_guard<std::mutex> guard(this->_queueMutex);
    return this->_queue.empty();
}

template <typename T>
using sharedTSQueue = std::shared_ptr<ThreadsafeQueue<T>>;

}  // namespace bookchain
