#include "GameLoop.hpp"

using namespace warp;

GameLoop::GameLoop(std::function<void(void)> body_) : running(true), body(body_)
{
    
}

void GameLoop::run()
{
    while (running) body();
}

void GameLoop::onClosed()
{
    running = false;
}

void GameLoop::onKeyDown(Input::Key type)
{
    switch (type) {
        case Input::Key::Escape:
            running = false;
            break;
        default:
            break;
    }
}