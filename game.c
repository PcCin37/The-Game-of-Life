//
// Created by asus on 2022/5/11.
//

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "game.h"


void loadmodel(int input, int delay){
    //int i = 100;
    if (input == 1) {
        SDL_Delay(delay * 1000);
    }
    else if (input == 2) {
        while(1) {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            SDL_PumpEvents();
            if (state[SDL_SCANCODE_DOWN]) {
                while(1) {
                    const Uint8 *state2 = SDL_GetKeyboardState(NULL);
                    SDL_PumpEvents();
                    if (state2[SDL_SCANCODE_DOWN]) {
                        continue;
                    }
                    else {
                        break;
                    }
                }
                break;
            }
            else if (state[SDL_SCANCODE_RIGHT]) {
                while(1) {
                    const Uint8 *state2 = SDL_GetKeyboardState(NULL);
                    SDL_PumpEvents();
                    if (state2[SDL_SCANCODE_RIGHT]) {
                        continue;
                    }
                    else {
                        break;
                    }
                }
                break;
            }
            else if (state[SDL_SCANCODE_ESCAPE]) {
                exit(0);
            }
        }
    }
}

void drawthestrct(SDL_Window *window, SDL_Surface *screen, int n, int m) {
    int i;
    for (i = 0; i <= n; i++) {
        SDL_Rect tape = {i * 40, 0, 1, 40 * m};
        SDL_FillRect(screen, &tape, SDL_MapRGB(screen->format, 128, 128, 128));
        SDL_UpdateWindowSurface(window);
    }
    for(i = 0; i <= m; i++){
        SDL_Rect tape = {0, i * 40, 40 * n,1};
        SDL_FillRect(screen, &tape, SDL_MapRGB(screen->format, 128, 128, 128));
        SDL_UpdateWindowSurface(window);
    }
}

void drawthelivesqure (SDL_Window *window, SDL_Surface *screen, int n, int m) {
    SDL_Rect squre = {n, m, 40, 40};
    SDL_FillRect(screen, &squre, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_UpdateWindowSurface(window);
}

void drawthedeadsqure (SDL_Window *window, SDL_Surface *screen, int n, int m) {
    SDL_Rect squre = {n, m, 40, 40};
        SDL_FillRect(screen, &squre, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
}

int initial_cell(SDL_Window *window, SDL_Surface *screen, int n, int m) {
    int i;
    int j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            // randomly form the initial world
            // introduce a p for random number, when p < 5, let the cell be dead
            int p = rand() % 10;
            if (p < 5) {
                cell[i][j] = 0;
            }
            else {
                cell[i][j] = 1;
            }
            flag[i][j] = 0;
        }
    }

    // output of the initial status of the game
    FILE *fp;
    fp = fopen(myfile,"w");
    if (fp == NULL) {
        printf("File not found.\n");
        return -1;
    }

    printf("\nInitial status:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ",cell[i][j]);
            if (cell[i][j] == 1) {
                drawthelivesqure(window, screen, 40 * j, i * 40);
            }
        }
        printf("\n");
    }
    fprintf(fp,"--initial status--\n");
    int del = rand() % 5 + 1;
    fprintf(fp, "!%d\n", del);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fprintf(fp,"%d", cell[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
}

int clicktodefine(SDL_Window *window, SDL_Surface *screen, int n, int m) {
    int i;
    int j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cell[i][j] = 0;
            flag[i][j] = 0;
        }
    }

    printf("You can click %d times.\n", (n + m) / 2);

    int num = 0;
    while(1) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                case SDL_MOUSEBUTTONDOWN:
                    position_x = event.button.x / 40;
                    position_y = event.button.y / 40;
                    if (cell[position_y][position_x] == 0) {
                        cell[position_y][position_x] = 1;
                        drawthelivesqure(window, screen, 40 * position_x, position_y * 40);
                        drawthestrct(window, screen, m, n);
                        num++;
                    }
                    else if (cell[position_y][position_x] == 1) {
                        cell[position_y][position_x] = 0;
                        drawthedeadsqure(window, screen, 40 * position_x, position_y * 40);
                        drawthestrct(window, screen, m, n);
                        num++;
                    }
                    printf("Mouse down: (%d, %d)\n", position_x, position_y);
                    break;
            }
        }
        if (num == (n + m) / 2) {
            break;
        }
    }

    FILE *fp;
    fp = fopen(myfile,"w");
    if (fp == NULL) {
        printf("File not found.\n");
        return -1;
    }
    printf("\nInitial status:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ",cell[i][j]);
        }
        printf("\n");
    }
    fprintf(fp,"--initial status--\n");
    int del = rand() % 5 + 1;
    fprintf(fp, "!%d\n", del);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fprintf(fp,"%d", cell[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
}

int read_delay() {
    FILE *fp;
    fp = fopen(myfile,"r");
    if (fp == NULL) {
        printf("File not found.\n");
        fprintf(stderr, "Invalid file.\n");
        return -1;
    }

    char row[3000];
    int p;
    int delay;
    if (fgets(row, 3000, fp) == NULL) {
        printf("Nothing in the file.\n");
        return -1;
    }

    while (fgets(row, 3000, fp) != NULL) {
        if (row[0] == '!') {
            p = strlen(row);
            delay = row[p - 1];
        }
    }
    return delay;
}

int read_status() {
    FILE *fp;
    fp = fopen(myfile,"r");
    if (fp == NULL) {
        printf("File not found.\n");
        fprintf(stderr, "Invalid file.\n");
        exit(EXIT_FAILURE);
    }

    char row[3000];
    int p = 0;
    int i = 0;
    int j;
    if (fgets(row, 3000, fp) == NULL) {
        printf("Nothing in the file.\n");
        return -1;
    }

    while (fgets(row, 3000, fp) != NULL) {
        if (row[0] != '-' && row[0] != '!') {
            for(j = 0; j < strlen(row); j++){
                cell[i][j] = row[j] - '0';
            }
            i += 1;
        }
        p += 1;
    }
    return 0;
}

int simulation(SDL_Window *window, SDL_Surface *screen, int n,int m) {
    //read_status();

    // re-intialize the sdl parts
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    drawthestrct(window, screen, m, n);

    int i;
    int j;
    simu_testcase(n, m);

    // the output part
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", cell[i][j]);
            if (cell[i][j] == 1) {
                drawthelivesqure(window, screen, 40 * j, i * 40);
            }
        }
        printf("\n");
    }

    // output the result to the file
    FILE *fp;
    fp = fopen(myfile,"w");
    if (fp == NULL) {
        printf("File not found.\n");
        return -1;
    }

    fprintf(fp,"--final status--\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fprintf(fp,"%d", cell[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
}

int simu_testcase(int n, int m) {
    int i;
    int j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            int cnt = 0;
            // search the live cell around
            if (i - 1 >= 0){
                // printf("(%d,%d) %d \n",i - 1,j,cell[i - 1][j]);
                if (cell[i - 1][j] == 1) {
                    cnt += 1;
                }
            }
            if (i + 1 < n) {
                // printf("(%d,%d) %d \n",i + 1,j,cell[i + 1][j]);
                if (cell[i + 1][j] == 1) {
                    cnt += 1;
                }
            }
            if (j - 1 >= 0) {
                // printf("(%d,%d) %d \n",i,j - 1,cell[i][j - 1]);
                if (cell[i][j - 1] == 1) {
                    cnt += 1;
                }
            }
            if (j + 1 < m) {
                //printf("(%d,%d) %d \n",i,j + 1,cell[i][j + 1]);
                if (cell[i][j + 1] == 1) {
                    cnt += 1;
                }
            }
            if (j + 1 < m && i + 1 < n) {
                // printf("(%d,%d) %d \n",i + 1,j + 1,cell[i + 1][j + 1]);
                if (cell[i + 1][j + 1] == 1) {
                    cnt += 1;
                }
            }
            if (j + 1 < m && i - 1 >= 0) {
                // printf("(%d,%d) %d \n",i - 1,j +1,cell[i-1][j+1]);
                if (cell[i - 1][j + 1] == 1) {
                    cnt += 1;
                }
            }
            if (j - 1 >= 0 && i - 1 >= 0) {
                // printf("(%d,%d) %d \n",i - 1,j - 1,cell[i - 1][j - 1]);
                if (cell[i - 1][j - 1] == 1) {
                    cnt += 1;
                }
            }
            if (j - 1 >= 0 && i + 1 < n) {
                // printf("(%d,%d) %d \n",i,j,cell[i + 1][ j - 1]);
                if (cell[i + 1][j - 1] == 1) {
                    cnt += 1;
                }
            }
            flag[i][j] = cnt;
            // printf("(%d,%d) %d \n",i,j,cnt);
        }

    }

    // according to the rules, change the status of the cell
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (cell[i][j] == 1) {
                if (flag[i][j] == 0 || flag[i][j] == 1) {
                    cell[i][j] = 0;
                }
                if (flag[i][j] == 2 || flag[i][j] == 3) {
                    cell[i][j] = 1;
                }
                if (flag[i][j] > 3) {
                    cell[i][j] = 0;
                }
            }
            else if (cell[i][j] == 0) {
                if (flag[i][j] == 3) {
                    cell[i][j] = 1;
                }
            }
        }
    }
}
