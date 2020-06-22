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

using std::unique_ptr;
using std::make_unique;
using std::string;

class ConsoleLogger {
public:
    ConsoleLogger();
    // run the loop which constantly checks for messages to print.
    void Run();
    // send the message you wish to log.
    void Log(string logMessage);
    // used to keep track of running loop.
    void IsRunning(bool running);
private:
    // ptr to message queue for incoming and outgoing messages.
    unique_ptr<MessageQueue<string>> _messageQueue;
    // keeps track of whether loop should continue.
    bool _running{true};
};

#endif//PONG_GAME_CONSOLE_LOGGER_H
