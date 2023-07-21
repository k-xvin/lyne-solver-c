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

// Functions
Tile * mallocBoardFromFile(char * fileName);
void printBoard(Tile * pBoard);

void solveBoard(Tile * pBoard);
void initializeTile(Tile * tile, char c);