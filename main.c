#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "menu.h"

int main(int argc, char* argv[]) {
    if (argc != 2 || strcmp(argv[0], "./lifegame") != 0) {
        printf("Invalid input! Please input: ./lifegame filename.txt\n");
        return -1;
    }
    else {
        printf("Welcome to the Game of Life interface!\n");
        myfile = (char*)malloc(sizeof(argv[1]+1));
        strcpy(myfile, argv[1]);
        run_menu();
        return 0;
    }
}
