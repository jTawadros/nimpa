#ifndef RENDERER_H
#define RENDERER_H

#include<ncurses.h>

class Renderer {
    public:
        void initialize();
        void draw(const char* buffer);
        void cleanup();
        int getInput();
};

#endif
