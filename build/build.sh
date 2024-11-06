#!/bin/bash

# Function to check OS and install dependencies
install_dependencies() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if command -v apt &> /dev/null; then
            echo "Detected Ubuntu/Debian. Installing dependencies with apt..."
            sudo apt update
            sudo apt install -y build-essential libncurses5-dev libncursesw5-dev g++ make
        elif command -v dnf &> /dev/null; then
            echo "Detected Fedora. Installing dependencies with dnf..."
            sudo dnf install -y @development-tools ncurses-devel gcc-c++ make
        elif command -v pacman &> /dev/null; then
            echo "Detected Arch Linux. Installing dependencies with pacman..."
            sudo pacman -Syu --noconfirm base-devel ncurses gcc make
        else
            echo "Unsupported Linux distribution. Please install dependencies manually."
            exit 1
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "Detected macOS. Installing dependencies with Homebrew..."
        if ! command -v brew &> /dev/null; then
            echo "Homebrew not found. Please install it first: https://brew.sh/"
            exit 1
        fi
        brew install ncurses
    else
        echo "Unsupported OS. Please install dependencies manually."
        exit 1
    fi
}   

# Function to build nimpad
build_nimpad() {
    echo "Building nimpad..."
    if [[ -f "Makefile" ]]; then
        make
    else
        g++ ../src/*.cpp -I include -lncurses -o nimp
    fi
}

# Main script execution
echo "Starting setup for nimpad..."

install_dependencies
build_nimpad

echo "Setup complete! Run ./nimp <filename.ext> to start your application!"
