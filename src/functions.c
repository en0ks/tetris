#include "header.h"

struct Tetromino{
  SDL_Rect blocks[4]; /*Blocks which makes a Tetromino*/
  int type; /*0 1 2 3 4 5 6 => Ix Ox Z S Tx L J */
  int orient; /*Orientation of type of tetromino*/
};

struct User_Tetromino{
  struct Tetromino tetromino;
  int busy;
};

//TODO: figure out how to clean garbage.cnt and recycle old.

struct Garbage{
  int cnt;
  struct Tetromino tetromino[];  
};

void rotate(struct User_Tetromino *user_tetromino, struct Garbage *garbage, int direction, int type);
int check_garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void mov(struct User_Tetromino *user_tetromino, struct Garbage *garbage, int direction);
void gravitate(struct User_Tetromino *user_tetromino, struct Garbage *garbage);
void spawn(struct User_Tetromino *user_tetromino, int type);
void sdrop(int *delay);
void clear_line(struct Garbage *garbage);

void clear_line(struct Garbage *garbage){

  int board[10][20] = {0};
  
  for(int i=0; i<garbage->cnt; i++){
    for(int j=0; j<4; j++){
      int index_x = (garbage->tetromino[i].blocks[j].x)/50;
      int index_y = (garbage->tetromino[i].blocks[j].y)/50;
      if(index_x >= 0 && index_x <= 450 && index_y >= 0 && index_y <= 950){
	board[index_x][index_y] = 1;
      }      
    }
  }

  int cnt, y_to_clear = 0;
  for(int j=0; j<20; j++){
    cnt = 0;
    for(int i=0; i<10; i++){
      if(board[i][j] == 1){
	cnt++;
      }
      if(cnt == 10){	
	y_to_clear = 50*j;
	break;
      }
    }
    if(cnt == 10){
      break;
    }
  }

  cnt = 0;
  for(int i=0; i<garbage->cnt; i++){
    for(int j=0; j<4; j++){
      if(garbage->tetromino[i].blocks[j].y <= y_to_clear){
	cnt++;	
      }
    }
  }

  int bound = cnt;
  cnt = 0;

  //Give cleared line a magic number.
  for(int i=0; i<garbage->cnt; i++){
    for(int j=0; j<4; j++){
      if(garbage->tetromino[i].blocks[j].y == y_to_clear){
	garbage->tetromino[i].blocks[j].y = -61;
	garbage->tetromino[i].blocks[j].x = -61;       
      }
    }
  }
  
  for(int i=0; i<garbage->cnt; i++){
    for(int j=0; j<4; j++){
      if(garbage->tetromino[i].blocks[j].y <= y_to_clear){
	if(cnt < bound)
	  garbage->tetromino[i].blocks[j].y = garbage->tetromino[i].blocks[j].y + 50;
	cnt++;
      }
      else{
	cnt = 0;
      }
    }
  }
  
  return;
}

void sdrop(int *delay){

  *delay = INT_MIN;

  return;
}

void rotate(struct User_Tetromino *user_tetromino, struct Garbage *garbage, int direction, int type){

  int x0 = user_tetromino->tetromino.blocks[0].x;
  int x1 = user_tetromino->tetromino.blocks[1].x;
  int x2 = user_tetromino->tetromino.blocks[2].x;
  int x3 = user_tetromino->tetromino.blocks[3].x;

  int y0 = user_tetromino->tetromino.blocks[0].y;
  int y1 = user_tetromino->tetromino.blocks[1].y;
  int y2 = user_tetromino->tetromino.blocks[2].y;
  int y3 = user_tetromino->tetromino.blocks[3].y;

  int sign = 1;
  int orient = user_tetromino->tetromino.orient;

  if(direction == 1){
    sign = -1;
    if(orient == 0){user_tetromino->tetromino.orient = 3;}
    if(orient == 1){user_tetromino->tetromino.orient = 0;}
    if(orient == 2){user_tetromino->tetromino.orient = 1;}
    if(orient == 3){user_tetromino->tetromino.orient = 2;}
  }
  if(direction == 0){
    if(orient == 0){user_tetromino->tetromino.orient = 1;}
    if(orient == 1){user_tetromino->tetromino.orient = 2;}
    if(orient == 2){user_tetromino->tetromino.orient = 3;}
    if(orient == 3){user_tetromino->tetromino.orient = 0;}
  }

  switch(type){
  case 0:

    if (orient == 0) {
      if (direction == 0) {
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x1;
	  user_tetromino->tetromino.blocks[i].y = y1 + 100 - 50*i;
	}
      }
      else{
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x2;
	  user_tetromino->tetromino.blocks[i].y = y1 + 100 - 50*i;	  
	}
      }
    }

    if (orient == 1) {
      if (direction == 0) {
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x1 + 100 - 50*i;
	  user_tetromino->tetromino.blocks[i].y = y1;
	}
      }
      else{
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x2 - 50 + 50*i;
	  user_tetromino->tetromino.blocks[i].y = y2;
	}
      }
    }

    if (orient == 2) {
      if (direction == 0) {
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x1;
	  user_tetromino->tetromino.blocks[i].y = y1 - 100 + 50*i;
	}
      }
      else{
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x2;
	  user_tetromino->tetromino.blocks[i].y = y2 + 100 - 50*i;	  
	}
      }
    }

    if (orient == 3) {
      if (direction == 0) {
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x1 - 100 + 50*i;
	  user_tetromino->tetromino.blocks[i].y = y1;
	}
      }
      else{
	for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = x1 + 50 - 50*i;
	  user_tetromino->tetromino.blocks[i].y = y1;
	}
      }
    }
    break;
  case 1:
    break;
  case 4:
      if(orient == 0){
	user_tetromino->tetromino.blocks[0].x = x0 + 50;
	user_tetromino->tetromino.blocks[2].x = x2 - 50;
	user_tetromino->tetromino.blocks[3].x = x3 - 50*sign;

	user_tetromino->tetromino.blocks[0].y = y0 + 50*sign;
	user_tetromino->tetromino.blocks[2].y = y2 - 50*sign;
	user_tetromino->tetromino.blocks[3].y = y3 + 50;
      }
      else if(orient == 1){
	user_tetromino->tetromino.blocks[0].x = x0 + 50*sign;
	user_tetromino->tetromino.blocks[2].x = x2 - 50*sign;
	user_tetromino->tetromino.blocks[3].x = x3 + 50;

	user_tetromino->tetromino.blocks[0].y = y0 - 50;
	user_tetromino->tetromino.blocks[2].y = y2 + 50;
	user_tetromino->tetromino.blocks[3].y = y3 + 50*sign;
      }
      else if(orient == 2){

	user_tetromino->tetromino.blocks[0].x = x0 - 50;
	user_tetromino->tetromino.blocks[2].x = x2 + 50;
	user_tetromino->tetromino.blocks[3].x = x3 + 50*sign;

	user_tetromino->tetromino.blocks[0].y = y0 - 50*sign;
	user_tetromino->tetromino.blocks[2].y = y2 + 50*sign;
	user_tetromino->tetromino.blocks[3].y = y3 - 50;
      }
      else if(orient == 3){
	user_tetromino->tetromino.blocks[0].x = x0 - 50*sign;
	user_tetromino->tetromino.blocks[2].x = x2 + 50*sign;
	user_tetromino->tetromino.blocks[3].x = x3 - 50;

	user_tetromino->tetromino.blocks[0].y = y0 + 50;
	user_tetromino->tetromino.blocks[2].y = y2 - 50;
	user_tetromino->tetromino.blocks[3].y = y3 - 50*sign;
      }
      break;
  case 5:

    if(orient == 0){
      if(direction == 0){
	
      }
      else{
	
      }
    }
    else if(orient == 1){
      
    }
    else if (orient == 2){
      
    }
    else if (orient == 3){
      
    }
    
    break;
  }
  return;
}

int check_garbage(struct User_Tetromino *user_tetromino, struct Garbage *garbage){

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      if(user_tetromino->tetromino.blocks[j].y == 950){
	return 1;
      }
    }
  }

  /*Redo at some point in time*/
  for(int i=0; i<garbage->cnt; i++){
    for(int j=0; j<4; j++){
      for(int k=0; k<4; k++){
	if(garbage->tetromino[i].blocks[j].y -
	   user_tetromino->tetromino.blocks[k].y == 50){
	  if(garbage->tetromino[i].blocks[j].x ==
	     user_tetromino->tetromino.blocks[k].x){
	    return 1;
	  }
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
      for(int k=0; k<4; k++){
	if(user_tetromino->tetromino.blocks[k].x - 50 + offset == garbage->tetromino[i].blocks[j].x){
	  if(user_tetromino->tetromino.blocks[k].y  == garbage->tetromino[i].blocks[j].y){
	    return;
	  }
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
      garbage->tetromino[garbage->cnt].blocks[i] = user_tetromino->tetromino.blocks[i];
    }

    garbage->cnt = garbage->cnt + 1;
    
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

  if(user_tetromino->busy == 0){
    switch(type){
    case 0:
      for(int i=0; i<4; i++){
	  user_tetromino->tetromino.blocks[i].x = (WIDTH/10)*5 - 100 + 50*i;
	  user_tetromino->tetromino.blocks[i].y = -50;
	  user_tetromino->tetromino.blocks[i].w = WIDTH/10;
	  user_tetromino->tetromino.blocks[i].h = HEIGHT/20;
      }
      user_tetromino->tetromino.type = 0;

      user_tetromino->tetromino.orient = 0;

      user_tetromino->busy = 1;

      break;
    case 1:
      for(int i=0; i<2; i++){
	  user_tetromino->tetromino.blocks[i].x = (WIDTH/10)*5 - 50 + 50*i;
	  user_tetromino->tetromino.blocks[i].y = -50;
	  user_tetromino->tetromino.blocks[i].w = WIDTH/10;
	  user_tetromino->tetromino.blocks[i].h = HEIGHT/20;
      }
      for(int i=0; i<2; i++){
	  user_tetromino->tetromino.blocks[i + 2].x = (WIDTH/10)*5 - 50 + 50*i;
	  user_tetromino->tetromino.blocks[i + 2].y = 0;
	  user_tetromino->tetromino.blocks[i + 2].w = WIDTH/10;
	  user_tetromino->tetromino.blocks[i + 2].h = HEIGHT/20;
      }
      user_tetromino->tetromino.type = 1;

      user_tetromino->tetromino.orient = 0;

      user_tetromino->busy = 1;

      break;
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

      user_tetromino->tetromino.orient = 0;

      user_tetromino->busy = 1;
      break;
    case 5:
      for(int i=0; i<3; i++){
	user_tetromino->tetromino.blocks[i].x = (WIDTH/10)*5 - 50 + 50*i;
	user_tetromino->tetromino.blocks[i].y = 0;
	user_tetromino->tetromino.blocks[i].w = WIDTH/10;
	user_tetromino->tetromino.blocks[i].h = HEIGHT/20;
      }
      
      user_tetromino->tetromino.blocks[3].x = (WIDTH/10)*5 + 50;
      user_tetromino->tetromino.blocks[3].y = -50;                       
      user_tetromino->tetromino.blocks[3].w = WIDTH/10;                
      user_tetromino->tetromino.blocks[3].h = HEIGHT/20;

      user_tetromino->tetromino.type = 5;

      user_tetromino->tetromino.orient = 0;

      user_tetromino->busy = 1;      
    }
  }
  return;
}
