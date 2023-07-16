#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

static int width = 0;
static int height = 0;

// Functions
void solveBoard();

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("usage: ./solver <board.txt>");
        return 1;
    }

    // read the provided board file
    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    printf("Reading %s...\n", argv[1]);
    
    // Read and process the file line by line
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // initialize width of board from the first line
        if(width == 0){
            // strcspn() gets the length of string up the the \n character
            width = strcspn(line, "\n");
        }

        // error if any lines are not the same width
        if(strcspn(line, "\n") != width){
            printf("invalid board width format\n");
            return 1;
        }


        // create our board struct, line by line
        
        // every line is one row of the board
        // height also serves as our currentHeight or line counter
        height++;
    }

    // close file when done
    fclose(file);

    // solve the board
    solveBoard();

    printf("\n\ndone\n");
    return 0;
}

void solveBoard(){
    printf("h: %d, w: %d \n", height,width);
}