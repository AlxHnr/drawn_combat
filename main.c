#include <SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <txt_draw.h>
#include <menu.h>
#include <level.h>

#define win_message "GEWONNEN!!!"

#ifdef __WIN32__
  int WinMain(int argc, char *argv[])
#else
  int main(int argc, char *argv[])
#endif
{
  //variables
  SDL_Surface *screen = NULL;
  SDL_Surface *drawn_combat_icon = NULL;
  SDL_Event user_input;
  
  unsigned char particle_counter = 0;
  particle win_particles[20][5000];
  
  drawn_combat_icon = SDL_LoadBMP("gfx/drawn_combat.bmp");
  
  //0 = exit, 1 = main_menu, 2 = game
  char program_run = 1;
  
  //init SDL start
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    exit(-1);
  
  SDL_WM_SetCaption("Drawn Combat", NULL);
  SDL_WM_SetIcon(drawn_combat_icon, NULL);
  
  if((screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE)) == NULL)
    exit(-1);
  atexit(SDL_Quit);
  SDL_EnableKeyRepeat(200, 50);
  SDL_ShowCursor(0);
  //init SDL end
  
  
  //init libs start
  if(init_txt_draw() == -1)
    exit(-1);
  atexit(txt_draw_quit);
  
  if(init_menu() == -1)
    exit(-1);
  atexit(menu_quit);
  
  if(init_levels() == -1)
    exit(-1);
  atexit(levels_quit);
  //init libs end
  
  //main loop start
  while(program_run != 0)
  {
    if(program_run == 1)
    {
      program_run = call_main_menu(screen);
    }
    if(program_run == 2)
    {
      if((program_run = frog(screen)) != 2)
        continue;
      if((program_run = throw_stones(screen)) != 2)
        continue;
      if((program_run = rocket_flight(screen)) != 2)
        continue;
      
      particle_counter = 0;
      while(particle_counter < 20)
      {
        init_falling_particles(win_particles[particle_counter], 5000, 0, 0, screen->w, screen->h);
        particle_counter++;
      }
      
      while(program_run == 2)
      {
        //calc
        particle_counter = 0;
        while(particle_counter < 10)
        {
          render_falling_particles(win_particles[particle_counter], 5000, 0, 0, screen->w, screen->h, 1);
          particle_counter++;
        }
        while(particle_counter < 20)
        {
          render_jet_flame(win_particles[particle_counter], 5000, 0, 0, screen->w, screen->h, 1);
          particle_counter++;
        }
        
        //draw
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        
        particle_counter = 0;
        while(particle_counter < 20)
        {
          blit_particles(screen, win_particles[particle_counter], 5000, rand() % 255, rand() % 255, rand() % 255);
          particle_counter++;
        }
        
        Blit_String(win_message, NULL, screen);
        SDL_Flip(screen);
                
        while(SDL_PollEvent(&user_input))
        {
          if(user_input.type == SDL_KEYDOWN && user_input.key.keysym.sym == SDLK_SPACE)
            program_run = 1;
          else if(user_input.type == SDL_QUIT)
            program_run = 0;
        }
      }
    }
  }
  //main loop end
  
  SDL_FreeSurface(screen);
  return 0;
}