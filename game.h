//
// Created by asus on 2022/5/11.
//

#ifndef PJ_GAME_H
#define PJ_GAME_H

int cell[2000][2000];
int flag[2000][2000];
char* myfile;

void initial_mark(int,int);
int initial_cell(int,int);
int read_status();
void simulation(int,int);

#endif //PJ_GAME_H
