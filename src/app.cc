#include "../include/app.h"

void App::start(){
    // Init renderer
    renderer.initialize();

    bool running = true;
    while(running) {
        running = handleInput();
        renderer.draw(gapBuffer.getBuffer(), gapBuffer.get_cursor(), gapBuffer);

    }

    renderer.cleanup();
}

void App::openFile(const std::string& fileName){
    std::ifstream inFile(fileName);
    if(inFile) {
        File_Here = fileName;
        std::string fileContent;
        char ch;
        while (inFile.get(ch)) {
            fileContent += ch;
        }

        inFile.close();
        for (char a : fileContent) {
            gapBuffer.insert(a);
        }

    }else {
        std::ofstream outFile(fileName);

        if (outFile) {
            File_Here = fileName;
            outFile.close();
        } else {
            std::cerr << "Could not create the file: " << fileName << std::endl;
        }

    }
}

void App::saveFile() {

    std::ofstream outFile(File_Here);
    if (outFile) {
        char* buffer = gapBuffer.getBuffer();
        std::string test = gapBuffer.getBuffer();

        for (size_t i = 0; i < test.size(); ++i) {
            outFile << buffer[i];
        }
        outFile.close();
        std::cout << "File saved: " << File_Here << std::endl;

    } else {
        std::cerr << "Error: Could not save file: " << File_Here << std::endl;
    }


}

bool App::handleInput(){
    int ch = renderer.getInput();
    switch (ch) {

        // Key_Left
        case 260:
            gapBuffer.move_cursor_left();
            return true;
            break;

        // Key_Right
        case 261:
            gapBuffer.move_cursor_right();
            return true;
            break;

        // Key_Up
        case 259:
            gapBuffer.move_cursor_up(renderer.getColumns());
            return true;

        // Key_Down
        case 258:
            gapBuffer.move_cursor_down(renderer.getColumns());
            return true;
            break;

        // KEY_BACKSPACE
        case 127:
            gapBuffer.remove_at_cursor();
            return true;

        case 10:
            gapBuffer.insert('\n');
            return true;
        case KEY_F(1):
            renderer.cleanup();
            return false;
            break;

        case KEY_F(2):
            saveFile();
            return true;
            break;

        default:
            if (ch >= 32 && ch <= 126) {
                gapBuffer.insert(ch);
            }
            return true;
            break;
    }

}
