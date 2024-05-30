#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "getch.h"
#include "colorPrint.h"
#include "mineSweeper.h"

//initiate the board game
bool initBoard(GameBoard *g, int rows, int cols, int level) {
    if(rows > 20){
        rows = 20;
    }
    if(rows <= 0){
        rows = 4;
    }
    if(cols > 20){
        cols = 20;
    }
    if(cols <= 0){
        cols = 4;
    }
    if(level > 3 || level < 1){
        level = 1;
    }

    g->rows = rows;
    g->cols = cols;
    g->hiddenTiles = (cols*rows);
    g->isMineClicked = FALSE;
    g->board = (Tile**) malloc(sizeof(Tile *) * rows);
    if (g->board == NULL)
        return FALSE;
    for (int i = 0; i < rows; i++) {
        g->board[i] = (Tile*) malloc(sizeof(Tile) * cols);
        if (g->board[i] == NULL)
            return FALSE;
        for (int j = 0; j < cols; j++) {
            g->board[i][j].isVisible = FALSE;
            g->board[i][j].numOfMines = 0;
            g->board[i][j].isMine = FALSE;
            g->board[i][j].isFlagged = FALSE;
        }
    }
    populateMines(g, level);
    markNumbers(g);
    return TRUE;
}

/**
 * set the mines randomly 
 **/
void populateMines(GameBoard *g, int level){
    int temp = (g->rows) * (g->cols);
        //level precent seting
        switch(level){
            case EASY:
                g->totalMines = (int)((EASY_LEVEL_PERCENT*temp)/100);
                break;
            case MEDIUM:
                g->totalMines = (int)((MEDIUM_LEVEL_PERCENT*temp)/100);
                break;
            case HARD:
                g->totalMines = (int)((HARD_LEVEL_PERCENT*temp)/100);
                break;
        }
        //seting ramdom mines in the board 
        int totalTemp = g->totalMines; //used as a counter
        int rand1;
        int rand2;
        while(totalTemp > 0){
            rand1 = rand() % g->rows; 
            rand2 = rand() % g->cols;
            if(g->board[rand1][rand2].isMine == FALSE){
                g->board[rand1][rand2].isMine = TRUE;
                g->board[rand1][rand2].numOfMines = - 1;
                totalTemp --;
            }
        }
    }

/**
 * a function that gets the board and 2 numbers and checks if the number givin is out of board
 **/
bool outOfBoard(GameBoard *g, int i, int j){
    if((i >= (g->rows)) || (i < 0) || (j < 0) || (j >= (g->cols))){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/**
 * a function that mark every tile how many mine there is araund the Tile
 **/
void markNumbers(GameBoard *g){
    int row = g->rows;
    int col = g->cols;
    //go on all the matrix
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            //if the current tile is a mine we do nothing
            if(g->board[i][j].isMine == TRUE){
                continue;
            }
            //else we check every tile araund him
            if(outOfBoard(g, i + 1, j) == FALSE){
                if(g->board[i + 1][j].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
            if(outOfBoard(g, i + 1, j + 1) == FALSE){
                if(g->board[i + 1][j + 1].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
            if(outOfBoard(g, i, j + 1) == FALSE){
                if(g->board[i][j + 1].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
            if(outOfBoard(g, i - 1, j) == FALSE){
                if(g->board[i - 1][j].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
            if(outOfBoard(g, i - 1, j - 1) == FALSE){
                if(g->board[i - 1][j - 1].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
            if(outOfBoard(g, i, j - 1) == FALSE){
                if(g->board[i][j - 1].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
            if(outOfBoard(g, i - 1, j + 1) == FALSE){
                if(g->board[i - 1][j + 1].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
            if(outOfBoard(g, i + 1, j - 1) == FALSE){
                if(g->board[i + 1][j - 1].numOfMines == -1){
                    g->board[i][j].numOfMines ++;
                }
            }
        }
    }
}


void clickTile(GameBoard *g, int row, int col){
    //if the current tile is visible
    if(g->board[row][col].isVisible == TRUE){
        return;
    }
    //if the current tile was alredy flagged
    if(g->board[row][col].isFlagged == TRUE){
        return;
    }
    //if the current tile is not visible and not flagged
    if(g->board[row][col].isVisible == FALSE){
        //if the current tile is mine
        if(g->board[row][col].isMine == TRUE){
            g->isMineClicked = TRUE;
            return;
        }
        //if the current tile as mines around him
        else if(g->board[row][col].numOfMines > 0){
            g->board[row][col].isVisible = TRUE;
            g->hiddenTiles--;
            return;
        }
        //if the current tile is empty
        else if(g->board[row][col].numOfMines == 0){
            g->board[row][col].isVisible = TRUE;
            g->hiddenTiles--;
            if(outOfBoard(g, row + 1, col) == FALSE){
                clickTile(g, row + 1, col);
            }
            if(outOfBoard(g, row + 1, col + 1) == FALSE){
                clickTile(g, row + 1, col + 1);
            }
            if(outOfBoard(g, row ,col + 1) == FALSE){
                clickTile(g, row, col + 1);
            }
            if(outOfBoard(g, row - 1, col) == FALSE){
                clickTile(g, row - 1, col);
            }
            if(outOfBoard(g, row - 1, col - 1) == FALSE){
                clickTile(g, row - 1, col - 1);
            }
            if(outOfBoard(g, row, col - 1) == FALSE){
                clickTile(g, row, col - 1);
            }
            if(outOfBoard(g, row - 1, col + 1) == FALSE){
                clickTile(g, row - 1, col + 1);
            }
            if(outOfBoard(g, row + 1, col - 1) == FALSE){
                clickTile(g, row + 1, col - 1);
            }
        }
    }
}

/**
 * a function that marks and dismarks as flag hiddenTiles
 **/
void flagTile(GameBoard *g, int row, int col){
    //if is visible
    if(g->board[row][col].isVisible == TRUE){
        return;
    }
    //else if flaged
    else if(g->board[row][col].isFlagged == TRUE){
        g->board[row][col].isFlagged = FALSE;
    }
    //if not flaged
    else if(g->board[row][col].isFlagged == FALSE){
        g->board[row][col].isFlagged = TRUE;
    }
}

/**
 * a function that prints the board
 **/
void printBoard(GameBoard *g, int cursorCoords[2]){
    for (int i = 0; i < g->rows; i++){
        char c[2];
        for (int j = 0; j < g->cols; j++) {
            //print the pointer
            if(i == cursorCoords[0] && j == cursorCoords[1]){
                if(g->board[i][j].isFlagged == TRUE)//if its flagged
                    colorPrint(FG_Black, BG_Red, ATT_Def, " F");
                else if(g->board[i][j].isVisible && g->board[i][j].numOfMines > 0){
                    c[0] = (char)(g->board[i][j].numOfMines + 48);
                    c[1] = ' ';
                    colorPrint(FG_Black, BG_Green, ATT_Def, c);
                }
                else
                    colorPrint(FG_Green, BG_Green, ATT_Def, "  ");
            }
            //if the current location not visible
            else if(g->board[i][j].isVisible == FALSE){
                if(g->board[i][j].isFlagged == TRUE)//if its flagged
                    colorPrint(FG_Black, BG_Red, ATT_Def, " F");
                else
                    colorPrint(FG_Yellow, BG_Yellow, ATT_Def, "  ");
            }
            //if the current location is visible
            else{
                //if there are mines araund him
                if(g->board[i][j].numOfMines > 0){
                    c[0] = (char)(g->board[i][j].numOfMines + 48);
                    c[1] = ' ';
                    //sprintf((char)charNum, "%d", num);
                    colorPrint(FG_Black, BG_White, ATT_Def, c);
                }
                else{
                    colorPrint(FG_White, BG_White, ATT_Def, "  ");
                }
            }
        }
        printf("\n");
    }
}



