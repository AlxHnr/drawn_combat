#ifndef TXT_DRAW_H
#define TXT_DRAW_H

#include <SDL.h>
#include <SDL_image.h>
#include <lib_gfx.h>

#define key_map_path "gfx/key_map.png"

int init_txt_draw();
void txt_draw_quit();

unsigned short get_string_w(char* string);
unsigned short get_string_h(char* string);

void Blit_Int(int num, SDL_Rect *dest, SDL_Surface *screen);
void Blit_String(char *string, SDL_Rect *dest, SDL_Surface *screen);

#endif