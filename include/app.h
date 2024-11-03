#ifndef APP_H
#define APP_H

#include "renderer.h"
#include "gap_buffer.h"
#include <string>

class App {
public:
    void start();
    void openFile(const std::string& fileName);

private:
    bool handleInput();
    void saveFile();

    Renderer renderer;
    GapBuffer gapBuffer;
    std::string file_here;
};

#endif // APP_H

