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
void mov(struct User_Tetromino *user_tetromino, struct Garbage *garbage, int direction);
void gravitate(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void spawn(struct User_Tetromino *user_tetromino, int type);
void sdrop(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void signal_handler(int signum, int *flag);

void signal_handler(int signum, int *flag){
  *flag = 1;
}

int check_garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  for(int i=0; i<4; i++){    
    if(user_tetromino->tetromino.blocks[i].y == 950){  
      return 1;
    }     
  }
  
  for(int i=0; i<garbage->cnt; i++){
    for(int j=0; j<4; j++){
      if(garbage->tetromino->blocks[i].y - user_tetromino->tetromino.blocks[j].y == 50){
	if(garbage->tetromino->blocks[i].x == user_tetromino->tetromino.blocks[j].x){
	  return 1;
	}
    }
    } 
  }
  
  
  return 0;
}

void mov(struct User_Tetromino *user_tetromino, struct Garbage *garbage, int direction){

  int offset = 0;
  if(direction == 1){
    offset = 100;
  }
  
  for(int i=0; i<garbage->cnt; i++){
    for(int j=0; j<4; j++){
      if((user_tetromino->tetromino.blocks[j].x - 50 + offset) == garbage->tetromino->blocks[i].x){
	if(user_tetromino->tetromino.blocks[j].y == garbage->tetromino->blocks[i].y){
	  return;
	}      
      }
    }   
  }

  for(int i=0; i<4; i++){
    if(user_tetromino->tetromino.blocks[i].x == 450 && direction == 1){
      return;
    }
    if(user_tetromino->tetromino.blocks[i].x == 0 && direction == 0){
      return;
    }
  }
  
  int x0 = user_tetromino->tetromino.blocks[0].x;
  int x1 = user_tetromino->tetromino.blocks[1].x;
  int x2 = user_tetromino->tetromino.blocks[2].x;
  int x3 = user_tetromino->tetromino.blocks[3].x;
  
  user_tetromino->tetromino.blocks[0].x = x0 - 50 + offset;
  user_tetromino->tetromino.blocks[1].x = x1 - 50 + offset;
  user_tetromino->tetromino.blocks[2].x = x2 - 50 + offset;
  user_tetromino->tetromino.blocks[3].x = x3 - 50 + offset; 
  
  return;
}

void gravitate(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  int var = check_garbage(user_tetromino, garbage);

  if(var == 1){
    user_tetromino->busy = 0;

    for(int i=0; i<4; i++){
      garbage->tetromino->blocks[garbage->cnt].x = user_tetromino->tetromino.blocks[i].x;
      garbage->tetromino->blocks[garbage->cnt].y = user_tetromino->tetromino.blocks[i].y;
      garbage->cnt++;
    }
      
  }

  else if(var == 0){
    
    int y0 = user_tetromino->tetromino.blocks[0].y;
    int y1 = user_tetromino->tetromino.blocks[1].y;
    int y2 = user_tetromino->tetromino.blocks[2].y;
    int y3 = user_tetromino->tetromino.blocks[3].y;
    
    user_tetromino->tetromino.blocks[0].y = y0 + HEIGHT/20;
    user_tetromino->tetromino.blocks[1].y = y1 + HEIGHT/20;
    user_tetromino->tetromino.blocks[2].y = y2 + HEIGHT/20;
    user_tetromino->tetromino.blocks[3].y = y3 + HEIGHT/20;
    
  }
  
  return;
}

void spawn(struct User_Tetromino *user_tetromino, int type){

  //For now spawn T which has type = 4.
  if(user_tetromino->busy == 0){
    switch(type){
    case 4:

      for(int i=0; i<3; i++){
	user_tetromino->tetromino.blocks[i].x = (WIDTH/10)*5 - 50 + 50*i;
	user_tetromino->tetromino.blocks[i].y = 0;
	user_tetromino->tetromino.blocks[i].w = WIDTH/10;      
	user_tetromino->tetromino.blocks[i].h = HEIGHT/20;
      }

      user_tetromino->tetromino.blocks[3].x = (WIDTH/10)*5;
      user_tetromino->tetromino.blocks[3].y = -50;
      user_tetromino->tetromino.blocks[3].w = WIDTH/10;      
      user_tetromino->tetromino.blocks[3].h = HEIGHT/20;      
    
      user_tetromino->tetromino.type = 4;

      user_tetromino->tetromino.x = (WIDTH/10)*5;
      user_tetromino->tetromino.y = 0;

      user_tetromino->tetromino.orient = 0;

      user_tetromino->busy = 1;
      
    }
  }
  return;
}
