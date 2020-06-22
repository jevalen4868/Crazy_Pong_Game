//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_CONSOLE_LOGGER_H
#define PONG_GAME_CONSOLE_LOGGER_H

#include <iostream>
#include <string>
#include "SDL.h"
#include "messageQueue.h"
#include "messageQueue.cpp"

using std::shared_ptr;
using std::string;

class ConsoleLogger {
public:
    ConsoleLogger(shared_ptr<MessageQueue<string>> &messageQueue);
    void Run();
    void Log(string logMessage);
    void IsRunning(bool running);
private:
    shared_ptr<MessageQueue<string>> _messageQueue;
    bool _running{true};
};

#endif//PONG_GAME_CONSOLE_LOGGER_H
