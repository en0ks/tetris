#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "header.h"
#include "functions.c"

/* Create the struct User which holds information about the current falling
   block. This struct comprises another struct Tet. This struct Tet holds
   information about the all seven tetromino pieces. When doing operations
   on the User tetromino, we check the struct User, and procede according to
   this struct User and Tet. */
  
int main(int argc, char *argv[]){
		       	
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

  time_t start_time;
  start_time = time(NULL);

  struct User_Tetromino user_tetromino = {0};  
  struct Garbage garbage = {0};


  
  spawn(&user_tetromino, 4);

  //TODO: implement converting to garbage when block hits height 950.
 
  while(!quit){

    if(time(NULL) - start_time > DELAY){
      
      start_time = time(NULL);

      /* Fall code. */
      gravitate(&user_tetromino, &garbage);
      
      if(user_tetromino.busy == 1){
	//fall
      }
      else if(user_tetromino.busy == 0){
	//spawn
	//in f_spawn create 4 blocks and put them in user.
      }
      else{
	//error warning
      }
    }
    
    while(SDL_PollEvent(&event)){

      switch(event.type){
 		  
      case SDL_KEYDOWN:

	if(event.key.keysym.sym==SDLK_c){

	}
	if(event.key.keysym.sym==SDLK_UP){

	}
	if(event.key.keysym.sym==SDLK_DOWN){

	}
	if(event.key.keysym.sym==SDLK_LEFT){
	  mov_l(&user_tetromino);
	} 
	if(event.key.keysym.sym==SDLK_RIGHT){
	  mov_r(&user_tetromino);	  
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

    /* Render structs.  */
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRects(renderer, user_tetromino.tetromino.blocks, 4);
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, SDL_ALPHA_OPAQUE);        
    SDL_RenderFillRects(renderer, garbage.garbage_blocks, garbage.cnt_garbage);
    
    //printf("%d:%d:%d:%d \n", user_tetromino.tetromino.blocks[0].x, user_tetromino.tetromino.blocks[0].y, user_tetromino.tetromino.blocks[0].w, user_tetromino.tetromino.blocks[0].h);
      
      
    /* Render rectangles.  */
    SDL_RenderPresent(renderer);

  }
  
  SDL_Quit();
  return 0;  
}
