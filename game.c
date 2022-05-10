//
// Created by asus on 2022/5/10.
//

#include "game.h"
#include "map.h"

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
    int** old = (int **)malloc(rownum* sizeof(int *));
    int** new = (int **)malloc(sizeof(int *) * rownum);
    int** now = (int **)malloc(sizeof(int *) * rownum);

}