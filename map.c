//
// Created by asus on 2022/5/9.
//

#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define row 20
#define col 20

int readinitmap() {
    FILE *fp;
    int i = 0;
    int j = 0;
    char ch = '\0';
    fp = fopen("initmap.txt","r");

    if (!fp) {
        printf("Can not find such initial file.\n");
        return -1;
    }

    int Map1[row][col] = {0};
    int Map2[row][col] = {0};


    for (i = 0; i < row; i++) {
        // read the whole line
        for (j = 0; j < col; j++){
            // read each char in the array
            fscanf(fp, "%c", &ch);
            if ('*' != ch) {
                // '0' represent dead cell
                Map1[i][j] = 0;
                Map2[i][j] = 0;
            }
            else {
                // '1' represent live cell
                Map1[i][j] = 1;
                Map2[i][j] = 1;
            }
        }
        // at the end of each line, there has a '\0'. so, read it again
        fscanf(fp, "%c", &ch);
    }
    return 0;
}