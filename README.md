# Minesweeper Game

## Introduction

This project is a console-based implementation of the classic Minesweeper game in C. It provides an interactive gameplay experience with customizable board dimensions and difficulty levels.

## Files

1. **main.c:** Contains the main function to run the Minesweeper game.
2. **mineSweeper.h:** Header file defining the structures and function prototypes for the Minesweeper game logic.
3. **mineSweeper.c:** Source file implementing the Minesweeper game logic functions.
4. **getch.h:** Header file providing functions for non-blocking keyboard input.
5. **colorPrint.h:** Header file defining functions for color printing in the console.
6. **colorPrint.c:** Source file implementing color printing functions using ANSI escape codes.

## Features

- Dynamic board generation based on user-defined rows, columns, and difficulty level.
- Random mine placement with adjustable difficulty levels: Easy, Medium, and Hard.
- Interactive gameplay with cursor movement and tile revealing.
- Flagging mechanism to mark potential mine locations.
- Colorful output using ANSI escape codes for enhanced user experience.

## Usage

1. **Compilation:** Compile the source code files using a C compiler, such as GCC.
   gcc main.c mineSweeper.c getch.c colorPrint.c -o minesweeper
   
2. **Execution:** Run the compiled executable to start the game.
   ./minesweeper

3. **Gameplay Controls:**
   - Use arrow keys (Up, Down, Left, Right) to move the cursor.
   - Press Spacebar to reveal a tile.
   - Press Enter to flag or unflag a tile as a potential mine.
   - Press Q to quit the game.

## Instructions

1. Choose the level of difficulty (1 for Easy, 2 for Medium, 3 for Hard).
2. Enter the number of rows and columns for the game board.
3. Use arrow keys to navigate the cursor and Spacebar to reveal tiles.
4. Flag tiles suspected to contain mines by pressing Enter.
5. Clear all non-mine tiles to win the game.
6. Avoid clicking on mines to prevent game over.

## Dependencies

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
- External header files: `getch.h`, `colorPrint.h`, `mineSweeper.h`
