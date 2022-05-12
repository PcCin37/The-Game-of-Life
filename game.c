//
// Created by asus on 2022/5/11.
//

#include "game.h"

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int p = 0;

void initial_mark(int n, int m) {
    for (int i = 0;i < n; i++) {
        for (int j = 0; j < m; j++) {
            flag[i][j] = 0;
        }
    }
}

void initial_cell(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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
    fp = fopen("cell_status.txt","w");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ",cell[i][j]);
        }
        printf("\n");
    }
    fprintf(fp,"--initial status--\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(fp,"%d", cell[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void read_status() {
    FILE *fp;
    fp = fopen("cell_status.txt","r");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    char row[3000];
    int p = 0;
    int i = 0;

    while (fgets(row, 3000, fp) != NULL) {
        if (row[0] != '-') {
            for(int j = 0; j < strlen(row); j++){
                cell[i][j] = row[j] - '0';
            }
            i += 1;
        }
        p += 1;
    }
}

void simulation(int n,int m) {
    read_status();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", cell[i][j]);
        }
        printf("\n");
    }
    FILE *fp;
    fp = fopen("cell_status.txt","w");
    fprintf(fp,"--final status--\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(fp,"%d", cell[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    initial_mark(n,m);
}
