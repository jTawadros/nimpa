#include "../include/renderer.h"
#include <ncurses.h>


void Renderer::initialize() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void Renderer::draw(){
    clear();
    // Draw stuff
    refresh();
}

void Renderer::cleanup() {
    endwin();
}

int Renderer::getInput() {
    return getch();
}
