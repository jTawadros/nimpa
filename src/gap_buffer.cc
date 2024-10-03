#include "../include/gap_buffer.h"
#include <iostream>
#include <cstring>

GapBuffer::GapBuffer(int buffer_size, int gap_size)
    : buffer_size(buffer_size), gap_size(gap_size), gap_left(0), gap_right(gap_size-1) {
        buffer = new char[buffer_size];
    }

GapBuffer::~GapBuffer(){
    delete [] buffer; // free memory
}

void GapBuffer::grow(int position){
    int new_size = buffer_size * 2;
    char* temp = new char[buffer_size];

    // place characters 
    for(int i = position; i < new_size; i++){
        temp[i - position] = buffer[i];
    }

    // set gap
    int new_gap_size = new_size - buffer_size;


    int gap_offset = new_size - (buffer_size - gap_right - 1);
    for(int i = gap_right + 1; i < buffer_size; i++){
        temp[gap_offset - (i - gap_right - 1)] = buffer[i];
    }

    gap_right = gap_left + new_gap_size - 1;


    delete[] buffer;
    buffer = temp;
    buffer_size = new_size;
}

const char* GapBuffer::getBuffer() {
    static char temp[buffer_size] = buffer;
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
        grow(gap_left);
    }

    // insert in the correct position.
    buffer[gap_left] = input;
    gap_left++;

}

void GapBuffer::left(int position){
    while(position < gap_left){
        gap_left--;
        gap_right--;
        buffer[gap_right+1] = buffer[gap_left];
    }
}

void GapBuffer::right(int position){
    while(position < gap_left){
        gap_left++;
        gap_right++;
        buffer[gap_left-1] = buffer[gap_right];
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
        right(gap_right + 1);
    }

}

// void GapBuffer::move_cursor_left(int position){
// 
// }
// 
// void GapBuffer::move_cursor_left(int position){
// 
// }
