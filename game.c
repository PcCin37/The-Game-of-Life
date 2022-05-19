//
// Created by asus on 2022/5/11.
//

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "game.h"

int p = 0;

void drawthestrct(SDL_Window *window, SDL_Surface *screen, int n, int m) {
    int i;
    for (i = 0; i <= n; i++) {
        SDL_Rect tape = {i*100, 0, 1, 100*m};
        SDL_FillRect(screen, &tape, SDL_MapRGB(screen->format, 128, 128, 128));
        SDL_UpdateWindowSurface(window);
    }
    for(i = 0; i <= m; i++){
        SDL_Rect tape = {0, i*100, 100*n,1};
        SDL_FillRect(screen, &tape, SDL_MapRGB(screen->format, 128, 128, 128));
        SDL_UpdateWindowSurface(window);
    }
}

void drawthesqure (SDL_Window *window, SDL_Surface *screen, int n, int m) {
    SDL_Rect squre = {n, m, 100, 100};
    SDL_FillRect(screen, &squre, SDL_MapRGB(screen->format, 0, 0, 0));
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

    //-------------output--------------
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
                drawthesqure(window, screen, 100 * j, i * 100);
            }
        }
        printf("\n");
    }
    fprintf(fp,"--initial status--\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fprintf(fp,"%d", cell[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
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
        if (row[0] != '-') {
            for(j = 0; j < strlen(row); j++){
                cell[i][j] = row[j] - '0';
            }
            i += 1;
        }
        p += 1;
    }
    return 0;
}

int simulation(int n,int m) {
    read_status();

    int i;
    int j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            int cnt = 0;
            // search with the direction down
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

    //-------------output--------------
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", cell[i][j]);
        }
        printf("\n");
    }

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
