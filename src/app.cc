#include "../include/app.h"

void App::start(){
    // Init renderer

    bool running = true;
    while(running) {
        handleInput();
        renderer.draw();
    }

    renderer.cleanup();
}

void App::handleInput(){
    int ch = renderer.getInput();
}
