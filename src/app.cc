#include "../include/app.h"
#include <iostream>

void App::start(){
    // Init renderer
    renderer.initialize();

    bool running = true;
    while(running) {
        running = handleInput();
        renderer.draw(gapBuffer.getBuffer(), gapBuffer.get_cursor());
    }

    renderer.cleanup();
}

bool App::handleInput(){
    int ch = renderer.getInput();
    switch (ch) {
        case 260:
            gapBuffer.move_cursor_left();
            return true;
            break;
        case 261:
            gapBuffer.move_cursor_right();
            return true;
            break;
        case KEY_F(1):
            renderer.cleanup();
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
