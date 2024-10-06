#include "../include/renderer.h"
#include <utility>

void Renderer::initialize() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
}

void Renderer::draw(const char* buffer, int cursor_position, const GapBuffer& gapBuffer) {
    // Clear the screen first
    clear();

    int x = 0, y = 0;

    // Render the buffer content
    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            // Move to the next line
            y++;
            x = 0;
        } else {
            mvaddch(y, x, buffer[i]);
            x++;
        }
    }

    // Calculate the actual cursor position based on `cursor_position`
    // Iterate through the buffer up to `cursor_position` to determine `(y, x)`
    x = 0;
    y = 0;
    for (int i = 0; i < cursor_position; ++i) {
        if (buffer[i] == '\n') {
            y++;
            x = 0;
        } else {
            x++;
        }
    }

    // Move the cursor to the calculated position
    move(y, x);

    // Refresh the screen to show changes
    refresh();
}


void Renderer::cleanup() {
    // Deallocate all ncurses memory
    endwin();
}

int Renderer::getInput() {
    return getch();
}

int Renderer::getColumns() {
    return COLS;
}

