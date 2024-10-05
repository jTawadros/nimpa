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

        // Key_Left
        case 260:
            gapBuffer.move_cursor_left();
            return true;
            break;

        // Key_Right
        case 261:
            gapBuffer.move_cursor_right();
            return true;
            break;

        // Key_Up
        case 259:
            gapBuffer.move_cursor_up(renderer.getColumns());
            return true;

        // Key_Down
        case 258:
            gapBuffer.move_cursor_down(renderer.getColumns());
            return true;
            break;

        // KEY_BACKSPACE
        case 263:
            gapBuffer.remove_at_cursor();
            return true;

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
