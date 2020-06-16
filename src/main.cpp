#include <iostream>
#include <thread>
#include "game.h"
#include "controller.h"
#include "renderer.h"

using std::thread;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;

int main() {

    constexpr Uint32 framesPerSecond{144};
    constexpr Uint32 msPerFrame{1000 / framesPerSecond};
    constexpr size_t screenWidth{1024};
    constexpr size_t screenHeight{768};

    std::cout << "Initializing crazy nasty arse Pong game." << std::endl;

    // need shared paddles, controllers, ball, and renderer.
    
    // create paddles, attach to controllers.
    shared_ptr<Paddle> leftPaddle = make_shared<Paddle>(0, screenHeight / 2);
    shared_ptr<Paddle> rightPaddle = make_shared<Paddle>(screenWidth, screenHeight / 2);
    shared_ptr<Ball> ball = make_shared<Ball>(screenWidth / 2, screenHeight / 2, leftPaddle, rightPaddle);
    Renderer renderer(leftPaddle, rightPaddle, ball);

    Controller leftController(leftPaddle, msPerFrame,SDL_SCANCODE_W, SDL_SCANCODE_S);
    thread leftControllerThread = thread(&Controller::Control, &leftController);

    Controller rightController(rightPaddle, msPerFrame,SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
    thread rightControllerThread = thread(&Controller::Control, &rightController);

    Game game(leftPaddle, rightPaddle, ball, renderer);

    // this will quit once the game is no longer running so just set other objects to no longer run afterwards.
    game.RunLoop();

    rightController.IsRunning(false);
    rightControllerThread.join();
    
    leftController.IsRunning(false);
    leftControllerThread.join();

    return 0;
}
