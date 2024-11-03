#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>
#include <string>

class Renderer {
public:
    void initialize();
    void draw(const std::string& buffer, int cursor_position);
    void cleanup();
    int getInput();
};

#endif // RENDERER_H

