#include "../include/renderer.h"
#include <utility>

void Renderer::initialize() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
}

void Renderer::draw(const char* buffer, int cursor_position){
    clearok(stdscr, TRUE);
    clear();
    for(int i = 0; buffer[i] != '\0'; ++i){
        addch(buffer[i]);
    }
    // Place cursor in the position used in the buffer.
    int y = cursor_position / COLS;
    int x = cursor_position % COLS;

    move(y, x);

    refresh();
}

void Renderer::cleanup() {
    // Deallocate all ncurses memory
    endwin();
}

int Renderer::getInput() {
    int ch = getch();
    return ch;
}

int Renderer::getColumns(){
    return COLS;
}
