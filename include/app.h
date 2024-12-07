#ifndef APP_H
#define APP_H

#include "gap_buffer.h"
#include "renderer.h"
#include <string>

class App {
public:
  void start();
  void openFile(const std::string &fileName);

private:
  bool handleInput();
  void saveFile();
  void showSearchBar();

  Renderer renderer;
  GapBuffer gapBuffer;
  std::string file_here;
  int top_line = 0;
};

#endif // APP_H
