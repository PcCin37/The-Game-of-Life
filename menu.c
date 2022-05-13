//
// Created by asus on 2022/5/13.
//
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "game.h"

void run_menu() {
    int n, m;
    int step;
    char arr[50] = {};
    memset(arr, 0, 20);

    printf("Define the number of rows in the world:");
    gets(arr);
    n = atoi(arr);
    while(1) {
        if (n <= 0) {
            printf("Wrong input. Define the number of rows in the world:");
            gets(arr);
            n = atoi(arr);
        }
        else break;
    }

    printf("Define the number of columns in the world:");
    gets(arr);
    m = atoi(arr);
    while(1) {
        if (m <= 0) {
            printf("Wrong input. Define the number of columns in the world:");
            gets(arr);
            m = atoi(arr);
        }
        else break;
    }

    initial_cell(n, m);

    printf("\nDefine the game steps:");
    gets(arr);
    step = atoi(arr);
    while(1) {
        if (step <= 0) {
            printf("Wrong input. Define the game steps:");
            gets(arr);
            step = atoi(arr);
        }
        else break;
    }

    //initial_cell(n, m);
    for (int i = 0; i < step; i++){
        printf("\nRound %d of the game:\n", i + 1);
        simulation(n, m);
    }
}