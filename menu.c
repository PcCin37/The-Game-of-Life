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

    window = SDL_CreateWindow("LifeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, n*100, m*100, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not initialize! SDL_Error: %s\n",SDL_GetError());
        return;
    }
    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    drawthestrct(window, screen, n, m);

    initial_cell(window, screen, n, m);

    printf("Whether you want to define the step of the game (yes or no):");
    gets(arr);
    while(1) {
        if (strcmp(arr, "yes") != 0 && strcmp(arr, "no") != 0) {
            printf("Please input 'yse' or 'no':");
            gets(arr);
        }
        else break;
    }

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

        //initial_cell(n, m);
        int i;
        for (i = 0; i < step; i++){
            printf("\nRound %d of the game:\n", i + 1);
            simulation(n, m);
        }
    }
    else {
        int i = 0;
        while(1) {
            printf("\nRound %d of the game:\n", i + 1);
            simulation(n, m);
            i++;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

}