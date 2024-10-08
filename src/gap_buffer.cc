#include "../include/gap_buffer.h"
#include <iostream>
#include <cstring>

GapBuffer::GapBuffer(int buffer_size)
    : buffer(nullptr), gap_left(0), gap_right(9), buffer_size(buffer_size) {
        buffer = new char[buffer_size];
        lineStarts.push_back(0);
    }

GapBuffer::~GapBuffer(){
    delete [] buffer; // free memory
}

void GapBuffer::grow(){
    int new_size = buffer_size * 2;
    char* temp = new char[new_size];

    // place characters 
    for(int i = 0; i < gap_left; i++){
        temp[i] = buffer[i];
    }

    // set gap

    int new_gap_right_start = new_size - (buffer_size - gap_right - 1);
    for(int i = gap_right + 1; i < buffer_size; i++){
        temp[new_gap_right_start + (i - gap_right - 1)] = buffer[i];
    }

    gap_right = new_gap_right_start - 1;


    delete[] buffer;
    buffer = temp;
    buffer_size = new_size;
}

char* GapBuffer::getBuffer() const {
    char* temp = new char[buffer_size];
    int index = 0;

    // Copy characters from the left side of 
    // the gap
    for(int i = 0; i < gap_left; i++){
        temp[index] = buffer[i];
        index++;
    }

    // Copy characters from after the gap.
    for(int i = gap_right + 1; i < buffer_size; i++){
        temp[index] = buffer[i];
        index++;
    }

    // String terminate with null.
    temp[index] ='\0';

    return temp;
}

void GapBuffer::insert(char input){

    if (gap_right == gap_left){
        // Double the size 
        grow();
    }

    // insert in the correct position.
    buffer[gap_left] = input;

    if(input == '\n') addNewLine(gap_left);

    gap_left++;

}

void GapBuffer::addNewLine(int position){
    lineStarts.push_back(position);
}

int GapBuffer::getLineFromBuffer(int position) const {
    for (size_t i = 0; i < lineStarts.size(); ++i) {
        if (lineStarts[i] > position) {
            return i - 1;
        }
    }
    return lineStarts.size() - 1;
}

int GapBuffer::getLineStart(size_t lineIndex) const {
    return lineStarts[lineIndex];
}

void GapBuffer::removeLine(size_t lineIndex) {
    if (lineIndex >= 0 && lineIndex < lineStarts.size()) {
        lineStarts.erase(lineStarts.begin() + lineIndex);
    }
}

void GapBuffer::left(int position){
    while(gap_left > position){
        gap_left--;
        buffer[gap_right] = buffer[gap_left];
        gap_right--;

    }
}

void GapBuffer::right(int position){
    while(position > gap_left && gap_right < buffer_size - 1){
        gap_left++;
        gap_right++;
        buffer[gap_left - 1] = buffer[gap_right];

    }
}

void GapBuffer::move_cursor_left(){
    if (gap_left > 0){
        // Adjust the gap left
        left(gap_left - 1);
    }
}

void GapBuffer::move_cursor_right(){
    if(gap_right < buffer_size - 1){
        // Adjust the gap right
        right(gap_left + 1);
    }

}

void GapBuffer::move_cursor_up() {
    // Determine the current line number based on gap_left
    int currentLine = getLineFromBuffer(gap_left);

    // Only move up if not on the first line
    if (currentLine > 0) {
        // Get the start of the current line and the previous line
        int currentLineStart = getLineStart(currentLine);
        int previousLineStart = getLineStart(currentLine - 1);

        // Calculate the current column within the line
        int currentColumn = gap_left - currentLineStart;

        // Calculate the target position in the previous line
        int previousLineLength = getLineEnd(currentLine - 1) - previousLineStart;
        int targetPosition = previousLineStart + std::min(currentColumn, previousLineLength);

        // Move left until we reach the target position
        while (gap_left > targetPosition) {
            move_cursor_left();  // Use the existing left movement logic
        }
    }
}



void GapBuffer::move_cursor_down(){

    size_t currentLine = getLineFromBuffer(gap_left);

    if (currentLine < lineStarts.size() - 1) {
        int currentLineStart = getLineStart(currentLine);
        int nextLineStart = getLineStart(currentLine + 1);

        int currentColumn = gap_left - currentLineStart;

        int nextLineLength = getLineEnd(currentLine + 1) - nextLineStart;
        int targetPos = nextLineStart + std::min(currentColumn, nextLineLength);

        while (gap_left < targetPos) {
            move_cursor_right();
        }
    }
}

void GapBuffer::remove_at_cursor(){
    if(gap_left > 0) {
        gap_left--;


        if(buffer[gap_left] == '\n') {
            int lineToRemove = getLineFromBuffer(gap_left);
            removeLine(lineToRemove);
        }
    }
}
int GapBuffer::get_cursor(){
    return gap_left;
}

int GapBuffer::getLineEnd(size_t currentLine) {
    // If the current line is the last line, the end is at gap_right or buffer_size - 1
    if (currentLine + 1 >= lineStarts.size()) {
        return buffer_size - 1;  // Last character in the buffer
    } else {
        // Otherwise, it's the position just before the start of the next line
        return getLineStart(currentLine + 1) - 1;
    }
}

