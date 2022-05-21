//
// Created by asus on 2022/5/13.
//
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "menu.h"
#include "game.h"

void run_menu() {
    int useroption;
    int n, m;
    int step = -100;
    char arr[50] = {};
    memset(arr, 0, 20);
    SDL_Window *window = NULL;
    SDL_Surface *screen = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
        return;
    }

    printf("\nDefine the number of rows in the world:");
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

    printf("\nDefine the number of columns in the world:");
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

    window = SDL_CreateWindow("The Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m * 40, n * 40, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not initialize! SDL_Error: %s\n",SDL_GetError());
        return;
    }
    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    drawthestrct(window, screen, m, n);

    int rord;
    printf("\nRandomly initialize the world or define it by yourself:\n");
    printf("1. Randomly\n");
    printf("2. Click to define\n");
    printf("Your option:");
    gets(arr);
    rord = atoi(arr);
    while(1) {
        if (rord <= 0) {
            printf("Wrong input. Define the model of the game:");
            gets(arr);
            rord = atoi(arr);
        }
        else break;
    }

    if (rord == 1) {
        initial_cell(window, screen, n, m);
    }
    else if (rord == 2) {
        clicktodefine(window, screen, n, m);
    }

    printf("\nWhether you want to define the step of the game (yes or no):");
    gets(arr);
    while(1) {
        if (strcmp(arr, "yes") != 0 && strcmp(arr, "no") != 0) {
            printf("Please input 'yse' or 'no':");
            gets(arr);
        }
        else break;
    }

    int delay = read_delay();

    if (strcmp(arr, "yes") == 0) {
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

        printf("\nDefine the model of the game:\n");
        printf("1. run the game according to the delay\n");
        printf("2. run the game by press the key 'down' or 'right'\n");
        printf("Your option:");
        gets(arr);
        useroption = atoi(arr);
        while(1) {
            if (useroption <= 0) {
                printf("Wrong input. Define the model of the game:");
                gets(arr);
                useroption = atoi(arr);
            }
            else break;
        }

        int delay = read_delay();
        loadmodel(useroption, delay);

        //initial_cell(n, m);
        int i;
        for (i = 0; i < step; i++){
            printf("\nRound %d of the game:\n", i + 1);
            read_status();
            simulation(window, screen, n, m);
            loadmodel(useroption, delay);
        }
    }
    else {
        printf("\nDefine the model of the game:\n");
        printf("1. run the game according to the delay\n");
        printf("2. run the game by press the key 'down' or 'right'\n");
        printf("Hint: You can stop the game by pressing 'esc' whenever you want.\n");
        printf("Your option:");
        gets(arr);
        useroption = atoi(arr);
        while(1) {
            if (useroption <= 0) {
                printf("Wrong input. Define the model of the game:");
                gets(arr);
                useroption = atoi(arr);
            }
            else break;
        }

        loadmodel(useroption, delay);

        int i = 0;
        while(1) {
            printf("\nRound %d of the game:\n", i + 1);
            read_status();
            simulation(window, screen, n, m);
            loadmodel(useroption, delay);
            i++;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

}