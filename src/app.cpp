#include "../include/app.h"
#include "../include/aho_corasick.h"
#include <fstream>
#include <ncurses.h>
#include <vector>
#include <algorithm>

void App::start() {
  renderer.initialize();
  bool running = true;
  while (running) {
    renderer.draw(gapBuffer.getBuffer(), gapBuffer.get_cursor(), top_line);
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
  int current_line = gapBuffer.get_line_from_buffer(gapBuffer.get_cursor());

  if (ch == 6) { // Ctrl - F
    showSearchBar();
    return true;
  }

  switch (ch) {
  case KEY_LEFT:
    gapBuffer.move_cursor_left();
    break;
  case KEY_RIGHT:
    gapBuffer.move_cursor_right();
    break;
  case KEY_UP:
    gapBuffer.move_cursor_up();
    if (current_line <= top_line && top_line > 0) {
      top_line--;
    }
    break;
  case KEY_DOWN:
    gapBuffer.move_cursor_down();
    if (current_line >= top_line + LINES - 1) {
      top_line++;
    }
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

void App::showSearchBar() {
  // Create a small subwindow at the bottom of the screen
  int height = 1;
  int width = COLS;
  int starty = LINES - 1;
  int startx = 0;

  WINDOW *search_win = newwin(height, width, starty, startx);
  // optional: box(search_win, 0, 0);
  wmove(search_win, 0, 0);
  wprintw(search_win, "Search (use '\\' to separate patterns): ");
  wrefresh(search_win);

  echo();
  curs_set(1);

  char query[256];
  wgetnstr(search_win, query, 255);

  noecho();
  curs_set(0);
  werase(search_win);
  wrefresh(search_win);
  delwin(search_win);

  std::string pattern_line(query);
  // Split by backslash '\'
  std::vector<std::string> patterns;
  {
    size_t start = 0, end;
    while ((end = pattern_line.find('\\', start)) != std::string::npos) {
      std::string p = pattern_line.substr(start, end - start);
      if (!p.empty())
        patterns.push_back(p);
      start = end + 1;
    }
    // Add the last pattern after the last '\', if any
    if (start < pattern_line.size()) {
      std::string p = pattern_line.substr(start);
      if (!p.empty())
        patterns.push_back(p);
    }
  }

  if (patterns.empty()) {
    mvprintw(LINES - 1, 0, "No patterns entered.");
    refresh();
    return;
  }

  // Run Aho-Corasick search with multiple patterns
  AhoCorasick aho;
  aho.build(patterns);
  std::string text = gapBuffer.getBuffer();
  auto matches = aho.search(text);

  // Build a result file with matches
  std::ofstream outFile("search_results.txt");
  if (!outFile) {
    // If fail to open file
    mvprintw(LINES - 1, 0, "Could not write to search_results.txt");
    refresh();
    return;
  }

  // Preprocessing lines: find line offsets
  std::vector<int> line_offsets;
  line_offsets.push_back(0);
  for (int i = 0; i < (int)text.size(); i++) {
    if (text[i] == '\n') {
      line_offsets.push_back(i + 1);
    }
  }

  // Output all matches
  // For each match: pattern_id, position
  // Convert position to line number and print line
  for (auto &match : matches) {
    int pid = match.first;
    int pos = match.second;
    // Find line for pos
    int line_idx =
        (int)(std::upper_bound(line_offsets.begin(), line_offsets.end(), pos) -
              line_offsets.begin()) -
        1;
    if (line_idx < 0)
      line_idx = 0;

    int start_line = line_offsets[line_idx];
    int end_line = (line_idx + 1 < (int)line_offsets.size())
                       ? line_offsets[line_idx + 1] - 1
                       : (int)text.size();
    std::string line = text.substr(start_line, end_line - start_line);

    outFile << "Pattern \"" << patterns[pid] << "\" found at line "
            << (line_idx + 1) << ": " << line << "\n";
  }

  outFile.close();

  mvprintw(LINES - 1, 0, "Results saved to search_results.txt");
  refresh();
}
