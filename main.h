#include <stdbool.h>
#include <stdint.h>

// Structs
typedef enum Color { COLOR_A, COLOR_B, COLOR_C, COLOR_NEUTRAL } Color;
typedef enum Type { 
    EDGE_EMPTY,
    EDGE_UP,
    EDGE_DOWN,
    EDGE_LEFT,
    EDGE_RIGHT,
    EDGE_UP_LEFT,
    EDGE_UP_RIGHT,
    EDGE_DOWN_LEFT,
    EDGE_DOWN_RIGHT, 
    NODE, 
    TERMINAL
} Type;

// Symbols as strings in order to use unicode characters 
// and more flexibility with printing format
// mapped 1:1 with the enum TYPE
// second dimension represents the COLOR
// TYPE_SYMBOLS[type][color + maxConnections - 1]
static char * TYPE_SYMBOLS[11][7] = {
    {".", ".", ".", "."}, // EDGE_EMPTY,
    {"|", "|", "|", "|"}, // EDGE_UP,
    {"|", "|", "|", "|"}, // EDGE_DOWN,
    {"-", "-", "-", "-"}, // EDGE_LEFT,
    {"-", "-", "-", "-"}, // EDGE_RIGHT,
    {"\\", "\\", "\\", "\\"}, // EDGE_UP_LEFT,
    {"/", "/", "/", "/"}, // EDGE_UP_RIGHT,
    {"/", "/", "/", "/"}, // EDGE_DOWN_LEFT,
    {"\\", "\\", "\\", "\\"}, // EDGE_DOWN_RIGHT, 
    {"a", "b", "c", "o", "2", "3", "4"}, // NODE
    {"a", "b", "c", "T"}, // TERMINAL
};

typedef struct Tile {
    Color color;
    Type type;
    uint8_t maxConnections;
    uint8_t currentConnections;
    uint8_t row;
    uint8_t column;
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

static Type DIRECTION_EDGE_TYPE[8] = {
    EDGE_UP,
    EDGE_DOWN,
    EDGE_LEFT,
    EDGE_RIGHT,
    EDGE_UP_LEFT,
    EDGE_UP_RIGHT,
    EDGE_DOWN_LEFT,
    EDGE_DOWN_RIGHT
};

// Functions
Tile * mallocBoardFromFile(char * fileName);
void initializeTile(Tile * pTile, char c, int row, int col);

void printBoard(Tile * pBoard);
Tile * getTile (Tile * pBoard, uint8_t row, uint8_t col);

// Color is retained when we move through neutral tiles
void moveAndSolve(Tile * pBoard, Tile * pCurrentTile, Color color); 

bool isBoardSolved(Tile * pBoard);
bool isColorFilled(Tile * pBoard, Color color);
Tile * getFirstAvailiableTerminal(Tile * pBoard);
bool isEndTerminal(Tile * pBoard, Tile * pTerminal);
