#ifndef APP_H
#define APP_H

#include "renderer.h"

class App {
    public:
        void start();
    private:
        Renderer renderer;
        void handleInput();

};

#endif // APP_H
