#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

// Globals
static int fileWidth = 0;
static int fileHeight = 0;
static int boardWidth = 0;
static int boardHeight = 0;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("usage: ./solver <board.txt>");
        return 1;
    }

    // Create board from file name
    char * fileName = argv[1];
    Tile * pBoard = mallocBoardFromFile(fileName);
    if(pBoard == NULL) return 1;

    // solve the board
    solveBoard(pBoard);

    // free board
    free(pBoard);

    printf("\n\ndone\n");
    return 0;
}

Tile * mallocBoardFromFile(char * fileName){
#define MAX_WIDTH 20
    
    // open the file
    FILE *file;
    char line[MAX_WIDTH];
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return NULL;
    }
    printf("Reading \"%s\" ...\n", fileName);

    // First, read the board file to get the size of the board
    while (fgets(line, MAX_WIDTH, file) != NULL) {
        // initialize width of board from the first line
        if(fileWidth == 0){
            // strcspn() gets the length of string up the the \n character
            fileWidth = strcspn(line, "\n");
        }
        // every line is one row of the board
        fileHeight++;
    }
    // increase boardWidth and height to fit in "edge" tiles
    boardWidth = 2*fileWidth - 1;
    boardHeight = 2*fileHeight - 1;

    // malloc board as a 1d array for contiguous memory
    // (we will address it as 2d with [row*width + col])
    Tile * pBoard = malloc(sizeof(Tile)*boardWidth*boardHeight);

    // go through board and make all the tiles edge tiles
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            Tile * t = &pBoard[i*boardWidth + j];
            initializeTile(t, '.');
        }
    }

    // reset file back to beginning
    fseek(file, 0, SEEK_SET);

    // Now read the file again and fill in the board with tiles
    int fileRow = 0;
    while (fgets(line, MAX_WIDTH, file) != NULL) {
        for(int fileCol=0; fileCol<fileWidth; fileCol++){
            // nodes are shifted to their proper positions in the board
            char currentChar = line[fileCol];
            int row = fileRow * 2;
            int col = fileCol * 2;
            initializeTile(&pBoard[row*boardWidth + col], currentChar);
        }
        fileRow++;
    }

    // close file; we are done
    fclose(file);

    return pBoard;
}

// Initialize tile with values based on c
// Must pass in the tile you want to initialize
void initializeTile(Tile * tile, char ch){
    // tile defaults
    tile->ch = ch;
    tile->type = NODE;
    tile->color = X_NEUTRAL;
    tile->currentConnections = 0;
    tile->maxConnections = 1;
    
    // change defaults depending on case
    switch(ch){
        // colored tiles
        case 'A':
            tile->type = TERMINAL;
        case 'a': // fall thru 
            tile->color = A_DIAMOND;
            break;

        case 'B':
            tile->type = TERMINAL;
        case 'b': // fall thru 
            tile->color = B_TRIANGLE;
            break;

        case 'C':
            tile->type = TERMINAL;
        case 'c': // fall thru 
            tile->color = C_SQUARE;
            break;

        // nodes with multi connections
        case '2':
            tile->maxConnections = 2;
            break;
        case '3':
            tile->maxConnections = 3;
            break;
        case '4':
            tile->maxConnections = 4;
            break;

        // edge tile
        case '.':
            tile->type = EDGE;
            break;

        // empty tile
        case 'x':
            tile->maxConnections = 0;
            break;
    }

    // tile is initialized from pointer, all done
}

void printBoard(Tile * pBoard){
    // i - row
    // j - col
    printf("\n");
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            Tile * t = &pBoard[i*boardWidth + j];
            // printf("%c | color: %d | type: %d | max: %d \n", t->c, t->color, t-> type, t->maxConnections);
            printf("%c", t->ch);
        }
        printf("\n");
    }
}

int pos2D(int row, int col){
    return row*boardWidth + col;
}

void moveAndSolve(Tile * pBoard, int currentRow, int currentColumn, Color color){
    // Board is solved, print solution
    if(isBoardSolved(pBoard)){
        printBoard(pBoard);
        return;
    }

    // Current position on a TERMINAL
    Tile currentTile = pBoard[pos2D(currentRow, currentColumn)];
    if(currentTile.type == TERMINAL){
        // check if the color is completed
        if(isColorFilled(pBoard, currentTile.color)){
            // if complete, we need to jump to another color's start terminal
            // moveAndSolve()
        }
        else {
            // this is a starting terminal
            // OR
            // path does not cover all colored nodes for this path
            
            // either way,
            // go look for valid directions to move
            // (if none) -> this path is a dead end and we go back up
        }
    }

    // Move in the first valid direction we find 
    // (up/down/left/right)
    // (upleft/upright/downleft/downright)
    for(int i=0; i<8; i++){
        // pick a direction
        
        // Each move is 2 moves in that direction (move to EDGE then move to NODE)
        // Make sure move is in bounds
        // Check if EDGE has connection space (1 away)
        // Check if NODE or TERMINAL has connection space (2 away)

        // Move is valid
        // Save the move
        // Update the board
        // moveAndSolve()
        // Undo the move and update the board
    }

    // All moves from current position have been explored
    return;
}