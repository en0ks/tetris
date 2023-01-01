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
};

struct Garbage{
  struct Tetromino tetromino[50];
  int cnt;
};

int check_garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void mov_r(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void mov_l(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void gravitate(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void spawn(struct User_Tetromino *user_tetromino, int type);
void hdrop(struct User_Tetromino *user_tetromino, struct Garbage *garbage);


void hdrop(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  for(int i=0; i<20; i++){
    for(int j=0; j<50; j++){

      if((user_tetromino->tetromino.blocks[0].y + 50*i) == garbage->tetromino->blocks[j].y){
	if(user_tetromino->tetromino.blocks[0].x == garbage->tetromino->blocks[j].x){
	  
	  user_tetromino->busy = 0;
	  garbage->tetromino->blocks[garbage->cnt].x = user_tetromino->tetromino.blocks[0].x;
	  garbage->tetromino->blocks[garbage->cnt].y = garbage->tetromino->blocks[j].y - 50;
	  garbage->cnt++;

	  return;
	}
      
      }

    }
    if(50*i == 950){
      user_tetromino->busy = 0;
      garbage->tetromino->blocks[garbage->cnt].x = user_tetromino->tetromino.blocks[0].x;
      garbage->tetromino->blocks[garbage->cnt].y = 950;
      garbage->cnt++;
    }
  }
  
  return;
}

int check_garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  if(user_tetromino->tetromino.blocks[0].y == 950){  
    return 1;
  }
  else {
    for(int i=0; i<50; i++){
      if(user_tetromino->tetromino.blocks[0].x == garbage->tetromino->blocks[i].x){
	if((user_tetromino->tetromino.blocks[0].y + 50) == garbage->tetromino->blocks[i].y){
	  return 1;
	}
      }
    }
  }

  return 0;
}

void mov_r(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  for(int i=0; i<50; i++){
    if((user_tetromino->tetromino.blocks[0].x + 50) == garbage->tetromino->blocks[i].x){
      if(user_tetromino->tetromino.blocks[0].y == garbage->tetromino->blocks[i].y){
	return;
      }      
    }    
  }

  if(user_tetromino->tetromino.blocks[0].x == 450){
    return;
  }
  
  int x0 = user_tetromino->tetromino.blocks[0].x;
  user_tetromino->tetromino.blocks[0].x = x0 + WIDTH/10;
  
  return;
}

void mov_l(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  for(int i=0; i<50; i++){
    if((user_tetromino->tetromino.blocks[0].x - 50) == garbage->tetromino->blocks[i].x){
      if(user_tetromino->tetromino.blocks[0].y == garbage->tetromino->blocks[i].y){
	return;
      }
    }    
  }

  if(user_tetromino->tetromino.blocks[0].x == 0){
    return;
  }
  
  int x0 = user_tetromino->tetromino.blocks[0].x;
  user_tetromino->tetromino.blocks[0].x = x0 - WIDTH/10;
  
  return;
}

void gravitate(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  int var = check_garbage(user_tetromino, garbage);

  if(var == 1){
    user_tetromino->busy = 0;
    garbage->tetromino->blocks[garbage->cnt].x = user_tetromino->tetromino.blocks[0].x;
    garbage->tetromino->blocks[garbage->cnt].y = user_tetromino->tetromino.blocks[0].y;
    garbage->cnt++;
  }
  else if(var == 0){
    int y0 = user_tetromino->tetromino.blocks[0].y;
    user_tetromino->tetromino.blocks[0].y = y0 + HEIGHT/20;     
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
