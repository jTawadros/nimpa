#include "../include/app.h"

int main(int argc, char* argv[]) {
    App app;

    if (argc > 1) {
        std::string fileName = argv[1];
        app.openFile(fileName);
    } else {
        std::cout << "Please use ./nimp filename.txt" << std::endl;
        return 1;
    }

    app.start();
    return 0;
}
