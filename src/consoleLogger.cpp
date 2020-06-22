//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "consoleLogger.h"

ConsoleLogger::ConsoleLogger() : _messageQueue{make_unique<MessageQueue<string>>()} {
    
}

void ConsoleLogger::Run() {
    while (_running || !_messageQueue->IsEmpty()) {
        std::cout << _messageQueue->Receive() << std::endl;
    }
}

void ConsoleLogger::Log(string logMessage) {
    _messageQueue->Send(std::move(logMessage));
}

void ConsoleLogger::IsRunning(bool running) {
    _running = running;
}
