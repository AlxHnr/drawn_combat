#include <level.h>

#define frog_speed 15

SDL_Surface *throw_sprite = NULL;
SDL_Surface *throw_stone = NULL;
SDL_Surface *throw_tile = NULL;

int init_throw_stones()
{
  if((throw_sprite = load_image("gfx/frog/sprite.png")) == NULL)
    return -1;
  if((throw_stone = load_image("gfx/frog/stone.png")) == NULL)
    return -1;
  if((throw_tile = load_image("gfx/frog/tile.jpg")) == NULL)
    return -1;
  
  return 0;
}
void quit_throw_stones()
{
  SDL_FreeSurface(throw_sprite);
  SDL_FreeSurface(throw_stone);
  SDL_FreeSurface(throw_tile);
}

int throw_stones(SDL_Surface *screen)
{
  char return_value = -1;
  SDL_Event user_input;
  
  //generate throw_tiled map start
  SDL_Rect cache_rect;
  SDL_Surface *map = SDL_ConvertSurface(screen, screen->format, screen->flags);
  cache_rect.y = 0;
  
  while(cache_rect.y < screen->h)
  {
    cache_rect.x = 0;
    while(cache_rect.x < screen->w)
    {
      SDL_BlitSurface(throw_tile, NULL, map, &cache_rect);
      cache_rect.x += throw_tile->w;
    }
    cache_rect.y += throw_tile->h;
  }
  
  vlineColor(map, throw_tile->w * 3, 0, map->h, 0x9F9F9FFF);
  
  cache_rect.x = throw_tile->w * 3/2;
  cache_rect.y = 50;
  
  while(cache_rect.y < screen->h)
  {
    filledCircleColor(map, cache_rect.x, cache_rect.y, 7, 0xFFFFFFFF);
    cache_rect.y += 200;
  }
  //generate throw_tiled map end
  
  cache_rect.x = screen->w/2 - throw_stone->w/2;
  cache_rect.y = 0;
  cache_rect.w = throw_stone->w;
  cache_rect.h = throw_stone->h;
  
  SDL_Rect frog_src;
  frog_src.x = 0;
  frog_src.y = throw_sprite->h/4*(rand() % 2 + 2);
  frog_src.w = throw_sprite->w/4;
  frog_src.h = throw_sprite->h/4;
  
  SDL_Rect frog_dest;
  frog_dest = frog_src;
  frog_dest.x = rand() % (screen->w/2 - throw_sprite->w/8);
  frog_dest.y = screen->h - throw_sprite->h/4;
  
  if((return_value = lvl_message(screen, lvl_2)) != 2)
    return return_value;
  
  SDL_BlitSurface(map, NULL, screen, NULL);
  
  while(return_value == 2)
  {
    //clear old graphics
    SDL_BlitSurface(map, &cache_rect, screen, &cache_rect);
    SDL_BlitSurface(map, &frog_dest, screen, &frog_dest);
    
    //handle user input
    while(SDL_PollEvent(&user_input))
    {
      switch(user_input.type)
      {
        case SDL_KEYDOWN:
          if(user_input.key.keysym.sym == SDLK_LEFT && cache_rect.y == 0 && cache_rect.x > throw_stone->w)
          {
            cache_rect.x -= frog_speed;
          }
          else if(user_input.key.keysym.sym == SDLK_RIGHT && cache_rect.y == 0 && cache_rect.x + throw_stone->w < screen->w)
          {
            cache_rect.x += frog_speed;
          }
          else if(user_input.key.keysym.sym == SDLK_SPACE && cache_rect.y == 0)
          {
            cache_rect.y += frog_speed;
          }
          break;
        case SDL_QUIT:
          return_value = 0;
          break;
        }
    }
    
    if(cache_rect.y > 0 && cache_rect.y + throw_stone->h < screen->h)
    {
      cache_rect.y += frog_speed;
    }
    else if(cache_rect.y + throw_stone->h >= screen->h)
    {
      cache_rect.y = 0;
    }
    
    if(frog_dest.x + throw_sprite->w/4 >= screen->w)
    {
      frog_src.y = frog_src.h*3;
    }
    else if(frog_dest.x <= 0)
    {
      frog_src.y = frog_src.h*2;
    }
    
    if(frog_src.y == frog_src.h*2)
    {
      //right
      if(frog_src.x == 0)
      {
        frog_src.x = frog_src.w;
      }
      else if(frog_src.x == frog_src.w)
      {
        frog_src.x = frog_src.w * 2;
      }
      else if(frog_src.x == frog_src.w * 2)
      {
        frog_src.x = frog_src.w * 3;
      }
      else if(frog_src.x == frog_src.w * 3)
      {
        frog_src.x = 0;
      }
      
      //pos_x
      frog_dest.x += frog_speed;
    }
    else
    {
      //left
      if(frog_src.x == 0)
      {
        frog_src.x = frog_src.w;
      }
      else if(frog_src.x == frog_src.w)
      {
        frog_src.x = frog_src.w * 2;
      }
      else if(frog_src.x == frog_src.w * 2)
      {
        frog_src.x = frog_src.w * 3;
      }
      else if(frog_src.x == frog_src.w * 3)
      {
        frog_src.x = 0;
      }
      
      //pos_x
      frog_dest.x -= frog_speed;
    }
    
    
    //calc throw_stone event + collision
    if(frog_dest.x + frog_dest.w >= cache_rect.x &&
        frog_dest.x <= cache_rect.x + cache_rect.w &&
        frog_dest.y + frog_dest.h >= cache_rect.y &&
        frog_dest.y <= cache_rect.y + cache_rect.h)
    {
      return_value = lvl_message(screen, "LEVEL 2 FERTIG!");
      break;
    }
    
    //blit grapics
    SDL_BlitSurface(throw_sprite, &frog_src, screen, &frog_dest);
    SDL_BlitSurface(throw_stone, NULL, screen, &cache_rect);
    
    SDL_Flip(screen);
    SDL_Delay(50);
    
    if(user_input.type == SDL_KEYDOWN && user_input.key.keysym.sym == SDLK_ESCAPE)
    {
      //call menu on escape
      return_value = call_game_menu(screen);
    }
  }
  SDL_FreeSurface(map);
  return return_value;
}