#ifndef LVL_H
#define LVL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <SDL_gfxPrimitives.h>
#include <lib_gfx.h>
#include <txt_draw.h>
#include <menu.h>

//level intro
#define lvl_1 "LEVEL 1: RUCKSACKFROSCH\nSAMMLE 50 STEINE"
#define lvl_2 "LEVEL 2: STEINWURF\nTREFFE DEN FROSCH"
#define lvl_3 "LEVEL 3: BLEISTIFTRACKETE\nSTREICHE ALLES DURCH "

//main functions
int init_levels();
void levels_quit();
char lvl_message(SDL_Surface *screen, char *lvl_txt);

//levels
int init_frog();
void quit_frog();
int frog(SDL_Surface *screen);

int init_throw_stones();
void quit_throw_stones();
int throw_stones(SDL_Surface *screen);

int init_rocket_flight();
void quit_rocket_flight();
int rocket_flight(SDL_Surface *screen);

#endif