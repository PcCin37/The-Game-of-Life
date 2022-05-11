//
// Created by asus on 2022/5/11.
//
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "cell.h"

void read_status() {
    FILE *fp;
    fp = fopen("cell_status.txt", "r");
    if (fp = NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }

    char row[3000];
    int p = 0;
    int i = 0;

    while (fgets(row, 3000, fp) != NULL) {
        if (row[0] != '-') {
            for (int j = 0; j < strlen(row); j++) {
                cell[i][j] = row[j] - '0';
            }
            i += 1;
        }
        p += 1;
    }
}
