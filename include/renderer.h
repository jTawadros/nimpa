#ifndef RENDERER_H
#define RENDERER_H

#include "gap_buffer.h"
#include<ncurses.h>
#include<iostream>

class Renderer {
    public:
        void initialize();
        void draw(const char* buffer, int cursor_position, const GapBuffer& gapBuffer);
        void cleanup();
        int getInput();
        int getColumns();
};

#endif
