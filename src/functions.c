#include "header.h"

struct Tetromino{
  SDL_Rect blocks[4]; /*Blocks which makes a Tetromino*/
  int type; /*0 1 2 3 4 5 6 => I O Z S T L J*/
  int x, y; /*Coordinates of the central piece*/
  int orient; /*Orientation of type of tetromino*/    
};

struct User_Tetromino{
  struct Tetromino tetromino;
  int busy;
  int rot_l;
  int rot_r;
  int mov_l;
  int mov_r;
  int hdrop;
  int sdrop;
};

struct Garbage{
  SDL_Rect garbage_blocks[200];
  int cnt_garbage;
};

int check_garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void mov_r(struct User_Tetromino *user_tetromino);
void mov_l(struct User_Tetromino *user_tetromino);
void gravitate(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void spawn(struct User_Tetromino *user_tetromino, int type);


int check_garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  int x0 = user_tetromino->tetromino.blocks[0].x;
  int y0 = user_tetromino->tetromino.blocks[0].y;

  for(int i=0; i<200; i++){
    if(x0 == garbage->garbage_blocks[i].x && y0 == (garbage->garbage_blocks[i].y - 50)){
      if(garbage->cnt_garbage > 199){
	printf("WARNING: exceeding bounds in garbage for garbage_blocks.");
      }
      return 1;
    }
    else return 0;
    
  }
  return -1;
}

void mov_r(struct User_Tetromino *user_tetromino){

  int x0 = user_tetromino->tetromino.blocks[0].x;
  user_tetromino->tetromino.blocks[0].x = x0 + WIDTH/10;
  
  return;
}

void mov_l(struct User_Tetromino *user_tetromino){

  int x0 = user_tetromino->tetromino.blocks[0].x;
  user_tetromino->tetromino.blocks[0].x = x0 - WIDTH/10;
  
  return;
}

void gravitate(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  int var = check_garbage(user_tetromino, garbage);

  if(var  == -1){
    printf("WARNING: in check_garbage no definite result.");
      }
  else if(var == 0){
    int y0 = user_tetromino->tetromino.blocks[0].y;
    user_tetromino->tetromino.blocks[0].y = y0 + HEIGHT/20;  
  }
  else if(var == 1){
    garbage->garbage_blocks[garbage->cnt_garbage++] = user_tetromino->tetromino.blocks[0];
    user_tetromino->busy = 0;
    spawn(user_tetromino, 4);
  }
  
  return;
}

void spawn(struct User_Tetromino *user_tetromino, int type){

  //For now spawn T which has type = 4.
  if(user_tetromino->busy == 0){
    switch(type){
    case 4:
      
      user_tetromino->tetromino.blocks[0].x = (WIDTH/10)*5;
      user_tetromino->tetromino.blocks[0].y = 0;
      user_tetromino->tetromino.blocks[0].w = WIDTH/10;      
      user_tetromino->tetromino.blocks[0].h = HEIGHT/20;

      user_tetromino->tetromino.type = 4;

      user_tetromino->tetromino.x = (WIDTH/10)*5;
      user_tetromino->tetromino.y = 0;

      user_tetromino->tetromino.orient = 0;

      user_tetromino->busy = 1;
      
    }
  }
  return;
}
