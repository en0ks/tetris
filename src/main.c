//For some reason after n garbage blocks have been added, the move
//barrier ceases to work. TODO: Fix this.
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <limits.h>
#include "header.h"
#include "functions.c"

/* Create the struct User which holds information about the current falling
   block. This struct comprises another struct Tet. This struct Tet holds
   information about the all seven tetromino pieces. When doing operations
   on the User tetromino, we check the struct User, and procede according to
   this struct User and Tet. */
  
int main(int argc, char *argv[]){

  srand(time(NULL));
  
  /* Refactor code: develop this game without the questionable array int **board.
     Doing this will make this code easier extensibe code. */
  
  /* SDL start  */
  SDL_Event event;
  int quit = 0;
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0){	
    printf("Initialization failed.");		
    return 1;
  }
  
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  
  /* Positive x-axis and negative y-axis.  */
  window = SDL_CreateWindow("Quad", 0, 0, WIDTH, HEIGHT, 0);
  
  if(!window){
    printf("Initializing window failed.");
    return 1; 		  
  }
  
  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  if(!renderer){
    printf("Initializing renderer failed");
    return 1; 		  
  }
  
  struct User_Tetromino user_tetromino = {0};
  struct Garbage *garbage = malloc(sizeof(struct Garbage) + 1 * sizeof(struct Tetromino));

  (*garbage).cnt = 0;
  
  struct timespec start;
  struct timespec current;
  
  int time_elapsed_ms = 0;
  int delay = 400;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  int size = 1;
  
  while(!quit){
    
    if(garbage->cnt == 1){
      garbage = realloc(garbage, sizeof(struct Garbage) + ++size * 1 * sizeof(struct Tetromino));
    }
    
    //Spawn
    if(user_tetromino.busy == 0){
      delay = 400;
      spawn(&user_tetromino, get_random_number());
    }

    //Fall
    clock_gettime(CLOCK_MONOTONIC_RAW, &current);
    time_elapsed_ms = (current.tv_sec - start.tv_sec)*1000 + (current.tv_nsec - start.tv_nsec)/1000000;
    
    if(time_elapsed_ms > delay){
      clock_gettime(CLOCK_MONOTONIC_RAW, &start);
      if(user_tetromino.busy == 1){       
	gravitate(&user_tetromino, garbage);    
      }
    }

    clear_line(garbage);
    
    while(SDL_PollEvent(&event)){

      switch(event.type){
 		  
      case SDL_KEYDOWN:
	if(event.key.keysym.sym==SDLK_x){
	  rotate(&user_tetromino, garbage, 0, user_tetromino.tetromino.type);
	}
	if(event.key.keysym.sym==SDLK_c || event.key.keysym.sym==SDLK_UP){
	  rotate(&user_tetromino, garbage, 1, user_tetromino.tetromino.type);	  
	}
	if(event.key.keysym.sym==SDLK_DOWN || event.key.keysym.sym==SDLK_SPACE){
	  sdrop(&delay);
	}
	if(event.key.keysym.sym==SDLK_LEFT){
	  mov(&user_tetromino, garbage, 0);
	} 
	if(event.key.keysym.sym==SDLK_RIGHT){
	  mov(&user_tetromino, garbage, 1);	  
	}
	if(SDL_GetModState() == KMOD_LCTRL){
	  if(event.key.keysym.sym==SDLK_F4){
	    event.type = SDL_QUIT;
	    SDL_PushEvent(&event);
	  }
	}
	break;
      case SDL_QUIT:
	quit = 1;
	break;
 		  
      default:
	break;
      }
    }   

    int flag = 0;
    for(int i=0; i<4; i++){
      if(user_tetromino.tetromino.blocks[i].x == -50)
	{
	  flag = 1;
	}
    }

    for(int i=0; i<4; i++){
      if(user_tetromino.tetromino.blocks[i].x == 500)
	{
	  flag = 2;
	}
    }


    for(int i=0; i<4; i++){
      if(flag == 1){
	user_tetromino.tetromino.blocks[i].x = user_tetromino.tetromino.blocks[i].x + 50;
      }
      else if(flag == 2){
	user_tetromino.tetromino.blocks[i].x = user_tetromino.tetromino.blocks[i].x - 50;	
      }
      else{flag = 0;}
    }    
    
    /* Render structs.  */
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    if(user_tetromino.busy == 1){
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
      SDL_RenderFillRects(renderer, user_tetromino.tetromino.blocks, 4);
    }
    //Test garbage->cnt > 410
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
    
    for(int i=0; i<garbage->cnt; i++){
      SDL_RenderFillRects(renderer, garbage->tetromino[i].blocks, 4);
    }
               
    /* Render rectangles.  */
    SDL_RenderPresent(renderer);

  }
  
  SDL_Quit();
  
  return 0;  
}
