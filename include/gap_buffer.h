#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <string>
#include <vector>

class GapBuffer {
    public:
        GapBuffer(int buffer_size = 50);
        ~GapBuffer();

        void insert(char input);
        char* getBuffer() const; // Get char array without gap
        void move_cursor_left();
        void move_cursor_right();
        void move_cursor_up();
        void move_cursor_down();
        void remove_at_cursor();
        int getLineStart(size_t lineIndex) const;
        int get_cursor();
        int getLineEnd(size_t currentLine);


        void addNewLine(int position);
        int getLineFromBuffer(int position) const;
        void removeLine(size_t lineIndex);

    private:
        char* buffer;
        // int gap_size;
        int gap_left;
        int gap_right;
        int buffer_size;

        void grow();        // Grow the at position
        void left(int position);        // Move the gap left
        void right(int position);       // Move the gap right

        std::vector<int> lineStarts;    // Vector to track new Lines
        
};

#endif
