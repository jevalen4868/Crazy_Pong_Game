//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_MSG_QUEUE_H
#define PONG_GAME_MSG_QUEUE_H

#include <mutex>
#include <deque>

// udacity's fun yet simple impl of a message queue.
template<class T>
class MessageQueue {
public:
    MessageQueue();
    // request whatever object is defined as input at the front of the queue.
    T Receive();
    // send a message to the queue.
    void Send(T &&t);
    // check if underlying queue is empty.
    bool IsEmpty();
private:
    // controls access to the deque.
    std::mutex _mutex;
    // Control so the app waits to be notified there is new data by the Send function.
    std::condition_variable _cond;
    std::deque<T> _messages;
};

#endif//PONG_GAME_MSG_QUEUE_H
