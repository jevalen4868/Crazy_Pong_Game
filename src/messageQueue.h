//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_MSG_QUEUE_H
#define PONG_GAME_MSG_QUEUE_H

#include <mutex>
#include <deque>

template<class T>
class MessageQueue {
public:
    MessageQueue();
    T Receive();
    void Send(T &&t);

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _messages;
};

#endif//PONG_GAME_MSG_QUEUE_H
