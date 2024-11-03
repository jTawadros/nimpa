#include "../include/renderer.h"

void Renderer::initialize() {
  initscr();
  cbreak();             // Disable line buffering
  noecho();             // Don't echo pressed keys
  keypad(stdscr, TRUE); // Enable special keys capture
  curs_set(1);          // Show the cursor
}

void Renderer::draw(const std::string &buffer, int cursor_position) {
  clear();

  int x = 0, y = 0;
  int cursor_x = 0, cursor_y = 0;

  for (size_t i = 0; i < buffer.size(); ++i) {
    char ch = buffer[i];
    if (ch == '\n') {
      y++;
      x = 0;
    } else {
      mvaddch(y, x, ch);
      x++;
    }

    if (static_cast<int>(i) == cursor_position - 1) {
      cursor_x = x;
      cursor_y = y;
    }
  }

  move(cursor_y, cursor_x);
  refresh();
}

void Renderer::cleanup() { endwin(); }

int Renderer::getInput() { return getch(); }
