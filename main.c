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
    Tile * startingTerminal = getFirstAvailiableTerminal(pBoard);
    moveAndSolve(pBoard, startingTerminal, startingTerminal->color);

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
            Tile * t = getTile(pBoard, i, j);
            initializeTile(t, '.', i, j);
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
            initializeTile(getTile(pBoard, row, col), currentChar, row, col);
        }
        fileRow++;
    }

    // close file; we are done
    fclose(file);

    return pBoard;
}

// Initialize tile with values based on c
// Must pass in the tile you want to initialize
void initializeTile(Tile * tile, char ch, int row, int col){
    // tile defaults
    tile->row = row;
    tile->column = col;
    tile->symbol = ch;
    tile->type = NODE;
    tile->color = COLOR_NEUTRAL;
    tile->currentConnections = 0;
    tile->maxConnections = 1;
    
    // change defaults depending on case
    switch(ch){
        // colored tiles
        case 'A':
            tile->type = TERMINAL;
        case 'a': // fall thru 
            tile->color = COLOR_A;
            break;

        case 'B':
            tile->type = TERMINAL;
        case 'b': // fall thru 
            tile->color = COLOR_B;
            break;

        case 'C':
            tile->type = TERMINAL;
        case 'c': // fall thru 
            tile->color = COLOR_C;
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
            Tile * t = getTile(pBoard, i, j);
            // printf("%c | color: %d | type: %d | max: %d \n", t->c, t->color, t-> type, t->maxConnections);
            printf("%c", t->symbol);
            //🡠🡢🡡🡣🡤🡥🡦🡧
        }
        printf("\n");
    }
}

Tile * getTile(Tile * pBoard, uint8_t row, uint8_t column){
    return &pBoard[row*boardWidth + column];
}

int pos2D(int row, int col){
    return row*boardWidth + col;
}
bool isBoardSolved(Tile * pBoard){
    // i - row
    // j - col
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            Tile * t = getTile(pBoard, i ,j);
            // For all NODE and TERMINALs
            // If connections are not all used,
            // then they are not filled and board is incomplete
            if(t->type == NODE || t->type == TERMINAL){
                if(t->currentConnections < t->maxConnections){
                    return false;
                }
            }
        }
    }
    return true;
}
bool isColorFilled(Tile * pBoard, Color color){
    // i - row
    // j - col
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            Tile * t = getTile(pBoard, i, j);
            // For all NODE and TERMINALs that are COLOR
            // If connections are not all used,
            // then the color path is incomplete
            if((t->type == NODE || t->type == TERMINAL) && t->color == color){
                if(t->currentConnections < t->maxConnections){
                    return false;
                }
            }
        }
    }
    return true;
}
Tile * getFirstAvailiableTerminal(Tile * pBoard){
    // i - row
    // j - col
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            Tile * t = getTile(pBoard, i, j);
            if(t->type == TERMINAL){
                if(t->currentConnections == 0){
                    return t;
                }
            }
        }
    }
    return NULL;
}

bool isEndTerminal(Tile * pBoard, Tile * pTerminal) {
    // i - row
    // j - col
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            Tile * t = getTile(pBoard, i, j);
            if(t->type == TERMINAL && t->color == pTerminal->color &&
            t->currentConnections < t->maxConnections){
                // there exists one that is not filled
                return false;
            }
        }
    }
    // both terminals are filled
    return true;
}

void moveAndSolve(Tile * pBoard, Tile * pCurrentTile, Color color){
    uint8_t currentRow = pCurrentTile->row;
    uint8_t currentColumn = pCurrentTile->column;
    // Color color = pCurrentTile->color;

    printf("----------------------\n");
    printf("current color: %d\n", color);
    printf("moving to position: %d, %d\n", currentRow, currentColumn);
    printBoard(pBoard);
    printf("----------------------\n");

    // Update the board with our most recent move
    pCurrentTile->currentConnections += 1;

    // Board is solved, print solution
    if(isBoardSolved(pBoard)){
        printf("SOLUTION FOUND!!!!\n");
        printBoard(pBoard);
        return;
    }

    // Current position on a TERMINAL and it's the END of a path
    // Tile * pCurrentTile = getTile(pBoard, currentRow, currentColumn);
    if(pCurrentTile->type == TERMINAL && isEndTerminal(pBoard, pCurrentTile)){
        printf("WE HIT AN END TERMINAL, RUN PATH CHECK!\n");
        // check if the color is completed
        if(isColorFilled(pBoard, pCurrentTile->color)){
            // if complete, we need to jump to another color's start terminal
            // locate an unfilled color terminal and move there
            printf("path is valid\n");
            Tile * newTerminal = getFirstAvailiableTerminal(pBoard);
            if(newTerminal == NULL){
                // all terminals are filled but the board is not solved
                // (the final path is valid but did not solve the board)
                // (so it is still a dead end)
                return;
            }
            else {
                moveAndSolve(pBoard, newTerminal, newTerminal->color);
            }
            // we're back, reset the terminal we moved onto and this a dead end
            newTerminal->currentConnections = 0;
            return;
        }
        else {
            // path does not cover all colored nodes for this path
            printf("path is invalid, go back\n");
            return;
        }
    }

    // Move in the first valid direction we find 
    // (up/down/left/right)
    // (upleft/upright/downleft/downright)
    for(int i=0; i<8; i++){
        // pick a direction
        int rowOffset = DIRECTION[i][0];
        int colOffset = DIRECTION[i][1];
        
        // Each move is 2 moves in that direction (move to EDGE then move to NODE)
        // Make sure move is in bounds
        int newEdgeRow = currentRow + rowOffset;
        int newEdgeCol = currentColumn + colOffset;
        int newNodeRow = currentRow + rowOffset*2;
        int newNodeCol = currentColumn + colOffset*2;
        // printf("testing offsets: %d, %d", rowOffset, colOffset);
        if(newNodeRow >= boardHeight || newNodeCol >= boardWidth
            || newNodeRow < 0 || newNodeCol < 0) {
            // skip this direction since it is out of bounds
            continue;
        }
        // Check if EDGE has connection space (1 away)
        Tile * pNewEdge = getTile(pBoard, newEdgeRow, newEdgeCol);
        if(pNewEdge->currentConnections >= pNewEdge->maxConnections){
            // skip this direction, edge is occupied
            continue;
        }
    
        // Check if NODE or TERMINAL is the same color or is neutral color(2 away)
        Tile * pNewNode = getTile(pBoard, newNodeRow, newNodeCol);
        if(pNewNode->color != color && pNewNode->color != COLOR_NEUTRAL){
            // skip, not the same color
            continue;
        }

        // Check if NODE or TERMINAL has connection space (2 away)
        if(pNewNode->currentConnections >= pNewNode->maxConnections){
            // skip this direction, node is occupied/full
            continue;
        }

        // MOVE IS VALID!!
        // Update board with the new edge
        pNewEdge->currentConnections = 1;
        pNewEdge->symbol = DIRECTION_SYMBOL[i];
        pNewEdge->color = color;
        // Move to the new position
        printf("we are moving with these offsets: %d %d\n", rowOffset, colOffset);
        moveAndSolve(pBoard, pNewNode, color);

        // when we return, that means we hit a dead end and we need to undo the move
        // clear the edge
        pNewEdge->currentConnections = 0;
        pNewEdge->symbol = EDGE_EMPTY;
        pNewEdge->color = COLOR_NEUTRAL;
        // clear the node
        pNewNode->currentConnections -= 1;
    }

    // All directional moves from current position have been explored
    printf("NO VALID DIRECTIONS, GO BACK!\n");
    return;
}