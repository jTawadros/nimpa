#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <string>
#include "line_tracker.h"

class GapBuffer {
    public:
        GapBuffer(int buffer_size = 50, int gap_size = 10);
        ~GapBuffer();

        void insert(char input);
        char* getBuffer() const; // Get char array without gap
        void move_cursor_left();
        void move_cursor_right();
        void move_cursor_up(int COLS);
        void move_cursor_down(int COLS);
        void remove_at_cursor();
        int get_cursor();
    private:
        char* buffer;
        int gap_size;
        int gap_left;
        int gap_right;
        int buffer_size;

        LineTracker lineTracker;

        void grow(int position);        // Grow the at position

        void left(int position);        // Move the gap left
        void right(int position);       // Move the gap right
        
};

#endif
