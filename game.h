//
// Created by asus on 2022/5/11.
//

#ifndef PJ_GAME_H
#define PJ_GAME_H

#include <SDL2/SDL.h>

int cell[2000][2000];
int flag[2000][2000];
char* myfile;

void loadmodel(int);
void drawthestrct(SDL_Window *, SDL_Surface *, int, int);
void drawthesqure (SDL_Window *, SDL_Surface *, int, int);
int initial_cell(SDL_Window *, SDL_Surface *, int, int);
int read_status();
int simulation(SDL_Window *, SDL_Surface *, int, int);

#endif //PJ_GAME_H
