#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "header.h"
#include "functions.c"

int main(int argc, char *argv[]){
			
  /* Create thread  */
	
  /* Create pointer to 2D array.  */
  int **board;

  /* Create a board. In this array of board the following values are defined
   * as follows: -1 (=EMPTY) is an empty block, 0 is a garbage block and lastly
   * 1 (=USER) is a block under user control. */
  /* Board is indexed as follows: 
   * (0,0) (0,1) (0,2) ... (0,9)
   * (1,0) 						 
   * (2,0)						
   * .						
   * .					
   * .				
   * (19,0)	*/
  board = create_board();
  /* Intgrate SDL.
   * Make user be able to input to play tetris. */

  printf("\n");

  /* SDL start  */

  SDL_Event event;
  int quit = 0;
   
  /*Initialize*/
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
		
    printf("Initialization failed");
		
    return 1;

  }
  
  /*Initialize window*/
  SDL_Window *window = NULL;
  /*Initialize renderer*/
  SDL_Renderer *renderer = NULL;

  window = SDL_CreateWindow("Quad", 0, 0, WIDTH, HEIGHT, 0);

  if(window == NULL){

    printf("Initializing window failed");

    return 1;
 		  
  }
  
  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  if(renderer == NULL){

    printf("Initializing renderer failed");

    return 1;
 		  
  }

  SDL_Point points[231] = {{-1, -1}};

  /*Set points on the board for coordinates sake*/
  int i = 0;
  for(int y = 0; y < 21; y++){
    for(int x = 0; x < 11; x++){

      points[i].x = x*WIDTH/10;
      points[i].y = y*HEIGHT/20;
      ++i;

    }

    if(i == 230){
      break;
    }
  }
  
  printf("index(points[i].x, points[i].y) =>\n");
  int cnt = 0;
  for(int i = 0; i < 231; ++i){
    printf("%d(%d, %d)\t",i , points[i].x, points[i].y);
    if(cnt >= 10){
      printf("\n");
      cnt = 0;
    }
    else{
      cnt++;
    }
  }

  /* Pointer to an array of size 2 with point A and point B of which
   * RenderDrawLines will draw the board lines. */
  SDL_Point points_line[2] = {0};
  
  /* Store in even indices the point A, and in its next place the respective
   * point B */
  int indices[42 + 22] = {-1};

  /* Calc the indices for the positions of the points A and B in the points[]
   * array for the horizontal lines */
  for(int i = 0; i < 42; ++i){
  
    indices[i] = (i/2)*11;
    ++i;
    indices[i] = indices[i-1] + 10;
   
  }
  /*Do the same for the vertical lines*/
  for(int i = 0; i < 22; ++i){

    indices[42+i] = i/2;
    ++i;
    indices[42+i] = indices[42+i - 1] + 220;

  }

  /*Initialize building rectangle for each tetriminoe block*/
  SDL_Rect block[200];

  /* Assign 200 blocks in total to the SDL grid of points of type Point. */

  cnt = 0;
  int row = 0;

  for(int i=0; i<200; i++){
    block[i].x = (WIDTH/10)*cnt;
    block[i].y = HEIGHT/20*row;
    cnt++;
    if(cnt == 10){
      cnt = 0;
      row++;
    }
    block[i].w = WIDTH/10;		
    block[i].h = HEIGHT/20;
  }

  printf("i, block[i].x, block[i].y");
  cnt = 0;
  for(int i = 0; i < 200; i++){
    printf("%d: %d %d || ",i , block[i].x, block[i].y);
    if(cnt >= 10){
      printf("\n");
      cnt = 0;
    }
    else{
      cnt++;
    }
  }

  /* Convert the 2 dimensional array board[][] to a 1 dimensional board[]
   * such that we can compare board[i] and block[i]. */
  int copy_board[200];
  cnt = 0;
  int flag_user_occupied = 1;

  time_t start_time;
  start_time = time(NULL);

  //TODO: when mv left, check garbage, if garbage block mv, else mv.
  //rotate_l and rotate_r.
  //harddrop and softdrop.
  
  while(!quit){

    if(time(NULL) - start_time > DELAY){
      
      start_time = time(NULL);

      if(flag_user_occupied == 1){
	fall_tetromino(board, &flag_user_occupied);
      }
      else if(flag_user_occupied == 0){
	spawn_tetromino(board, 0);//get_magic rng doesnt work yet, puts out garbage, do 0 instead.
	flag_user_occupied = 1;
      }

      
    }
    
    while(SDL_PollEvent(&event)){

      switch(event.type){
 		  
      case SDL_KEYDOWN:
	printf("[INPUT]:\t");
	if(event.key.keysym.sym==SDLK_c){
	  rotate_cw(board, &flag_user_occupied, 0);
	}
	if(event.key.keysym.sym==SDLK_UP){
	  printf("UP\n");
	}
	if(event.key.keysym.sym==SDLK_DOWN){
	  /*Slowdrop*/
	  printf("DOWN\n");
	}
	if(event.key.keysym.sym==SDLK_LEFT){
	  /*Move tet to left*/
	  move_tetromino_left(board, &flag_user_occupied);

	  printf("LEFT\n");
	} 
	if(event.key.keysym.sym==SDLK_RIGHT){
	  /*Move tet to right*/
	  move_tetromino_right(board, &flag_user_occupied);

	  printf("RIGHT\n");
	}
	if((SDL_GetModState() == KMOD_LCTRL) || 
	   SDL_GetModState() == KMOD_RCTRL){
	  printf("LCTRL");
	  if(event.key.keysym.sym==SDLK_F4){
	    printf("+F4\nExiting program\n");
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

    cnt = 0;
    for(int i=0; i<ROW; i++){
      for(int j=0; j<COL; j++){
	copy_board[cnt] = board[i][j];
	cnt++;

      }
    }


    for(int i=0; i<200; i++){

      /* If empty draw black  */
      /* How does the array board relate to block?  */

      if(copy_board[i] == EMPTY){
	/* Color: black */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &block[i]);
      }
      else if(copy_board[i] == USER){	
	/* Color: yellow */
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &block[i]);
      }
      else if(copy_board[i] == GARBAGE){
	/* Color: gray */
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &block[i]);
      }

    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int i = 0; i < 42 + 22; i++){
      points_line[0] = points[indices[i]]; 
      points_line[1] = points[indices[++i]];
      SDL_RenderDrawLines(renderer, points_line, 2);
    }

    SDL_RenderPresent(renderer);

  }

  /* SDL ended  */
  free(board);

  /*Exit SDL*/
  SDL_Quit();

  return 0;

}
