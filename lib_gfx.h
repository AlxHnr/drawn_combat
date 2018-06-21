#ifndef LIB_GFX_H
#define LIB_GFX_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <txt_draw.h>

SDL_Surface *load_image(const char *image_path);

//particles
typedef struct particle{
  int x;
  int y;
}particle;

void init_falling_particles(particle *particle_array, int elements, int x, int y, int w, int h);
void render_jet_flame(particle *particle_array, int elements, int x, int y, int w, int h, int speed);
void render_falling_particles(particle *particle_array, int elements, int x, int y, int w, int h, int speed);
void blit_particles(SDL_Surface *screen, particle *particle_array, int elements, unsigned char r, unsigned char g, unsigned char b);

//animations
void move_in_surface(SDL_Surface *surface, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed);
void move_out_surface(SDL_Surface *surface, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed);
void move_in_string(char *string, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed);
void move_out_string(char *string, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed);

#endif