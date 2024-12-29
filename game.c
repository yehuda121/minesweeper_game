#include <stdlib.h>
#include <stdio.h>
#include "mineSweeper.h"
#include "getch.h"
#include "colorPrint.h"

int main (){
    int rows, cols, level;
    GameBoard g;
    int xy[] = { 0, 0 };

    //getting the setings from the user
    printf("enter level: 1, 2, 3\n");
    scanf("%d", &level);
    printf("enter rows\n");
    scanf("%d", &rows);
    printf("enter cols\n");
    scanf("%d", &cols);
    my_getch();//remove \n from stdin buffer
    // getch();//remove \n from stdin buffer
    clearScreen();

    //initiatethe board
    initBoard (&g, rows, cols, level);
    
    char input;
    printBoard (&g, xy);
    while (1){
        if (g.isMineClicked == TRUE){
	        printf ("game over!!");
	        exit (1);
	    }
        if (g.totalMines == g.hiddenTiles){
	        printf ("you win!!");
	        exit (1);
	    }
        // input = getch();
        input = my_getch();
        if (input == UP){
	        if (xy[0] - 1 >= 0){
	            xy[0]--;
	        }
	    }
        else if (input == DOWN){
	        if (xy[0] + 1 < cols){
	            xy[0]++;
	        }
	    }
        else if (input == LEFT){
	        if (xy[1] - 1 >= 0){
	            xy[1]--;
	        }
	    }
        else if (input == RIGHT){
	        if (xy[1] + 1 < rows){
	            xy[1]++;
	        }
	    }
        else if (input == CLICK_TILE){
	        clickTile (&g, xy[0], xy[1]);
	    }
        else if (input == FLAG_TILE){
	        if (g.board[xy[0]][xy[1]].isVisible){
	            continue;
	        }
	        else if (g.board[xy[0]][xy[1]].isFlagged == TRUE){
	            g.board[xy[0]][xy[1]].isFlagged = FALSE;
	        }
	        else{
	            g.board[xy[0]][xy[1]].isFlagged = TRUE;
	        }
	    }
        else if (input == QUIT){
	        exit (1);
	    }
        else{//if the user pressed another key
	        continue;
	    }

        clearScreen ();
        printBoard (&g, xy);
        printf ("\n");
    }

    //free all the poiters
    for (int i = 0; i < rows; i++){
        free (g.board[i]);
    }
    free (g.board);

    return 0;
}