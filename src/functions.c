#include "header.h"

int ** create_board();
void spawn_tetromino(int **board, int magic);
void fall_tetromino(int **board, int *flag_user_occupied);
int ** get_user_indices(int **board); 
void convert_to_garbage(int **board, int **indices);
void print_board(int **board);
void move_tetromino_left(int **board, int *flag_user_occupied);
void move_tetromino_right(int **board, int *flag_user_occupied);
int get_magic();                      
void toggle_flag_user_occupied(int *flag, int on);
void rotate_cw(int **board, int *flag_user_occupied, int *magic);

/* Magic number table: 
 * 	0: I, 1: O, 2: L, 3:J, 4:T, 5:S, 6:Z*/
void rotate_cw(int **board, int *flag_user_occupied){

  if(*flag_user_occupied == 1){

    switch(magic){
    case 0:

      
      
    }
    
  }
  else return;

}

int ** create_board(){
	
  int **row = calloc(ROW, sizeof(int *));

  if(!row){

    perror("calloc");

    exit(1);

  }

  for (int i=0; i<ROW; i++){
		
    /* Calloc returns a pointer to the allocated memory.
     * Thus for every row store a pointer in the heap of row 
     * to the first index of the allocated memory of COL
     * blocks. Each block has a size of int. */

    row[i] = calloc(COL, sizeof(int));


  }
	
  if(!*row){

    perror("calloc");

    exit(1);

  }

  for (int i=0; i<ROW; i++){

    for (int j=0; j<COL; j++){

      row[i][j] = EMPTY;		

    }		

  }

  return row;

}

/* Dependend the magic number spawn a tetrimino under user 
 * influence in the board pointed to by board.  */
/* Magic number table: 
 * 	0: I, 1: O, 2: L, 3:J, 4:T, 5:S, 6:Z*/
void spawn_tetromino(int **board, int magic){

  switch(magic){
		
  case 0:	
			
    /* If all blocks are EMPTY (= -1)  spawn the I tetromino. 4 empty blocks always
     * have a value of -1. Therefore if they are not all empty, they do
     * not add up to 4*EMPTY. */
    if((board[0][3] + board[0][4] + board[0][5] + board[0][6]) == 4*EMPTY){
				
      for(int i=3; i<7; i++){

	board[0][i] = USER;

      }
      break;
    }
    else{

      /* Exit for now. Later implement "You died" screen  */

      return;

    }
		
  case 1:
				
    if((board[1][4] + board[0][4] + board[0][5] + board[1][5]) == 4*EMPTY){
				
      for(int i=4; i<6; i++){
	for(int j=0; j<2; j++){
	  board[j][i] = USER;
	}
      }
      break;
    }
    else{
      return;
    }

  case 2:
			
    if((board[1][3] + board[1][4] + board[1][5] + board[0][5]) == 4*EMPTY){
				
      for(int i=3; i<6; i++){
	board[1][i] = USER;

      }
      board[0][5] = USER;

      break;
    }
    else{
      return;
    }
  case 3:

    if((board[1][3] + board[1][4] + board[1][5] + board[0][3]) == 4*EMPTY){
				
      for(int i=3; i<6; i++){
	board[1][i] = USER;

      }
      board[0][3] = USER;

      break;
    }
    else{
      return;
    }
  case 4:
			
    if((board[1][3] + board[1][4] + board[1][5] + board[0][4]) == 4*EMPTY){
				
      for(int i=3; i<6; i++){
	board[1][i] = USER;

      }
      board[0][4] = USER;

      break;
    }
    else{
      return;
    }
  case 5:

    if((board[1][3] + board[1][4] + board[0][5] + board[0][4]) == 4*EMPTY){
				
      for(int i=3; i<5; i++){
	board[1][i] = USER;
      }

      for(int i=4; i<6; i++){
	board[0][i] = USER;
      }
      break;
    }
    else{
      return;
    }
  case 6:

    if((board[0][3] + board[1][4] + board[1][5] + board[0][4]) == 4*EMPTY){
				
      for(int i=4; i<6; i++){
	board[1][i] = USER;
      }

      for(int i=3; i<5; i++){
	board[0][i] = USER;
      }
      break;
    }
    else{
      return;
    }

  }
		
			

}

/* Get indices of all blocks currently under user influence.  */
int ** get_user_indices(int **board){
	
  int flag_user_block = 0;

  int **indices = malloc(4*sizeof(int *));

  for(int i=0; i<4; i++){
		
    indices[i] = malloc(2*sizeof(int));

  }


  int row_index = 0;

  for(int i=0; i<ROW; i++){

    for(int j=0; j<COL; j++){	

      if(board[i][j] == USER){
				
	flag_user_block = 1;

	indices[row_index][0] = i;
	indices[row_index][1] = j;
	row_index++;

      }

    }

  }
	
  /* If no block under user influence return NULL pointer  */
  if(!flag_user_block){

    for(int i=0; i<4; i++){

      indices[i][0] = -1;
      indices[i][1] = -1;
			
    }

  }

  return indices;

}


void fall_tetromino(int **board, int *flag_user_occupied){

  if(!board){
    printf("Warning: in fall_tetromino(int **board, int *flag_user_occupied): int **board is empty.");
  }	

  /* user_indices = 
   * row 0 = (col 0 = i,col 1 = j)
   * row 1 = ...
   * row 2 = ...
   * row 3 = ... , where board[i][j] = 1*/

  int **user_indices = get_user_indices(board);
	
  if(!user_indices){

    printf("Warning: in fall_tetromino(int **board, int *flag_user_occupied): int **user_indices is empty.");

  }

  /* Check if the next block under each USER block is EMPTY, else after delay 
   * convert USER block to GARBAGE block.  */
	
  /* Check availability else GARBAGE.  */

  /* Check whether user block even exists. If it does not the pointer is NULL.
   * -1 is an impossible index, so it is a type of flag for no user. This flag
   *  is always in user_indices. */

  int flag_not_empty = 0;

  for(int i=0; i<4; i++){

    if(user_indices[i][0] < 19){
		
      if(board[user_indices[i][0]+1][user_indices[i][1]] == 0){
	flag_not_empty = 1;
      }
    }
    else{
      if(user_indices[i][0] == 19){
	flag_not_empty = 1;
      }
    }
  }

  if(flag_not_empty){

    convert_to_garbage(board, user_indices);
    toggle_flag_user_occupied(flag_user_occupied, 0);

  }

  /* If empty, proceed to fall one time.  */
  if(!flag_not_empty){

    for(int i=0; i<4; i++){

      board[user_indices[i][0]][user_indices[i][1]] = -1;

    }

    for(int i=0; i<4; i++){

      board[user_indices[i][0]+1][user_indices[i][1]] = 1;

    }

  }

  free(user_indices);

}

void convert_to_garbage(int **board, int **indices){

  if(!board){

    printf("Warning: in convert_to_garbage(int **board, int **indices): int **board is empty.");

  }	

  if(!indices){

    printf("Warning: in convert_to_garbage(int **board, int **indices): int **indices is empty.");

  }

  if(indices[0][0] != -1){

    for(int i=0; i<4; i++){
			
      board[indices[i][0]][indices[i][1]] = 0;

    }
  }
  else{

    return;

  }
}

void print_board(int **board){

  for(int i=0; i<20; i++){
		
    SDL_Delay(DELAY);

    //fall_tetromino(board);

    /* Print board for visual aided information.  */
    int cnt = 0;
    printf("[INFO]:\n");
    for(int i=0; i<ROW; i++){
      for(int j=0; j<COL;j++){
	if(board[i][j] != EMPTY){	
	  printf("|  \033[33m%d\033[0m |", board[i][j]);
	}
	else{
	  printf("| %d |", board[i][j]);
	}
	cnt++;
	if(cnt == 10){
	  printf("\n");
	  cnt = 0;
	}
      }
    }
  }	


}
void move_tetromino_left(int **board, int *flag_user_occupied){

  if(*flag_user_occupied == 0){
    return;
  }

  int **user_indices = get_user_indices(board);

  /* Check whether block is movable to left or blocked by wall.  */
  for(int i=0; i<4; i++){
		
    if(user_indices[i][1] == 0){
      return;
    }		
  }
  /* If no corner move to left.  */

  for(int i=0; i<4; i++){
    board[user_indices[i][0]][user_indices[i][1]] = -1;
  }
  for(int i=0; i<4; i++){
    board[user_indices[i][0]][user_indices[i][1] - 1] = 1;
  }

}

void move_tetromino_right(int **board, int *flag_user_occupied){
	
  if(*flag_user_occupied == 0){
    return;
  }

  int **user_indices = get_user_indices(board);

  /* Check whether block is movable to right or blocked by wall.  */
  for(int i=0; i<4; i++){
		
    if(user_indices[i][1] == 9){
      return;
    }		
  }
  /* If no corner move to right.  */

  for(int i=0; i<4; i++){
    board[user_indices[i][0]][user_indices[i][1]] = -1;
  }
  for(int i=0; i<4; i++){
    board[user_indices[i][0]][user_indices[i][1] + 1] = 1;
  }

}
int get_magic(){
	
  srand(time(NULL));

  return (rand() % 6);

}

void toggle_flag_user_occupied(int *flag, int on){

  if(on == 1){
    *flag = 1;
  }
  if(on == 0){
    *flag = 0;
  }

}
