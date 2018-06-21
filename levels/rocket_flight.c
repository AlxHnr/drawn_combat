#include <level.h>

#define rocket_speed 5
#define rocket_flame_start_h 30

#define dark_flame_particles 500
#define mid_flame_particles 350
#define bright_flame_particles 250

#define line_w rocket_speed
#define line_particle_amount 2500

SDL_Surface *rocket_tile = NULL;
SDL_Surface *rocket = NULL;

int init_rocket_flight()
{
  SDL_Surface *cache_surface = NULL;
  
  if((rocket_tile = load_image("gfx/frog/tile.jpg")) == NULL)
    return -1;
  if((cache_surface = load_image("gfx/pencil.png")) == NULL)
    return -1;
  rocket = rotozoomSurface(cache_surface, 90, 1, 0);
  SDL_FreeSurface(cache_surface);
  
  return 0;
}
void quit_rocket_flight()
{
  SDL_FreeSurface(rocket_tile);
  SDL_FreeSurface(rocket);
}

int rocket_flight(SDL_Surface *screen)
{
  char return_value = -1;
  SDL_Event user_input;
  char key_button[323] = {0};
  
  Uint32 starting_time = SDL_GetTicks();
  Uint32 time_stop;
  
  //map vars
  SDL_Rect first_row;
  first_row.x = 0;
  first_row.y = 0;
  first_row.w = rocket_tile->w;
  
  char y_movement = 0;
  int paper_hole_pos_y = 50;
  
  unsigned char map_scroll_speed = 1;
  unsigned char time_scroll_movement = 0;
  
  //rocket vars
  SDL_Rect cache_rect;
  
  SDL_Rect rocket_dest;
  rocket_dest.x = screen->w/2 - rocket->w/2;
  rocket_dest.y = screen->h - rocket->h - rocket_flame_start_h;
  rocket_dest.w = rocket->w;
  rocket_dest.h = rocket->h;
  
  //init fire particles start
  unsigned char flame_h = rocket_flame_start_h;
  
  particle dark_flame[dark_flame_particles];
  particle mid_flame[mid_flame_particles];
  particle bright_flame[bright_flame_particles];
  
  init_falling_particles(dark_flame, dark_flame_particles, rocket_dest.x, rocket_dest.y + rocket->h, rocket->w, flame_h);
  init_falling_particles(mid_flame, mid_flame_particles, rocket_dest.x, rocket_dest.y + rocket->h, rocket->w, flame_h);
  init_falling_particles(bright_flame, bright_flame_particles, rocket_dest.x, rocket_dest.y + rocket->h, rocket->w, flame_h);
  //init fire particles end
  
  //init line particles start
  particle line_particle[line_particle_amount];
  init_falling_particles(line_particle, line_particle_amount, rocket_dest.x + rocket->w/2 - line_w/2, rocket_dest.y, line_w, screen->h - rocket_dest.y);
  //init line particles end
  
  if((return_value = lvl_message(screen, lvl_3)) != 2)
    return return_value;
  
  SDL_BlitSurface(rocket, NULL, screen, &rocket_dest);
  SDL_Flip(screen);
  
  while(return_value == 2)
  {
    time_stop = SDL_GetTicks();
    //render map start
    if(y_movement >= rocket_tile->h)
      y_movement = 0;
    else
      y_movement += time_scroll_movement;
    
    //calc and draw first row
    if(y_movement > 0)
    {
      first_row.y = rocket_tile->h - y_movement;
      first_row.h = y_movement;
      
      cache_rect.x = 0;
      cache_rect.y = 0;
      while(cache_rect.x < screen->w)
      {
        SDL_BlitSurface(rocket_tile, &first_row, screen, &cache_rect);
        cache_rect.x += rocket_tile->w;
      }
    }
    
    //calc and draw other rows
    
    cache_rect.y = y_movement;
    while(cache_rect.y < screen->h)
    {
      cache_rect.x = 0;
      while(cache_rect.x < screen->w)
      {
        SDL_BlitSurface(rocket_tile, NULL, screen, &cache_rect);
        cache_rect.x += rocket_tile->w;
      }
      cache_rect.y += rocket_tile->h;
    }
    
    //draw line
    vlineColor(screen, rocket_tile->w * 3, 0, screen->h, 0x9F9F9FFF);
    
    //calc and draw holes
    if(paper_hole_pos_y >= 200)
      paper_hole_pos_y = 0;
    else
      paper_hole_pos_y += time_scroll_movement;
    
    cache_rect.x = rocket_tile->w * 3/2;
    cache_rect.y = paper_hole_pos_y;
    
    while(cache_rect.y < screen->h)
    {
      filledCircleColor(screen, cache_rect.x, cache_rect.y, 7, 0xFFFFFFFF);
      cache_rect.y += 200;
    }
    //render map end
    
    //handle user input
    while(SDL_PollEvent(&user_input))
    {
      switch(user_input.type)
      {
        case SDL_KEYDOWN:
          key_button[user_input.key.keysym.sym] = 1;
          break;
        case SDL_KEYUP:
          key_button[user_input.key.keysym.sym] = 0;
          break;
        case SDL_QUIT:
          return_value = 0;
          break;
      }
    }
    
    if(key_button[SDLK_LEFT] && rocket_dest.x > 0)
    {
      rocket_dest.x -= rocket_speed * time_scroll_movement;
    }
    else if(key_button[SDLK_RIGHT] && rocket_dest.x + rocket->w < screen->w)
    {
      rocket_dest.x += rocket_speed * time_scroll_movement;
    }
    
    //calc graphics
    render_jet_flame(dark_flame, dark_flame_particles, rocket_dest.x, rocket_dest.y + rocket->h, rocket->w, flame_h, time_scroll_movement);
    render_jet_flame(mid_flame, mid_flame_particles, rocket_dest.x, rocket_dest.y + rocket->h, rocket->w, flame_h, time_scroll_movement);
    render_jet_flame(bright_flame, bright_flame_particles, rocket_dest.x, rocket_dest.y + rocket->h, rocket->w, flame_h, time_scroll_movement);
    
    render_falling_particles(line_particle, line_particle_amount, rocket_dest.x + rocket->w/2 - line_w/2, rocket_dest.y, line_w, screen->h - rocket_dest.y, time_scroll_movement);
    
    //draw new graphics
    blit_particles(screen, line_particle, line_particle_amount, 0, 0, 0);
    
    blit_particles(screen, dark_flame, dark_flame_particles, 0, 0, 0);
    blit_particles(screen, mid_flame, mid_flame_particles, 100, 100, 100);
    blit_particles(screen, bright_flame, bright_flame_particles, 255, 255, 255);
    
    SDL_BlitSurface(rocket, NULL, screen, &rocket_dest);
    
    SDL_Flip(screen);
    
    if(user_input.type == SDL_KEYDOWN && user_input.key.keysym.sym == SDLK_ESCAPE)
    {
      //call menu on escape
      return_value = call_game_menu(screen);
      time_stop = SDL_GetTicks();
    }
    
    //calc movement per frame
    time_scroll_movement = (int)(100/(1000.0f/(SDL_GetTicks() - time_stop))) * map_scroll_speed;
    while(time_scroll_movement == 0)
    {
      SDL_Delay(1);
      time_scroll_movement = (int)(100/(1000.0f/(SDL_GetTicks() - time_stop))) * map_scroll_speed;
    }
    
    if(SDL_GetTicks() - starting_time >= 15000)
    {
      return_value = lvl_message(screen, "LEVEL 3 FERTIG!");
      break;
    }
  }
  
  return return_value;
}