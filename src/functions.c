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
};

void garbage(struct User_Tetromino *user_tetromino);
void mov_r(struct User_Tetromino *user_tetromino);
void mov_l(struct User_Tetromino *user_tetromino);
void gravitate(struct User_Tetromino *user_tetromino);
void spawn(struct User_Tetromino *user_tetromino, int type);

void garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  int x0 = user_tetromino->tetromino.blocks[0].x;
  int y0 = user_tetromino->tetromino.blocks[0].y;

  for(int i=0; i<(WIDTH/10)(HEIGHT/20); i++){
    if(x0 == garbage->garbage_blocks[i].x && y0 == (garbage->garbage_blocks[i].y - HEIGHT/20)){
      
    }
    
  }
  return;
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

void gravitate(struct User_Tetromino *user_tetromino){

  int y0 = user_tetromino->tetromino.blocks[0].y;
  user_tetromino->tetromino.blocks[0].y = y0 + HEIGHT/20;

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
