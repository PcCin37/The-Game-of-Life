#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "menu.h"

int main(int argc, char* argv[]) {
    if (argc!= 3 || strcmp(argv[0], "./lifegame") != 0) {
        printf("Invalid input! Please input: ./lifegame filename.txt tORg\n");
        return -1;
    }
    else if (strcmp(argv[2], "g") == 0) {
        printf("Welcome to the Game of Life interface!\n");
        myfile = (char*)malloc(sizeof(argv[1]+1));
        strcpy(myfile, argv[1]);
        run_menu();
        return 0;
    }
    else if (strcmp(argv[2], "t") == 0) {
        printf("test result:\n");
        printf("test simulation:\n\n");
        test_simulation_1();
        test_simulation_2();
        test_simulation_3();
        test_simulation_4();
    }
}
