//
// Created by asus on 2022/5/10.
//

#include "cell.h"
#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int status(int life, int nei) {
    // 0 represent dead cell, 1 represent live cell
    if (life == 0 && nei == 3) {
        // a dead cell with exactly 3 live neighbours becomes alive
        return 1;
    }
    if (life == 1) {
        // a live cell
        if (nei == 2 || nei == 3) {
            // with 2 or 3 live neighbours stays alive
            return 1;
        }
        // with 0 or 1 live neighbours; with more than 3 live neighbours becomes dead
        else return 0;
    }
}