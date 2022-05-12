#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int main(int argc, char* argv[]) {
    if (argc != 2 || strcmp(argv[0], "./lifegame") != 0) {
        printf("Invalid input! Please input: ./lifegame filename.txt\n");
        return -1;
    }
    else {
        printf("Welcome to the Game of Life interface!\n");
        myfile = (char*)malloc(sizeof(argv[1]+1));
        strcpy(myfile, argv[1]);
    }

    int n, m;
    int step;
    printf("Define the number of rows in the world:");
    scanf("%d", &n);
    printf("Define the number of columns in the world:");
    scanf("%d", &m);
    printf("Define the game steps:");
    scanf("%d", &step);
    initial_cell(n, m);
    for (int i = 0; i < step; i++){
        printf("\nRound %d of the game:\n", i + 1);
        simulation(n, m);
    }
    return 0;
}
