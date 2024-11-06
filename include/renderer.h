#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>
#include <string>

class Renderer {
public:
    void initialize();
    void draw(const std::string& buffer, int cursor_position, int top_line);
    void cleanup();
    int getInput();
};

#endif // RENDERER_H

