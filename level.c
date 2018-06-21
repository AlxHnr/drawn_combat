#include <level.h>

int init_levels()
{
  if(init_frog() == -1)
    return -1;
  if(init_throw_stones() == -1)
    return -1;
  if(init_rocket_flight() == -1)
    return -1;
  
  return 0;
}
void levels_quit()
{
  quit_frog();
  quit_throw_stones();
  quit_rocket_flight();
}
char lvl_message(SDL_Surface *screen, char *lvl_txt)
{
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
  SDL_Surface *screen_shot = SDL_ConvertSurface(screen, screen->format, screen->flags);
  SDL_Rect cache_rect;
  SDL_Event user_input;
  char return_value = -1;
  
  cache_rect.x = screen->w/2 - get_string_w(lvl_txt) * 10;
  cache_rect.y = screen->h/2 - get_string_h(lvl_txt) * 10;
  move_in_string(lvl_txt, screen_shot, screen, &cache_rect, 1);
    
  while(return_value == -1)
  {
    //handle user input
    SDL_WaitEvent(&user_input);
    if(user_input.type == SDL_KEYDOWN)
    {
      if(user_input.key.keysym.sym == SDLK_SPACE)
      {
        return_value = 2;
      }
      else if(user_input.key.keysym.sym == SDLK_ESCAPE)
      {
        //call menu on escape
        return_value = call_game_menu(screen);
        if(return_value == 2)
          return_value = -1;
      }
    }
    if(user_input.type == SDL_QUIT)
    {
      return_value = 0;
    }
  }
  move_out_string(lvl_txt, screen_shot, screen, &cache_rect, 1);
  
  SDL_FreeSurface(screen_shot);
  return return_value;
}