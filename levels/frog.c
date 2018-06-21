#include <level.h>

#define frog_speed 15

SDL_Surface *frog_sprite = NULL;
SDL_Surface *frog_bag_sprite = NULL;
SDL_Surface *frog_stone = NULL;
SDL_Surface *frog_tile = NULL;

int init_frog()
{
  if((frog_sprite = load_image("gfx/frog/sprite.png")) == NULL)
    return -1;
  if((frog_bag_sprite = load_image("gfx/frog/bag.png")) == NULL)
    return -1;
  if((frog_stone = load_image("gfx/frog/stone.png")) == NULL)
    return -1;
  if((frog_tile = load_image("gfx/frog/tile.jpg")) == NULL)
    return -1;
  
  return 0;
}
void quit_frog()
{
  SDL_FreeSurface(frog_sprite);
  SDL_FreeSurface(frog_bag_sprite);
  SDL_FreeSurface(frog_stone);
  SDL_FreeSurface(frog_tile);
}

int frog(SDL_Surface *screen)
{
  char return_value = -1;
  SDL_Event user_input;
  char key_button[323] = {0};
  
  unsigned char frog_stones = 0;
  
  //generate frog_tiled map start
  SDL_Rect cache_rect;
  SDL_Surface *map = SDL_ConvertSurface(screen, screen->format, screen->flags);
  SDL_FillRect(map, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
  cache_rect.y = 0;
  
  while(cache_rect.y < screen->h)
  {
    cache_rect.x = 0;
    while(cache_rect.x < screen->w)
    {
      SDL_BlitSurface(frog_tile, NULL, map, &cache_rect);
      cache_rect.x += frog_tile->w;
    }
    cache_rect.y += frog_tile->h;
  }
  
  vlineColor(map, frog_tile->w * 3, 0, map->h, 0x9F9F9FFF);
  
  cache_rect.x = frog_tile->w * 3/2;
  cache_rect.y = 50;
  
  while(cache_rect.y < screen->h)
  {
    filledCircleColor(map, cache_rect.x, cache_rect.y, 7, 0xFFFFFFFF);
    cache_rect.y += 200;
  }
  //generate frog_tiled map end
  
  cache_rect.y = 0;
  cache_rect.h = frog_stone->h;
  
  SDL_Rect frog_src;
  frog_src.x = 0;
  frog_src.y = 0;
  frog_src.w = frog_sprite->w/4;
  frog_src.h = frog_sprite->h/4;
  
  SDL_Rect frog_dest;
  frog_dest = frog_src;
  frog_dest.x = screen->w/2 - frog_sprite->w/8;
  frog_dest.y = screen->h/2 - frog_sprite->h/8;
  
  SDL_Surface *frog_bag_sprite_cache = rotozoomSurface(frog_bag_sprite, 0, 0.25, 0);
  
  SDL_Rect frog_backpack_src;
  frog_backpack_src.x = 0;
  frog_backpack_src.y = 0;
  frog_backpack_src.w = frog_bag_sprite_cache->w/4;
  frog_backpack_src.h = frog_bag_sprite_cache->h;
  
  SDL_Rect frog_backpack_dest;
  frog_backpack_dest = frog_backpack_src;
  
  SDL_Rect frog_stone_dest;
  frog_stone_dest.x = rand() % (screen->w - frog_stone->w);
  frog_stone_dest.y = rand() % (screen->h - frog_stone->h);
  
  if((return_value = lvl_message(screen, lvl_1)) != 2)
    return return_value;
  
  SDL_BlitSurface(map, NULL, screen, NULL);
  
  //lvl 1 main loop
  while(return_value == 2)
  {
    //clear old graphics
    cache_rect.x = 0;
    cache_rect.w = 40 + frog_stone->w;
    SDL_BlitSurface(map, &cache_rect, screen, &cache_rect);
    SDL_BlitSurface(map, &frog_dest, screen, &frog_dest);
    SDL_BlitSurface(map, &frog_backpack_dest, screen, &frog_backpack_dest);
    
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
    //direction
    if(key_button[SDLK_UP])
    {
      frog_src.y = frog_src.h;
      frog_backpack_src.x = frog_backpack_src.w;
      
      //frame
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
      
      //pos_y
      if(frog_dest.y > frog_speed)
        frog_dest.y -= frog_speed;
    }
    else if(key_button[SDLK_DOWN])
    {
      frog_src.y = 0;
      frog_backpack_src.x = 0;
      
      //frame
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
      
      //pos_y
      if(frog_dest.y + frog_dest.h + frog_speed < screen->h)
        frog_dest.y += frog_speed;
    }
    else if(key_button[SDLK_LEFT])
    {
      frog_src.y = frog_src.h*3;
      frog_backpack_src.x = frog_backpack_src.w*3;
      
      //frame
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
      if(frog_dest.x > frog_speed)
        frog_dest.x -= frog_speed;
    }
    else if(key_button[SDLK_RIGHT])
    {
      frog_src.y = frog_src.h*2;
      frog_backpack_src.x = frog_backpack_src.w*2;
      
      //frame
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
      if(frog_dest.x + frog_dest.w  + frog_speed < screen->w)
        frog_dest.x += frog_speed;
    }

    //calc frog_stone event + collision
    if(frog_dest.x + frog_dest.w >= frog_stone_dest.x &&
        frog_dest.x <= frog_stone_dest.x + frog_stone_dest.w &&
        frog_dest.y + frog_dest.h >= frog_stone_dest.y &&
        frog_dest.y <= frog_stone_dest.y + frog_stone_dest.h)
    {
      frog_stones++;
      
      //clear old frog_stone
      SDL_BlitSurface(map, &frog_stone_dest, screen, &frog_stone_dest);
      
      if(frog_stones > 12)
      {
        SDL_FreeSurface(frog_bag_sprite_cache);
        frog_bag_sprite_cache = rotozoomSurface(frog_bag_sprite, 0, frog_stones * 0.02, 0);

        frog_backpack_src.w = frog_bag_sprite_cache->w/4;
        frog_backpack_src.h = frog_bag_sprite_cache->h;
        
        if(frog_src.y == frog_src.h)
          frog_backpack_src.x = frog_backpack_src.w;
        else if(frog_src.y == 0)
          frog_backpack_src.x = 0;
        else if(frog_src.y == frog_src.h*2)
          frog_backpack_src.x = frog_backpack_src.w*2;
        else if(frog_src.y == frog_src.h*3)
          frog_backpack_src.x = frog_backpack_src.w*3;
        
        frog_backpack_dest = frog_backpack_src;
      }
      
      frog_backpack_src.w = frog_bag_sprite_cache->w/4;
      frog_backpack_src.h = frog_bag_sprite_cache->h;
      
      frog_backpack_dest = frog_backpack_src;
      
      frog_stone_dest.x = rand() % (screen->w - frog_stone->w);
      frog_stone_dest.y = rand() % (screen->h - frog_stone->h);
    }
    
    //calc graphic values
    frog_backpack_dest.x = (frog_dest.x + frog_src.w/2) - frog_backpack_src.w/2;
    frog_backpack_dest.y = (frog_dest.y + frog_src.h - frog_src.h/3) - frog_backpack_src.h;
    
    //blit grapics
    SDL_BlitSurface(frog_stone, NULL, screen, &frog_stone_dest);
    SDL_BlitSurface(frog_sprite, &frog_src, screen, &frog_dest);
    SDL_BlitSurface(frog_bag_sprite_cache, &frog_backpack_src, screen, &frog_backpack_dest);
    
    if(frog_src.y == 0)
    {
      SDL_BlitSurface(frog_sprite, &frog_src, screen, &frog_dest);
    }
    
    SDL_BlitSurface(frog_stone, NULL, screen, &cache_rect);
    cache_rect.x += frog_stone->w;
    Blit_Int(frog_stones, &cache_rect, screen);
    SDL_Flip(screen);
    SDL_Delay(50);
    
    if(frog_stones == 50)
    {
      return_value = lvl_message(screen, "LEVEL 1 FERTIG!");
      break;
    }
    
    if(key_button[SDLK_ESCAPE])
    {
      //call menu on escape
      return_value = call_game_menu(screen);
      key_button[SDLK_ESCAPE] = 0;
    }
  }
  SDL_FreeSurface(map);
  SDL_FreeSurface(frog_bag_sprite_cache);
  return return_value;
}