# Makefile for NimPad text editor

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Source files
SRC = src/main.cc src/app.cc src/renderer.cc src/gap_buffer.cc

# Output executable
OUTPUT = nimp

# Default target to build the executable
all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC) -lncurses

# Clean up compiled files
clean:
	rm -f $(OUTPUT)

