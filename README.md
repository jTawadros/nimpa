# NIMPAD TEXT EDITOR

## Overview
This is a project I've created out of a passion to learn and create tools for deevelopers. This is, however, not a complete project. NimPad is sadly not ready to be your main text editor just yet. I would appreciate if you checked it out and potentially added improvements or suggestions.

## Warning: File Loading Limitation

Nimpad currently does not support automatic line wrapping. Please ensure that any files loaded into the editor contain manual line breaks (physical `\n`) where necessary. Files without these line breaks may result in text extending beyond the visible frame without wrapping.

If you're loading a file with code, it should generally be safe to load. However, if text extends past the screen, press `F1` to quit the editor.

*Note: Nimpad is a project focused on low-level terminal communication, built using `ncurses`. I'm a student working to deepen my understanding of terminal interfaces, so certain features are still under development.*

## Automatic Installation
To get started with NimPad, follow these steps:

1. **Clone  or Download the repository**:
   ```bash
   git clone https://github.com/jTawadros/nimpa
   ```
2. **Navigate to the NimPad build directory**
   ```bash
   cd nimpa/build
   ```
3. **Build NimPad**
   ```bash
   ./build.sh
   ```
4. **Run NimPad**
   ```bash
   ./nimp filename.ext
   ```
## Manual Installation
Before running Nimpad, ensure you have the following depndencies installed on your device!

### On Ubuntu/Debian
```bash
sudo apt update
sudo apt install ncurses-dev g++ make
```

### macOS with Homebrew
```bash
brew install ncurses
```

1. **Navigate to build directory**
    ```bash
    make
    ```
2. **Run NimPad**
    ```bash
   ./nimp filename.ext
    ```
## Controls
- **Arrow Keys**: Move the cursor up, down, left, and right.
- **Enter**: Add a new line.
- **Backspace**: Delete the character to the left of the cursor.
- **F1**: Quit the editor.
- **F2**: Save.
- **F3**: Save and Quit.
- **Ctrl-F**: Live grep multi-pattern search (Aho-Corasick)

## Current Features
- **Aho-Corasick Live grep search (main assignment functionality)**: Efficiently search for multiple patterns in the text at once using the Aho-Corasick algorithm. This feature allows you to specify search terms and returns all matches within the file, displaying their positions. The search is triggered by pressing Enter after typing the search query, ensuring accurate and responsive results. This implementation is optimized for multi-pattern searching, making it ideal for users who need to locate multiple keywords or phrases in a single operation!  
- **Basic Text Editing**: You can write, edit, and delete text within a file.
- **Text Insertion**: Add text mid-file without overwriting existing content.
- **Line Tracking**: Navigate and edit across multiple lines efficiently with advanced line tracking capabilities.
- **Cursor Navigation**: Move the cursor in all directions using arrow keys.
- **File Handling**: Create, save, and edit files now. Run the program using ./nimp filename.ext


## Recent Changes
- **Cursor movement Bug fix 1**: Fixed bug where moving cursor down forced cursor to end of file. 
- **Cursor movement Bug fix 2**: Fixed bug where moving cursor up would delete text and input random special characters.

## Data Structures
- **Gap Buffer**: NimPad uses a custom gap buffer implementation to efficiently manage text, particularly for insertions and deletions. This ensures minimal reallocation and provides fast editing even for large files.
- **Line Tracking**: An additional line tracking mechanism is implemented to facilitate efficient multi-line navigation and cursor positioning, improving the experience when working with larger documents.


## Planned Features
- **Live Grep search**: Using Aho-Corasick data structure, I plan to implement a grepping sort of feature using the unix fgrep as inspiration for code.
- **Text Shortcuts**: Additional commands for more advanced text manipulation, such as copying, cutting, and pasting.
- **Syntax Highlighting**
- **Line Numbers**
- **Custom Cursor**
- **Customization Options**







