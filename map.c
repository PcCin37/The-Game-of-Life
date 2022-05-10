//
// Created by asus on 2022/5/9.
//

#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readinitmap(int* row, int* col, char* filename) {
    FILE *fp;
    char in[500];
    int i;
    int j;
    char temp;
    fp = fopen(filename,"r");

    if (fp == NULL) {
        printf("Can not find such initial file.\n");
        return -1;
    }
    if (fgets(in, 300, fp) == NULL) {
        printf("Nothing in the file.\n");
        return -2;
    }

    for (i = 0, j = 0; i < strlen(in) && in[i] != '\n' && in[i] != '\r'; i++) {
        if (in[i] == '1' || in[i] == '0') {
            j++;
        }
    }
    * col = j;
    for (j = 1; fgets(in, 300, fp) != NULL; j++);
    * row = j;
    fclose(fp);
    return 0;
}