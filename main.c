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
void solveBoard(Tile **board);
void initializeTile(Tile tile, char c);

// Globals
static int width = 0;
static int height = 0;

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
    printf("Reading %s...\n", argv[1]);

    // First, read the board file to get the size of the board
    while (fgets(line, MAX_WIDTH, file) != NULL) {
        // initialize width of board from the first line
        if(width == 0){
            // strcspn() gets the length of string up the the \n character
            width = strcspn(line, "\n");
        }
        // every line is one row of the board
        height++;
    }
    // allocate 2d array board based on size
    Tile **board = malloc(sizeof(Tile)*height*width);

    // reset file back to beginning
    fseek(file, 0, SEEK_SET);

    // Now read the file again and fill in the board with tiles
    int row = 0;
    while (fgets(line, MAX_WIDTH, file) != NULL) {
        for(int col=0; col<width; col++){
            char currentChar = line[col];
            initializeTile(board[row][col], currentChar);
        }
        row++;
    }

    // close file when done
    fclose(file);

    // solve the board
    solveBoard(board);

    // Free the board and tiles
    // for(int row=0; row<width; row++){
    //     for(int col=0; col<height; col++){
    //         free(board[row][col]);
    //     }
    // }
    free(board);

    printf("\n\ndone\n");
    return 0;
}

// Initialize tile with values based on c
// Must pass in the tile you want to initialize
void initializeTile(Tile tile, char c){
    // tile defaults
    tile.c = c;
    tile.type = NODE;
    tile.color = X_NEUTRAL;
    tile.currentConnections = 0;
    tile.maxConnections = 1;
    
    // change defaults depending on case
    switch(c){
        // colored tiles
        case 'A':
            tile.type = TERMINAL;
        case 'a': // fall thru 
            tile.color = A_DIAMOND;
            break;

        case 'B':
            tile.type = TERMINAL;
        case 'b': // fall thru 
            tile.color = B_TRIANGLE;
            break;

        case 'C':
            tile.type = TERMINAL;
        case 'c': // fall thru 
            tile.color = C_SQUARE;
            break;

        // nodes with multi connections
        case '2':
            tile.maxConnections = 2;
            tile.type = EDGE;
            break;
        case '3':
            tile.maxConnections = 3;
            tile.type = EDGE;
            break;
        case '4':
            tile.maxConnections = 4;
            tile.type = EDGE;
            break;

        // empty tile
        case 'e':
            tile.maxConnections = 0;
            break;
    }

    // tile is initialized from pointer, all done
}

void solveBoard(Tile **board){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            printf("%c", board[i][j].c);
        }
    }
    printf("h: %d, w: %d \n", height,width);
}