#include <menu.h>

SDL_Surface *drawn_combat_logo = NULL;
SDL_Surface *pencil = NULL;
SDL_Surface *game_menu_background = NULL;

int init_menu()
{
  if((drawn_combat_logo = load_image(drawn_combat_logo_path)) == NULL)
    return -1;
  if((pencil = load_image(pencil_path)) == NULL)
    return -1;
  if((game_menu_background = load_image(game_menu_background_path)) == NULL)
    return -1;
  
  return 0;
}
void menu_quit()
{
  SDL_FreeSurface(drawn_combat_logo);
  SDL_FreeSurface(pencil);
  SDL_FreeSurface(game_menu_background);
}

int call_main_menu(SDL_Surface *screen)
{
  //vars
  int return_value = -1;
  
  SDL_Event user_input;
  SDL_Rect cache_dest;
  
  //clear screen
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
  
  //safe screen_shot
  SDL_Surface *screen_shot = SDL_ConvertSurface(screen, screen->format, screen->flags);
  
  //open menu
  cache_dest.x = screen->w/2 - drawn_combat_logo->w/2;
  cache_dest.y = 0;
  move_in_surface(drawn_combat_logo, screen_shot, screen, &cache_dest, main_menu_open_speed);
  
  //write menu text
  cache_dest.x = pencil->w;
  cache_dest.y = drawn_combat_logo->h;
  
  move_in_string(main_menu_text_1, screen_shot, screen, &cache_dest, main_menu_open_speed);
  cache_dest.y += 20;
  move_in_string(main_menu_text_2, screen_shot, screen, &cache_dest, main_menu_open_speed);
  
  //animate pencil
  cache_dest.x = 0;
  cache_dest.y = drawn_combat_logo->h;
  cache_dest.w = pencil->w;
  cache_dest.h = pencil->h;
  move_in_surface(pencil, screen_shot, screen, &cache_dest, main_menu_open_speed);
  
  while(return_value == -1)
  {
    SDL_WaitEvent(&user_input);
    if(user_input.type == SDL_KEYDOWN)
    {
      //clear old pencil
      SDL_FillRect(screen, &cache_dest, SDL_MapRGB(screen->format, 255, 255, 255));
      
      //handle user_input
      if(user_input.key.keysym.sym == SDLK_UP && cache_dest.y > drawn_combat_logo->h)
      {
        cache_dest.y -= 20;
      }
      else if(user_input.key.keysym.sym == SDLK_DOWN && cache_dest.y < drawn_combat_logo->h + 20)
      {
        cache_dest.y += 20;
      }
      else if(user_input.key.keysym.sym == SDLK_SPACE)
      {
        if(cache_dest.y == drawn_combat_logo->h)
        {
          //if menu entry 1
          return_value = 2;
        }
        else if(cache_dest.y == drawn_combat_logo->h + 20)
        {
          //if menu entry 2
          return_value = 0;
        }
      }
      
      //draw new pencil
      SDL_BlitSurface(pencil, NULL, screen, &cache_dest);
      SDL_Flip(screen);
    }
    else if(user_input.type == SDL_QUIT)
    {
      return_value = 0;
    }

  }
  
  //animate pencil
  move_out_surface(pencil, screen_shot, screen, &cache_dest, main_menu_close_speed);
  
  //animate menu text
  cache_dest.x = pencil->w;
  cache_dest.y = drawn_combat_logo->h + 20;
  
  move_out_string(main_menu_text_2, screen_shot, screen, &cache_dest, main_menu_close_speed);
  cache_dest.y -= 20;
  move_out_string(main_menu_text_1, screen_shot, screen, &cache_dest, main_menu_close_speed);
  
  //close menu
  cache_dest.x = screen->w/2 - drawn_combat_logo->w/2;
  cache_dest.y = 0;
  move_out_surface(drawn_combat_logo, screen_shot, screen, &cache_dest, main_menu_close_speed);
  
  SDL_FreeSurface(screen_shot);
  return return_value;
}
int call_game_menu(SDL_Surface *screen)
{
  //vars
  int return_value = -1;
  
  SDL_Surface *screen_shot = SDL_ConvertSurface(screen, screen->format, screen->flags);
  SDL_Surface *screen_shot_2 = NULL;
  
  SDL_Event user_input;
  SDL_Rect cache_dest;
  SDL_Rect cache_2_dest;
  
  //move in game_menu_background
  cache_dest.x = screen->w/2 - game_menu_background->w/2;
  cache_dest.y = screen->h/2 - game_menu_background->h/2;
  
  move_in_surface(game_menu_background, screen_shot, screen, &cache_dest, game_menu_open_speed);
  screen_shot_2 = SDL_ConvertSurface(screen, screen->format, screen->flags);
  
  //move in game_menu_text
  cache_dest.x += 4 + pencil->w;
  cache_dest.y += 32;
  move_in_string(game_menu_text_1, screen_shot_2, screen, &cache_dest, game_menu_open_speed);
  cache_dest.y += 20;
  move_in_string(game_menu_text_2, screen_shot_2, screen, &cache_dest, game_menu_open_speed);
  cache_dest.y += 20;
  move_in_string(game_menu_text_3, screen_shot_2, screen, &cache_dest, game_menu_open_speed);
  
  //move in pencil
  cache_dest.x -= pencil->w;
  cache_dest.y -= 40;
  move_in_surface(pencil, screen_shot_2, screen, &cache_dest, game_menu_open_speed);
  
  while(return_value == -1)
  {
    //handle user input
    SDL_WaitEvent(&user_input);
    if(user_input.type == SDL_KEYDOWN)
    {
      //handle user_input
      if(user_input.key.keysym.sym == SDLK_UP && cache_dest.y > (screen->h/2 - game_menu_background->h/2) + 32)
      {
        cache_dest.y -= 20;
      }
      else if(user_input.key.keysym.sym == SDLK_DOWN && cache_dest.y < (screen->h/2 - game_menu_background->h/2) + 72)
      {
        cache_dest.y += 20;
      }
      else if(user_input.key.keysym.sym == SDLK_SPACE)
      {
        if(cache_dest.y == (screen->h/2 - game_menu_background->h/2) + 32)
        {
          //menu entry 1
          return_value =  2;
        }
        else if(cache_dest.y == (screen->h/2 - game_menu_background->h/2) + 52)
        {
          //menu entry 2
          return_value = 1;
        }
        else if(cache_dest.y == (screen->h/2 - game_menu_background->h/2) + 72)
        {
          //menu entry 3
          return_value = 0;
        }
      }
      else if(user_input.key.keysym.sym == SDLK_ESCAPE)
      {
        return_value = 2;
      }
    }
    else if(user_input.type == SDL_QUIT)
    {
      return_value = 0;
    }
    
    //redraw menu
    cache_2_dest.x = screen->w/2 - game_menu_background->w/2;
    cache_2_dest.y = screen->h/2 - game_menu_background->h/2;
    cache_2_dest.w = game_menu_background->w;
    cache_2_dest.h = game_menu_background->h;
    
    SDL_BlitSurface(game_menu_background, NULL, screen, &cache_2_dest);
    
    cache_2_dest.x += 4 + pencil->w;
    cache_2_dest.y += 32;
    Blit_String(game_menu_text_1, &cache_2_dest, screen);
    cache_2_dest.y += 20;
    Blit_String(game_menu_text_2, &cache_2_dest, screen);
    cache_2_dest.y += 20;
    Blit_String(game_menu_text_3, &cache_2_dest, screen);
    
    SDL_BlitSurface(pencil, NULL, screen, &cache_dest);
    SDL_Flip(screen);
  }
  
  move_out_surface(pencil, screen_shot_2, screen, &cache_dest, game_menu_close_speed);
  
  cache_dest.x += pencil->w;
  cache_dest.y = (screen->h/2 - game_menu_background->h/2) + 72;
  
  move_out_string(game_menu_text_3, screen_shot_2, screen, &cache_dest, game_menu_close_speed);
  cache_dest.y -= 20;
  move_out_string(game_menu_text_2, screen_shot_2, screen, &cache_dest, game_menu_close_speed);
  cache_dest.y -= 20;
  move_out_string(game_menu_text_1, screen_shot_2, screen, &cache_dest, game_menu_close_speed);
  
  cache_dest.x = screen->w/2 - game_menu_background->w/2;
  cache_dest.y = screen->h/2 - game_menu_background->h/2;
  move_out_surface(game_menu_background, screen_shot, screen, &cache_dest, game_menu_close_speed);
    
  SDL_FreeSurface(screen_shot);
  SDL_FreeSurface(screen_shot_2);
  return return_value;
}