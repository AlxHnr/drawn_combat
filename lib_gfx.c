#include <lib_gfx.h>

SDL_Surface *load_image(const char *image_path)
{
  SDL_Surface *temp = NULL;
  
  if((temp = IMG_Load(image_path)) != NULL)
  {
    return SDL_DisplayFormatAlpha(temp);
  }
  
  return NULL;
}

//animations
void move_in_surface(SDL_Surface *surface, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed)
{
  //vars
  Uint32 time_stop;
  SDL_Rect cache_dest;
  
  cache_dest.x = dest->x;
  cache_dest.y = screen->h;
  
  //animation start
  time_stop = SDL_GetTicks();
  while(cache_dest.y > dest->y)
  {
    //clear old surface
    SDL_BlitSurface(background, &cache_dest, screen, &cache_dest);
    
    cache_dest.y = screen->h - (SDL_GetTicks() - time_stop) * speed;
    if(cache_dest.y < dest->y)
      cache_dest.y = dest->y;
    
    SDL_BlitSurface(surface, NULL, screen, &cache_dest);
    SDL_Flip(screen);
  }
  //animation end
}
void move_out_surface(SDL_Surface *surface, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed)
{
  //vars
  Uint32 time_stop;
  SDL_Rect cache_dest;
  
  cache_dest.x = dest->x;
  cache_dest.y = dest->y;
  cache_dest.w = surface->w;
  cache_dest.h = surface->h;
  
  //animation start
  time_stop = SDL_GetTicks();
  while(cache_dest.y < screen->h)
  {
    //clear old surface
    SDL_BlitSurface(background, &cache_dest, screen, &cache_dest);
    
    cache_dest.y = dest->y + (SDL_GetTicks() - time_stop) * speed;
    
    SDL_BlitSurface(surface, NULL, screen, &cache_dest);
    SDL_Flip(screen);
  }
  //animation end
}
void move_in_string(char *string, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed)
{
  //vars
  Uint32 time_stop;
  SDL_Rect cache_dest;
  
  cache_dest.x = dest->x;
  cache_dest.y = screen->h;
  
  //animation start
  time_stop = SDL_GetTicks();
  while(cache_dest.y > dest->y)
  {
    //clear old surface
    cache_dest.w = get_string_w(string) * 20;
    cache_dest.h = get_string_h(string) * 20;
    SDL_BlitSurface(background, &cache_dest, screen, &cache_dest);
    
    cache_dest.y = screen->h - (SDL_GetTicks() - time_stop) * speed;
    if(cache_dest.y < dest->y)
      cache_dest.y = dest->y;
    
    Blit_String(string, &cache_dest, screen);
    SDL_Flip(screen);
  }
  //animation end
}
void move_out_string(char *string, SDL_Surface *background, SDL_Surface *screen, SDL_Rect *dest, unsigned char speed)
{
  //vars
  Uint32 time_stop;
  SDL_Rect cache_dest;
  
  cache_dest.x = dest->x;
  cache_dest.y = dest->y;
  
  //animation start
  time_stop = SDL_GetTicks();
  while(cache_dest.y < screen->h)
  {
    //clear old surface
    cache_dest.w = get_string_w(string) * 20;
    cache_dest.h = get_string_h(string) * 20;
    SDL_BlitSurface(background, &cache_dest, screen, &cache_dest);
    
    cache_dest.y = dest->y + (SDL_GetTicks() - time_stop) * speed;
    
    Blit_String(string, &cache_dest, screen);
    SDL_Flip(screen);
  }
  //animation end
}

//particles
void init_falling_particles(particle *particle_array, int elements, int x, int y, int w, int h)
{
  int particle_counter = 0;
  while(particle_counter < elements)
  {
    particle_array[particle_counter].x = x + rand() % w;
    particle_array[particle_counter].y = y + rand() % h;
    particle_counter++;
  }
}
void render_jet_flame(particle *particle_array, int elements, int x, int y, int w, int h, int speed)
{
  int particle_counter = 0;
  int max_movement;
  
  if(h > w)
    max_movement = (int)(h/w) + 1;
  else if(w > h)
    max_movement = (int)(w/h) + 1;
  else
    max_movement = 2;
  
  while(particle_counter < elements)
  {
    if(particle_array[particle_counter].y < y + h - rand() % h/(int)(rand() % w + 1))
    {
      if(particle_array[particle_counter].x < x + (w/2 + rand() % (int)(w/2)))
        particle_array[particle_counter].x += rand() % max_movement;
      if(particle_array[particle_counter].x > x + w - (w/2 + rand() % (int)(w/2)))
        particle_array[particle_counter].x -= rand() % max_movement;
      
      particle_array[particle_counter].y += speed;
    }
    else
    {
      particle_array[particle_counter].y = y;
      particle_array[particle_counter].x = x + rand() % w;
    }
    
    if(rand() % (elements) == 0)
    {
      break;
    }
    particle_counter++;
  }
}
void render_falling_particles(particle *particle_array, int elements, int x, int y, int w, int h, int speed)
{
  int particle_counter = 0;
  
  while(particle_counter < elements)
  {
    if(particle_array[particle_counter].y < y + h)
    {
      particle_array[particle_counter].y += speed;
    }
    else
    {
      particle_array[particle_counter].y = y;
      particle_array[particle_counter].x = x + rand() % w;
    }
    particle_counter++;
  }
}
void blit_particles(SDL_Surface *screen, particle *particle_array, int elements, unsigned char r, unsigned char g, unsigned char b)
{
  int particle_counter = 0;
  
  while(particle_counter < elements)
  {
    pixelRGBA(screen, particle_array[particle_counter].x, particle_array[particle_counter].y, r, g, b, 255);
    particle_counter++;
  }
}