//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "messageQueue.h"

template<class T>
MessageQueue<T>::MessageQueue() {
}

template<class T>
T MessageQueue<T>::Receive() {
    // perform vector modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_messages.empty(); });// pass unique lock to condition variable

    // remove last vector element from queue
    T t = std::move(_messages.front());
    _messages.pop_front();

    return t;// will not be copied due to return value optimization (RVO) in C++
}

template<class T>
void MessageQueue<T>::Send(T &&t) {
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue    
    _messages.push_back(std::move(t));
    _cond.notify_one();// notify client after pushing new Vehicle into vector
}

template<class T>
bool MessageQueue<T>::IsEmpty() {
    return _messages.empty();
}
