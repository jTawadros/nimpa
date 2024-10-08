# NIMPAD TEXT EDITOR

## Overview
NimPad is a terminal-based text editor built for efficiency and fast text manipulation. It utilizes the `ncurses` library for rendering and handling terminal input, providing a streamlined and lightweight editing environment.

## Current Features
- **Basic Text Editing**: You can write, edit, and delete text within a file.
- **Text Insertion**: Add text mid-file without overwriting existing content.
- **Line Tracking**: Navigate and edit across multiple lines efficiently with advanced line tracking capabilities.
- **Cursor Navigation**: Seamlessly move the cursor in all directions using arrow keys.
- **File Handling**: Create, save, and edit files now. Run the program using ./nimp filename.ext

## Recent Changes
- **Fully Modular Arrow Key Navigation**: Cursor movement is now fully modular, allowing you to move in all directions using the arrow keys, enhancing the editor's navigation capabilities.

## Data Structures
- **Gap Buffer**: NimPad uses a custom gap buffer implementation to efficiently manage text, particularly for insertions and deletions. This ensures minimal reallocation and provides fast editing even for large files.
- **Line Tracking**: An additional line tracking mechanism is implemented to facilitate efficient multi-line navigation and cursor positioning, improving the experience when working with larger documents.

## Controls
- **Arrow Keys**: Move the cursor up, down, left, and right.
- **Enter**: Add a new line.
- **Backspace**: Delete the character to the left of the cursor.
- **F1**: Quit the editor.
- **F2**: Save.
- **F3**: Save and Quit.

## Planned Features
- **Search Functionality**: Implementation of a search bar to easily find and replace text within the file.
- **Text Shortcuts**: Additional commands for more advanced text manipulation, such as copying, cutting, and pasting.
- **Syntax Highlighting**
- **Line Numbers**
- **Auto-Complete**: For code writing per language.
- **Custom Cursor**
- **Customization Options**







