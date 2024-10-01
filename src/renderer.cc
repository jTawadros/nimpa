#include "../include/renderer.h"
#include <ncurses.h>


void Renderer::initialize() {
    initscr();
    // do stuff
}

void Renderer::draw(){
    clear();
    // Draw stuff
    refresh();
}

void Renderer::cleanup() {
    endwin();
}
