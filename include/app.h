#ifndef APP_H
#define APP_H

#include "renderer.h"
#include "gap_buffer.h"
#include <string.h>
#include <fstream>

class App {
    public:
        void start();
        void openFile(const std::string& fileName);
    private:
        Renderer renderer;
        GapBuffer gapBuffer;
        bool handleInput();
        void saveFile();
        std::string File_Here;

};

#endif // APP_H
