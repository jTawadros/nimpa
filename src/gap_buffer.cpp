#include "../include/gap_buffer.h"
#include <algorithm> // For std::min
#include <cstring>

GapBuffer::GapBuffer(int buffer_size)
    : buffer_size(buffer_size), gap_left(0), gap_right(buffer_size - 1) {
  buffer = new char[buffer_size];
  std::fill(buffer, buffer + buffer_size, '\0');
  line_starts.push_back(0);
}

GapBuffer::~GapBuffer() { delete[] buffer; }

void GapBuffer::grow() {
  int new_size = buffer_size * 2;
  char *new_buffer = new char[new_size];
  std::fill(new_buffer, new_buffer + new_size, '\0');

  // Copy data before the gap
  std::memcpy(new_buffer, buffer, gap_left);

  // Copy data after the gap
  int data_after_gap = buffer_size - gap_right - 1;
  std::memcpy(new_buffer + new_size - data_after_gap, buffer + gap_right + 1,
              data_after_gap);

  gap_right = new_size - data_after_gap - 1;
  buffer_size = new_size;

  delete[] buffer;
  buffer = new_buffer;
}

std::string GapBuffer::getBuffer() const {
  std::string result;
  result.reserve(buffer_size - (gap_right - gap_left + 1));

  for (int i = 0; i < gap_left; ++i) {
    result += buffer[i];
  }
  for (int i = gap_right + 1; i < buffer_size; ++i) {
    result += buffer[i];
  }
  return result;
}

void GapBuffer::insert(char input) {
  if (gap_left > gap_right) {
    grow();
  }

  if (input == '\n') {
    int new_line_start = gap_left;
    line_starts.insert(std::upper_bound(line_starts.begin(), line_starts.end(),
                                        new_line_start),
                       new_line_start);
  }
  buffer[gap_left++] = input;
}

void GapBuffer::add_new_line(int position) {
  line_starts.push_back(position + 1);
}

int GapBuffer::get_line_from_buffer(int position) const {
  for (size_t i = 0; i < line_starts.size(); ++i) {
    if (line_starts[i] > position) {
      return i - 1;
    }
  }
  return line_starts.size() - 1;
}

int GapBuffer::get_line_start(size_t lineIndex) const {
  if (lineIndex < line_starts.size()) {
    return line_starts[lineIndex];
  }
  return -1;
}

int GapBuffer::get_line_end(size_t lineIndex) const {
  if (lineIndex + 1 < line_starts.size()) {
    return line_starts[lineIndex + 1] -
           2; // -2 because of zero-based index and excluding newline
  } else {
    // Last line
    int total_length = gap_left + (buffer_size - gap_right - 1);
    return total_length - 1;
  }
}

void GapBuffer::remove_line(size_t lineIndex) {
  if (lineIndex < line_starts.size()) {
    line_starts.erase(line_starts.begin() + lineIndex);
  }
}

void GapBuffer::move_gap_left(int position) {
  while (gap_left > position) {
    gap_left--;
    buffer[gap_right--] = buffer[gap_left];
    buffer[gap_left] = '\0';

    for (size_t i = 0; i < line_starts.size(); ++i) {
      if (line_starts[i] == gap_left) {
        line_starts[i] = gap_right + 1;
      } else if (line_starts[i] > gap_left) {
        line_starts[i]++;
      }
    }
  }
}

void GapBuffer::move_gap_right(int position) {
  while (gap_left < position && gap_right < buffer_size - 1) {
    buffer[gap_left++] = buffer[++gap_right];
    buffer[gap_right] = '\0';

    for (size_t i = 0; i < line_starts.size(); ++i) {
      if (line_starts[i] == gap_right) {
        line_starts[i] = gap_left - 1;
      } else if (line_starts[i] > gap_right) {
        line_starts[i]--;
      }
    }
  }
}

void GapBuffer::move_cursor_left() {
  if (gap_left > 0) {
    move_gap_left(gap_left - 1);
  }
}

void GapBuffer::move_cursor_right() {
  int total_length = gap_left + (buffer_size - gap_right - 1);
  if (gap_left < total_length) {
    move_gap_right(gap_left + 1);
  }
}

void GapBuffer::move_cursor_up() {
  int current_line = get_line_from_buffer(gap_left);
  if (current_line > 0) {
    int current_column = gap_left - get_line_start(current_line);
    int previous_line_start = get_line_start(current_line - 1);
    int previous_line_end = get_line_end(current_line - 1);
    int previous_line_length = previous_line_end - previous_line_start + 1;
    int target_position =
        previous_line_start + std::min(current_column, previous_line_length);

    move_gap_left(target_position);
  }
}

void GapBuffer::move_cursor_down() {
  int current_line = get_line_from_buffer(gap_left);
  if (current_line + 1 < static_cast<int>(line_starts.size())) {
    int current_column = gap_left - get_line_start(current_line);
    int next_line_start = get_line_start(current_line + 1);
    int next_line_end = get_line_end(current_line + 1);
    int next_line_length = next_line_end - next_line_start + 1;
    int target_position =
        next_line_start + std::min(current_column, next_line_length);

    move_gap_right(target_position);
  }
}

void GapBuffer::remove_at_cursor() {
  if (gap_left > 0) {
    gap_left--;

    if (buffer[gap_left] == '\n') {
      int line_to_remove = get_line_from_buffer(gap_left);
      line_starts.erase(line_starts.begin() + line_to_remove + 1);
    } else {
      for (size_t i = 0; i < line_starts.size(); ++i) {
        if (line_starts[i] > gap_left) {
          line_starts[i]--;
        }
      }
    }
  }
}

int GapBuffer::get_cursor() const { return gap_left; }
