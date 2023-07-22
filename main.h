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
    int row;
    int col;
} Tile;

// Row, col
static int directions[8][2] = {
    {-1,0},     // up
    {1,0},      // down
    {0,-1},     // left
    {0,1},      // right
    {-1,-1},    // up-left
    {-1,1},     // up-right
    {1,-1},     // down-left
    {1,1},      // down-right
};

static char edgeSymbols[8] = {
    '|',
    '|',
    '-',
    '-',
    '\\',
    '/',
    '/',
    '\\'
};

// Functions
Tile * mallocBoardFromFile(char * fileName);
void initializeTile(Tile * tile, char c, int row, int col);

int pos2D(int row, int col);
void printBoard(Tile * pBoard);

void moveAndSolve(Tile * pBoard, int row, int column, Color color); 
bool isBoardSolved(Tile * pBoard);
bool isColorFilled(Tile * pBoard, Color color);
Tile * getFirstAvailiableTerminal(Tile * pBoard);
bool isEndTerminal(Tile * pBoard, Tile * pTerminal);