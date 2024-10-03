#include "../include/renderer.h"



void Renderer::initialize() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void Renderer::draw(const char* buffer){
    clear();
    for(int i = 0; buffer[i] != '\0'; ++i){
        addch(buffer[i]);
    }
    // Place cursor in the position used in the buffer.

    refresh();
}

void Renderer::cleanup() {
    // Deallocate all ncurses memory
    endwin();
}

int Renderer::getInput() {
    return getch();
}
