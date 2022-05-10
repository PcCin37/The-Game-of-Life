//
// Created by asus on 2022/5/10.
//

#include "game.h"
#include "map.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main_game() {
    FILE *fp;
    fp = fopen(initfile, "r");
    char in[500];
    int step = -100;
    int rownum;
    int colnum;
    int i;
    int j;
    int sum;
    readinitmap(&rownum, &colnum, initfile);
    int** old = (int **)malloc(sizeof(int *) * rownum);
    int** new = (int **)malloc(sizeof(int *) * rownum);
    int** now = (int **)malloc(sizeof(int *) * rownum);

    for (j = 0; fgets(in, 250, fp) != NULL; j++) {
        old[j] = (int *)malloc(sizeof(int) * colnum);
        for (i = 0; i < strlen(in) && in[i] != '\r' && in[i] != '\n'; i++) {
            if (in[i] != '1' && in[i] != '0') {
                return -3;
            }
            old[j][i] = in[i] - '0';
        }
    }

    for (i = 0; i < rownum; i++) {
        new[i] = (int *)malloc(sizeof(int) * colnum);
        now[i] = (int *)malloc(sizeof(int) * colnum);
        memset(new[i], 0, sizeof(new[i]));
        memset(now[i], 0, sizeof(now[i]));
    }
    while (1) {
        if (step != -100 && step < 0) {
            break;
        }
        //Deal with the four corners
        new[0][0] = status(old[0][0], old[0][1] + old[1][0] + old[1][1]);
        new[rownum - 1][0] = status(old[rownum - 1][0], old[rownum - 1][1] + old[rownum - 2][0] + old[rownum - 2][1]);
        new[0][colnum - 1] = status(old[0][colnum - 1], old[0][colnum - 2] + old[1][colnum - 1] + old[1][colnum - 2]);
        new[rownum - 1][colnum - 1] = status(old[rownum - 1][colnum - 1], old[rownum - 1][colnum - 2] + old[rownum - 2][colnum - 1] + old[rownum - 2][colnum - 2]);
        //Deal with four edges
        for (i = 1; i < rownum - 1; i++) {
            new[i][0] = status(old[i][0], old[i - 1][0] + old[i + 1][0] + old[i][1] + old[i - 1][1] + old[i + 1][1]);
            new[i][colnum - 1] = status(old[i][colnum - 1], old[i - 1][colnum - 1] + old[i + 1][colnum - 1] + old[i][colnum - 2] + old[i - 1][colnum - 2] + old[i + 1][colnum - 2]);
        }
        for (i = 1; i < colnum - 1; i++) {
            new[rownum - 1][i] = status(old[rownum - 1][i], old[rownum - 1][i - 1] + old[rownum - 1][i + 1] + old[rownum - 2][i] + old[rownum - 2][i + 1] + old[rownum - 2][i - 1]);
            new[0][i] = status(old[0][i], old[0][i - 1] + old[0][i + 1] + old[1][i] + old[1][i + 1] + old[1][i - 1]);
        }
        //Deal with the middle part
        for (i = 1; i < rownum - 1; i++) {
            for (j = 1, sum = 0; j < colnum - 1; j++) {
                new[i][j] = status(old[i][j], old[i - 1][j] + old[i + 1][j] + old[i][j-1] + old[i][j + 1] + old[i - 1][j - 1] + old[i + 1][j - 1] + old[i + 1][j + 1] + old[i - 1][j + 1]);
            }
        }
        fp = fopen("copy.txt", "w");
        for (i = 0, sum = 0; i < rownum; i++) {
            for (j = 0; j < colnum; j++) {
                now[i][j] = old[i][j];
                if ((old[i][j] = new[i][j])==1) {
                    sum++;
                }
                fprintf(fp,"%d", old[i][j]);
            }
            fprintf(fp,"\n");
            memset(new[i], 0, sizeof(new[i]));
        }
        fclose(fp);
        if (sum == 0) {
            break;
        }
        for (i = 0, sum = 0; i < rownum; i++) {
            for (j = 0; j < colnum; j++) {
                if (now[i][j] == old[i][j]) {
                    sum++;
                }
            }
        }
        if (sum == rownum * colnum) {
            break;
        }
        if (step != -100) {
            step--;
        }
    }
    free(old);
    free(new);
    return 0;
}