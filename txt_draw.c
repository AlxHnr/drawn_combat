#include <txt_draw.h>

SDL_Surface *key_map = NULL;

int init_txt_draw()
{
  if((key_map = load_image(key_map_path)) == NULL)
    return -1;
  
  return 0;
}
void txt_draw_quit()
{
  SDL_FreeSurface(key_map);
}

unsigned short get_string_w(char* string)
{
  unsigned short pos = 0;
  unsigned short string_w = 0;
  unsigned short cache_w = 0;
  
  while(string[pos] != '\0')
  {
    if(string[pos] == '\n')
    {
      if(cache_w > string_w)
      {
        string_w = cache_w;
      }
      cache_w = 1;
    }
    cache_w++;
    pos++;
  }
  
  if(string_w == 0)
  {
    string_w = strlen(string);
  }
  
  return string_w;
}
unsigned short get_string_h(char* string)
{
  unsigned short pos = 0;
  unsigned short string_h = 1;
  
  while(string[pos] != '\0')
  {
    if(string[pos] == '\n')
    {
      string_h++;
    }
    pos++;
  }
  
  return string_h;
}

void Blit_Int(int num, SDL_Rect *dest, SDL_Surface *screen)
{
  char cache_string[12];
  sprintf(cache_string, "%i", num);
  
  Blit_String(cache_string, dest, screen);
}
void Blit_String(char *string, SDL_Rect *dest, SDL_Surface *screen)
{
  unsigned short pos = 0;
  char cache_char;
  
  if(dest == NULL)
  {
    SDL_Rect cache_rect = {0, 0, 0, 0};
    dest = &cache_rect;
  }
  
  SDL_Rect cache_dest;
  cache_dest.x = dest->x;
  cache_dest.y = dest->y;
  
  SDL_Rect src;
  src.w = 20;
  src.h = 20;
  
  while(string[pos] != '\0')
  {
    cache_char = string[pos];
    
    if(cache_char >= 'a' && cache_char <= 'z')
    {
      cache_char -= 'a';
    }
    else if(string[pos] >= 'A' && string[pos] <= 'Z')
    {
      cache_char -= 'A';
    }
    else if(string[pos] >= '0' && string[pos] <= '9')
    {
      cache_char -= '0' - 26;
    }
    else if(string[pos] == '.')
    {
      cache_char = 36;
    }
    else if(string[pos] == ':')
    {
      cache_char = 37;
    }
    else if(string[pos] == '!')
    {
      cache_char = 38;
    }
    else if(string[pos] == '?')
    {
      cache_char = 39;
    }
    else if(string[pos] == '(')
    {
      cache_char = 40;
    }
    else if(string[pos] == ')')
    {
      cache_char = 41;
    }
    else if(string[pos] == '\n')
    {
      cache_dest.x = dest->x;
      cache_dest.y += 20;
      pos++;
      continue;
    }
    else
    {
      pos++;
      cache_dest.x += 20;
      continue;
    }
    
    src.x = 0;
    src.y = 0;
    
    while(cache_char > 0)
    {
      if(cache_char >= 6)
      {
        cache_char -= 6;
        src.y += 20;
      }
      else
      {
        cache_char--;
        src.x += 20;
      }
    }
    
    SDL_BlitSurface(key_map, &src, screen, &cache_dest);
    cache_dest.x += 20;
    pos++;
  }
}