#include "../include/app.h"
#include <fstream>
#include <ncurses.h>

void App::start() {
  renderer.initialize();
  bool running = true;
  while (running) {
    renderer.draw(gapBuffer.getBuffer(), gapBuffer.get_cursor());
    running = handleInput();
  }
  renderer.cleanup();
}

void App::openFile(const std::string &fileName) {
  std::ifstream inFile(fileName);
  if (inFile) {
    file_here = fileName;
    char ch;
    while (inFile.get(ch)) {
      gapBuffer.insert(ch);
    }
    inFile.close();
  } else {
    file_here =
        fileName; // Even if file doesn't exist, set the filename for saving
  }
}

void App::saveFile() {
  std::ofstream outFile(file_here);
  if (outFile) {
    std::string buffer = gapBuffer.getBuffer();
    outFile << buffer;
    outFile.close();
    mvprintw(LINES - 1, 0, "File saved: %s", file_here.c_str());
    refresh();
  } else {
    mvprintw(LINES - 1, 0, "Error: Could not save file: %s", file_here.c_str());
    refresh();
  }
}

bool App::handleInput() {
  int ch = renderer.getInput();

  switch (ch) {
  case KEY_LEFT:
    gapBuffer.move_cursor_left();
    break;
  case KEY_RIGHT:
    gapBuffer.move_cursor_right();
    break;
  case KEY_UP:
    gapBuffer.move_cursor_up();
    break;
  case KEY_DOWN:
    gapBuffer.move_cursor_down();
    break;
  case KEY_BACKSPACE:
  case 127: // Delete key
    gapBuffer.remove_at_cursor();
    break;
  case '\n':
    gapBuffer.insert('\n');
    break;
  case KEY_F(1):
    return false; // Exit
  case KEY_F(2):
    saveFile();
    break;
  case KEY_F(3):
    saveFile();
    return false; // Save and exit
  default:
    if (isprint(ch)) {
      gapBuffer.insert(static_cast<char>(ch));
    }
    break;
  }
  return true;
}
