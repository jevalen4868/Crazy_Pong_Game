#include <iostream>
#include <thread>
#include <future>
#include "game.h"
#include "controller.h"
#include "renderer.h"
#include "consoleLogger.h"

using std::thread;
using std::shared_ptr;

using std::make_shared;
using std::unique_ptr;

int main() {
    // create paddles, attach to controllers.
    shared_ptr<ConsoleLogger> consoleLogger = make_shared<ConsoleLogger>();
    thread consoleLoggerThread = thread(&ConsoleLogger::Run, consoleLogger);

    consoleLogger->Log("APP STARTED");

    shared_ptr<Paddle> leftPaddle = make_shared<Paddle>(0, Cfg::screenHeight / 2);
    shared_ptr<Paddle> rightPaddle = make_shared<Paddle>(Cfg::screenWidth, Cfg::screenHeight / 2);
    shared_ptr<Ball> ball = make_shared<Ball>(Cfg::screenWidth / 2, Cfg::screenHeight / 2, leftPaddle, rightPaddle);
    Renderer renderer(leftPaddle, rightPaddle, ball);

    Controller leftController(leftPaddle, Cfg::sixtyMsPerUpdate, SDL_SCANCODE_W, SDL_SCANCODE_S, "Player 1");
    std::future<string> leftCtrlFtr = std::async(std::launch::async, &Controller::Control, &leftController);
    //thread leftControllerThread = thread(&Controller::Control, &leftController);

    Controller rightController(rightPaddle, Cfg::sixtyMsPerUpdate, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, "Player 2");
    std::future<string> rightCtrlFtr = std::async(std::launch::async, &Controller::Control, &rightController);
    //thread rightControllerThread = thread(&Controller::Control, &rightController);

    Game game(leftPaddle, rightPaddle, ball, renderer);

    // this will quit once the game is no longer running so just set other objects to no longer run afterwards.
    game.RunLoop();

    leftController.IsRunning(false);
    leftCtrlFtr.wait();
    consoleLogger->Log("Controller " + leftCtrlFtr.get() + " complete.");
    //leftControllerThread.join();

    rightController.IsRunning(false);
    rightCtrlFtr.wait();
    consoleLogger->Log("Controller " + rightCtrlFtr.get() + " complete.");
    //rightControllerThread.join();

    consoleLogger->Log("APP ENDING");

    consoleLogger->IsRunning(false);
    consoleLoggerThread.join();    

    return 0;
}
