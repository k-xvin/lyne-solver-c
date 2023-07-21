#include <stdbool.h>

// Structs
typedef enum Color { A_DIAMOND, B_TRIANGLE, C_SQUARE, X_NEUTRAL } Color;
typedef enum Type { EDGE, NODE, TERMINAL} Type;

typedef struct Tile {
    char ch;
    Color color;
    Type type;
    int maxConnections;
    int currentConnections;
} Tile;

static int directions[8][2] = {

};

// Functions
Tile * mallocBoardFromFile(char * fileName);
void initializeTile(Tile * tile, char c);

int pos2D(int row, int col);
void printBoard(Tile * pBoard);

void moveAndSolve(Tile * pBoard, int row, int column, Color color); 
bool isBoardSolved(Tile * pBoard);
bool isColorFilled(Tile * pBoard, Color color);