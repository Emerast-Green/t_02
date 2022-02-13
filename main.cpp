#include <stdio.h>
#include <cstring>
#include <iostream>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <typeinfo>
#include "own.cpp"
#include <map>

#define WIDTH 640
#define HEIGHT 480
#define FPS 30
#define SIZE 100


class Colour
{
  public:
    int r;
    int g;
    int b;
    Colour(int R, int G, int B){
      r = R; g = G; b = B;
    };
};

class Custom_Renderer
{
  private:
    SDL_Rect rect;
    std::map<Entity_Type,Colour> colors;
    std::list<Entity>::iterator iter;
    int tmp[3];
  public:
    int entity_color[3];
    void init(Colour pl_col,Colour st_col, Colour it_col, Colour npc_col)
    {
      colors.insert(std::pair<Entity_Type,Colour>(Player,pl_col));
      colors.insert(std::pair<Entity_Type,Colour>(Storage,st_col));
      colors.insert(std::pair<Entity_Type,Colour>(Item,it_col));
      colors.insert(std::pair<Entity_Type,Colour>(NPC,npc_col));
    };
    // void define_colour(Entity_Type entp, int r, int g, int b)
    // {
    //   tmp[0]=r;tmp[1]=g;tmp[2]=b;
    //   colors[entp] = tmp;
    // };
    int Draw(SDL_Renderer* rend, Symulation S)
    {
      for(iter = S.ents.begin(); iter != S.ents.end(); iter++)
      {
        rect.x=iter->hb.pos[0]; rect.y=iter->hb.pos[1];
        rect.w=iter->hb.size[0];rect.h=iter->hb.size[1];
        SDL_SetRenderDrawColor(rend, colors.at(iter->et).r, colors.at(iter->et).g, colors.at(iter->et).b, 255);
        if(iter->GetName()=="test1"){std::cout << iter->hb.pos[1] << "|" << rect.y << std::endl;};
        SDL_RenderFillRect(rend, &rect);
      };
      return 0;
    };
};

int main(int argc, char* argv[])
{
  /*Window creation*/
  SDL_Window* wind = SDL_CreateWindow("Test 02!",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WIDTH, HEIGHT, 0);
  if (!wind)
  {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return 0;
  }
  /*Renderer*/
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);
  if (!rend)
  {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
  }

  Custom_Renderer cust_rend;
  Symulation sym;
  Colour pl_col(0,255,0);
  Colour st_col(255,0,0);
  Colour it_col(255,0,255);
  Colour npc_col(0,0,255);
  cust_rend.init(pl_col,st_col,it_col,npc_col);
  Entity t1(10,10,200,200,"test1",Player);
  Entity t2(0,300,50,50,"hitbox1",NPC);
  sym.AddEntity(t1);
  sym.AddEntity(t2);
  SDL_Event event;
  bool running = true;

  /*Loop */
  while(running)
  {
    while(SDL_PollEvent(&event))
    {
      int x; int y;
      SDL_GetMouseState(&x, &y);
      switch(event.type)
      {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.scancode)
          {
            case SDL_SCANCODE_Q:
              break;
            case SDL_SCANCODE_S:
              break;
            case SDL_SCANCODE_W:
              break;
            case SDL_SCANCODE_D:
              break;
            case SDL_SCANCODE_A:
              break;
            default:
              break;
          };
          break;
        case SDL_KEYUP:
          switch(event.key.keysym.scancode)
          {
            case SDL_SCANCODE_S:
              break;
            case SDL_SCANCODE_W:
              break;
            case SDL_SCANCODE_D:
              break;
            case SDL_SCANCODE_A:
              break;
            default:
              break;
          };
          break;
        default:
          break;
      };
    };
    /*Clear*/
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    /*Render widgets*/
    cust_rend.Draw(rend,sym);
    std::cout << t1.hb.pos[0] << "/" << t1.hb.pos[1] << std::endl;
    std::cout << "COLL:" << t1.hb.Move(0,10,sym) << std::endl;
    //std::cout <<  << " " << t1.hb.pos[1] <<std::endl; 
    /* Draw to window and loop */
    SDL_RenderPresent(rend);
    SDL_Delay(1000/FPS);
  };
  /* Release resources */
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(wind);
  SDL_Quit();
  return 0;
};