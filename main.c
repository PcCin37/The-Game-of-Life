#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int main(int argc, char* argv[]) {
    if(argc != 3 || strcmp(argv[0],"./game") != 0){
        printf("Invalid file name! Please input: ./game filename.txt filename.txt\n");
        return 0;
    } else {
        printf("\nWelcome to the library management system!\n");
        initfile = (char*)malloc(sizeof(argv[1]+1));
        resultfile = (char*)malloc(sizeof(argv[2]+1));
        strcpy(initfile, argv[1]);
        strcpy(resultfile, argv[2]);
        main_game();
        return 0;
    }
}
