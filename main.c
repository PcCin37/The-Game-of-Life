#include <stdio.h>

#include "cell.h"

int main() {
    int n, m;
    int step;
    printf("please enter the world size and the steps you want:");
    scanf("%d %d %d", &n, &m, &step);
    initial_cell(n, m);
    for (int i = 0; i < step; i++) {
        printf("1");
        printf("Round %d of the game:\n", i);
        printf("2");
        simulation(i, n, m);
    }
}
