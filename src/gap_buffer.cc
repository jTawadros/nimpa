#include "../include/gap_buffer.h"
#include <iostream>
#include <cstring>

GapBuffer::GapBuffer(int buffer_size, int gap_size)
    : buffer_size(buffer_size), gap_size(gap_size), gap_left(0), gap_right(gap_size-1) {
        buffer = new char[buffer_size];

        for(int i = 0; i < buffer_size; i++){
            buffer[i] = "_";
        }
    }

GapBuffer::~GapBuffer(){
    delete [] buffer; // free memory
}

void GapBuffer::grow(int position){
    int new_size = buffer_size * 2
    char* temp = new char[buffer_size];

    // place characters 
    for(int i = position; i < new_size; i++){
        a[i - position] = buffer[i];
    }

    // set gap
    int new_gap_size = new_size - buffer_size + 1;


    int gap_offset = new_size - (buffer_size - gap_right - 1);
    for(int i = gap_right + 1; i < buffer_size; i++){
        temp[gap_offset - (i - gap_right - 1)] = buffer[i];
    }

    gap_right = gap_left + new_gap_size - 1;


    delete[] buffer;
    buffer = temp;
    buffer_size = new_size;
}
