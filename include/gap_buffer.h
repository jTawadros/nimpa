#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <string>

class GapBuffer {
    public:
        GapBuffer(int buffer_size = 50, int gap_size = 10);
        ~GapBuffer();

        void insert(char input, int position);
        std::string getBuffer() const; //returns the current getBuffer
    private:
        char* buffer;
        int gap_size;
        int gap_left;
        int gap_right;
        int buffer_size;

        void grow(int position);        // Grow the at position
        void move_cursor_left();
        void move_cursor_right();
        void left(int position);        // Move the gap left
        void right(int position);       // Move the gap right
        
};

#endif
