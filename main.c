#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 20

// Structs
typedef enum Color { A_DIAMOND, B_TRIANGLE, C_SQUARE, X_NEUTRAL } Color;
typedef enum Type { EDGE, NODE, TERMINAL} Type;

typedef struct Tile {
    char c;
    Color color;
    Type type;
    int maxConnections;
    int currentConnections;
} Tile;

// Functions
void solveBoard(Tile * pBoard);
void initializeTile(Tile * tile, char c);
void initializeBoard(Tile * pBoard);

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

    // open the file
    FILE *file;
    char line[MAX_WIDTH];
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }
    printf("Reading \"%s\" ...\n", argv[1]);

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
    // board width and height also fits in "edge" tiles around every node tile
    boardWidth = 2*fileWidth - 1;
    boardHeight = 2*fileHeight - 1;

    // use 1d array in order to represent 2d array as contiguous memory
    Tile *pBoard = malloc(sizeof(Tile)*boardWidth*boardHeight);
    initializeBoard(pBoard);

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

    // solve the board
    solveBoard(pBoard);

    // free board
    free(pBoard);

    printf("\n\ndone\n");
    return 0;
}

// Initialize tile with values based on c
// Must pass in the tile you want to initialize
void initializeTile(Tile * tile, char c){
    // tile defaults
    tile->c = c;
    tile->type = NODE;
    tile->color = X_NEUTRAL;
    tile->currentConnections = 0;
    tile->maxConnections = 1;
    
    // change defaults depending on case
    switch(c){
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
        case 'e':
            tile->type = EDGE;
            break;

        // empty tile
        case 'x':
            tile->maxConnections = 0;
            break;
    }

    // tile is initialized from pointer, all done
}

void initializeBoard(Tile *pBoard){
    // go through board and make all the tiles edge tiles
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            Tile * t = &pBoard[i*boardWidth + j];
            initializeTile(t, 'e');
        }
    }
}

void solveBoard(Tile *pBoard){
    // for(int i=0;i<boardHeight;i++){
    //     for(int j=0;j<boardWidth;j++){
    //         Tile * t = &pBoard[i*boardWidth + j];
    //         printf("%c | color: %d | type: %d | max: %d \n", t->c, t->color, t-> type, t->maxConnections);
    //     }
    //     printf("\n");
    // }
    // printf("h: %d, w: %d \n", boardHeight,boardWidth);

    
}