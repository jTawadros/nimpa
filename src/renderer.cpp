#include "../include/renderer.h"
#include <ncurses.h>

void Renderer::initialize() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(1);
}

void Renderer::draw(const std::string &buffer, int cursor_position,
                    int top_line) {
  curs_set(0);

  int x = 0, y = 0;
  int cursor_x = 0, cursor_y = 0;

  int current_line = 0;

  for (int i = top_line; i < LINES + top_line; ++i) {
    move(y, 0);
    clrtoeol();
    y++;
  }

  x = 0;
  y = 0;
  current_line = 0;

  for (size_t i = 0; i < buffer.size(); ++i) {
    if (current_line >= top_line && y < LINES) {
      if(x == 0) {
        move(y, 0);
        clrtoeol();
      }
      char ch = buffer[i];
      if (ch == '\n') {
        y++; // Move to the next line
        x = 0;
        current_line++;
      } else {
        move(y, x);
        addch(ch);
        x++;
      }

      // Check if this position matches the cursor's position
      if (static_cast<int>(i) == cursor_position -1) {
        cursor_x = x;
        cursor_y = y;
      }

      if (y >= LINES - 1){
        break;
      }
    }
  }
  move(cursor_y, cursor_x);
  refresh();
  curs_set(1); // Show the cursor
}

void Renderer::cleanup() { endwin(); }

int Renderer::getInput() { return getch(); }
