//
// Created by asus on 2022/5/11.
//

#ifndef PJ_GAME_H
#define PJ_GAME_H

#include <SDL2/SDL.h>

int cell[2000][2000];
int flag[2000][2000];
char* myfile;
int position_x;
int position_y;

void loadmodel(int, int);
int clicktodefine(SDL_Window *, SDL_Surface *, int, int);
void drawthestrct(SDL_Window *, SDL_Surface *, int, int);
void drawthelivesqure (SDL_Window *, SDL_Surface *, int, int);
void drawthedeadsqure (SDL_Window *, SDL_Surface *, int, int);
int initial_cell(SDL_Window *, SDL_Surface *, int, int);
int read_status();
int read_delay();
int simulation(SDL_Window *, SDL_Surface *, int, int);

#endif //PJ_GAME_H
