#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <dirent.h>
#include <txt_draw.h>
#include <lib_gfx.h>

//graphic paths
#define drawn_combat_logo_path "gfx/drawn_combat.png"
#define pencil_path "gfx/pencil.png"
#define game_menu_background_path "gfx/game_menu.png"

//menu texts
#define main_menu_text_1 "NEUES SPIEL"
#define main_menu_text_2 "BEENDEN"

#define game_menu_text_1 "WEITER"
#define game_menu_text_2 "HAUPTMENU"
#define game_menu_text_3 "SPIEL BEENDEN"

//main menu opening settings
#define main_menu_open_speed 2
#define main_menu_close_speed 3

//game menu opening settings
#define game_menu_open_speed 5
#define game_menu_close_speed 5

int init_menu();
void menu_quit();

int call_main_menu(SDL_Surface *screen);
int call_game_menu(SDL_Surface *screen);

#endif