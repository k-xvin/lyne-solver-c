#include <stdbool.h>

// Structs
typedef enum Color { COLOR_A, COLOR_B, COLOR_C, COLOR_NEUTRAL } Color;
typedef enum Type { EDGE, NODE, TERMINAL} Type;
typedef enum Symbol {
    A_TERMINAL  = 'A',
    A_NODE      = 'a',
    B_TERMINAL  = 'B',
    B_NODE      = 'b',
    C_TERMINAL  = 'C',
    C_NODE      = 'c',

    NODE_2      = '2',
    NODE_3      = '3',
    NODE_4      = '4',

    EDGE_EMPTY  = '.',
    NODE_EMPTY  = 'x',
} Symbol; 

typedef struct Tile {
    char ch;
    Color color;
    Type type;
    int maxConnections;
    int currentConnections;
    int row;
    int column;
} Tile;

// Row, col
static int DIRECTION[8][2] = {
    {-1,0},     // up
    {1,0},      // down
    {0,-1},     // left
    {0,1},      // right
    {-1,-1},    // up-left
    {-1,1},     // up-right
    {1,-1},     // down-left
    {1,1},      // down-right
};

static char DIRECTION_CHAR[8] = {
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