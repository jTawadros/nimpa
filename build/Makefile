# Makefile for NimPad text editor

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Source files
SRC = ../src/main.cpp ../src/app.cpp ../src/renderer.cpp ../src/gap_buffer.cpp

# Output executable
OUTPUT = nimp

# Default target to build the executable
all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC) -lncurses

# Clean up compiled files
clean:
	rm -f $(OUTPUT)

