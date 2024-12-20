#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <algorithm>
#include <string>
#include <vector>

class GapBuffer {
public:
  GapBuffer(int buffer_size = 50);
  ~GapBuffer();

  void insert(char input);
  std::string getBuffer() const;
  void move_cursor_left();
  void move_cursor_right();
  void move_cursor_up();
  void move_cursor_down();
  void remove_at_cursor();
  int get_cursor() const;
  int get_line_from_buffer(int position) const;
  void ensureTrailingLine();

private:
  void grow();                       // Grow the buffer
  void move_gap_left(int position);  // Move the gap left
  void move_gap_right(int position); // Move the gap right
  void add_new_line(int position);
  void remove_line(size_t lineIndex);

  int get_line_start(size_t lineIndex) const;
  int get_line_end(size_t lineIndex) const;

  int logical_to_buffer_index(int logical_pos) const;
  int buffer_index_to_logical(int buffer_index) const;

  char *buffer;
  int buffer_size;
  int gap_left;
  int gap_right;

  std::vector<int> line_starts;
};

#endif // GAP_BUFFER_H
