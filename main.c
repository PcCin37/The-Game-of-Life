#include <stdio.h>
#include "game.h"

int main() {
    int n, m;
    int max_life;
    printf("please enter the world size and the steps you want:");
    scanf("%d %d %d", &n, &m, &max_life);
    initial_cell(n, m);
    for (int i = 0; i < max_life; i++){
        printf("Round %d of the game:\n", i);
        simulation(n, m);
    }
}
