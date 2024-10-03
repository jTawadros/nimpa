#ifndef APP_H
#define APP_H

#include "renderer.h"
#include "gap_buffer.h"

class App {
    public:
        void start();
    private:
        Renderer renderer;
        GapBuffer gapBuffer;
        bool handleInput();

};

#endif // APP_H
