#include "../include/app.h"

void App::start(){
    // Init renderer

    bool running = true;
    while(running) {
        running = handleInput();
        renderer.draw();
    }

    renderer.cleanup();
}

bool App::handleInput(){
    int ch = renderer.getInput();

    switch (ch) {
        case KEY_LEFT:
            gapBuffer.move_cursor_left();
            return true;
            break;
        case KEY_RIGHT:
            gapBuffer.move_cursor_right();
            return true;
            break;
        case KEY_F(1):
            return false;
            break;
        default:
            if (ch >= 32 && ch <= 126) {
                gapBuffer.insert(ch);
            }
            return true;
            break;
    }
}
