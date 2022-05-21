//
// Created by asus on 2022/5/21.
//

#include <stdio.h>

#include "game.h"
#include "menu.h"6

int expect[2000][2000];

void test_simulation_1() {
    int i;
    int j;
    cell[0][0]=0;
    cell[0][1]=0;
    cell[0][2]=0;
    cell[1][0]=0;
    cell[1][1]=1;
    cell[1][2]=0;
    cell[2][0]=0;
    cell[2][1]=0;
    cell[2][2]=0;
    simu_testcase(3, 3);
    expect[0][0]=0;
    expect[0][1]=0;
    expect[0][2]=0;
    expect[1][0]=0;
    expect[1][1]=0;
    expect[1][2]=0;
    expect[2][0]=0;
    expect[2][1]=0;
    expect[2][2]=0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (cell[i][j] != expect[i][j]){
                printf("------------------------------------\n");
                printf("| Error: test_simulation_1 failed! |\n");
                printf("------------------------------------\n");
            }
        }
    }
    printf("---------------------------\n");
    printf("| test_simulation_1 pass! |\n");
    printf("---------------------------\n");
}

void test_simulation_2() {
    int i;
    int j;
    cell[0][0]=0;
    cell[0][1]=0;
    cell[0][2]=1;
    cell[1][0]=0;
    cell[1][1]=1;
    cell[1][2]=0;
    cell[2][0]=0;
    cell[2][1]=1;
    cell[2][2]=0;
    simu_testcase(3, 3);
    expect[0][0]=0;
    expect[0][1]=0;
    expect[0][2]=0;
    expect[1][0]=0;
    expect[1][1]=1;
    expect[1][2]=1;
    expect[2][0]=0;
    expect[2][1]=0;
    expect[2][2]=0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (cell[i][j] != expect[i][j]){
                printf("------------------------------------\n");
                printf("| Error: test_simulation_2 failed! |\n");
                printf("------------------------------------\n");
            }
        }
    }
    printf("---------------------------\n");
    printf("| test_simulation_2 pass! |\n");
    printf("---------------------------\n");
}

void test_simulation_3() {
    int i;
    int j;
    cell[0][0]=1;
    cell[0][1]=1;
    cell[0][2]=0;
    cell[1][0]=1;
    cell[1][1]=1;
    cell[1][2]=0;
    cell[2][0]=0;
    cell[2][1]=0;
    cell[2][2]=1;
    simu_testcase(3, 3);
    expect[0][0]=1;
    expect[0][1]=1;
    expect[0][2]=0;
    expect[1][0]=1;
    expect[1][1]=0;
    expect[1][2]=1;
    expect[2][0]=0;
    expect[2][1]=1;
    expect[2][2]=0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (cell[i][j] != expect[i][j]){
                printf("------------------------------------\n");
                printf("| Error: test_simulation_3 failed! |\n");
                printf("------------------------------------\n");
            }
        }
    }
    printf("---------------------------\n");
    printf("| test_simulation_3 pass! |\n");
    printf("---------------------------\n");
}

void test_simulation_4() {
    int i;
    int j;
    cell[0][0]=0;
    cell[0][1]=0;
    cell[0][2]=1;
    cell[1][0]=0;
    cell[1][1]=0;
    cell[1][2]=1;
    cell[2][0]=0;
    cell[2][1]=0;
    cell[2][2]=1;
    simu_testcase(3, 3);
    expect[0][0]=0;
    expect[0][1]=0;
    expect[0][2]=0;
    expect[1][0]=0;
    expect[1][1]=1;
    expect[1][2]=1;
    expect[2][0]=0;
    expect[2][1]=0;
    expect[2][2]=0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (cell[i][j] != expect[i][j]){
                printf("------------------------------------\n");
                printf("| Error: test_simulation_4 failed! |\n");
                printf("------------------------------------\n");
            }
        }
    }
    printf("---------------------------\n");
    printf("| test_simulation_4 pass! |\n");
    printf("---------------------------\n");
}
