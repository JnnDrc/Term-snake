#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "input.h"
#include "game.h"


int main(void){
  // Initialization phase -----------------------
  srand(time(NULL));
  struct player_t player = {{{5,10}},1,0,'*'};
  struct berry_t berry = {4,17,'@'};
  enable_nbi();
  clear();
  // Game loop ----------------------------------
  for(;;){
    // Update phase -----------------------------
    if(player.segment_count == 10 * 20){
      move_cursor(1,1);
      clear();
      printf("You wind\n score: %d",player.segment_count);
      break;
    }
    if(check_collisions(&player)){
      move_cursor(1,1);
      clear();
      printf("You loose\n score: %d",player.segment_count);
      break;
    }
    switch(get_key()){
      case 'w':
          player.direction = 1;
        break;
      case 'a':
          player.direction = 2;
        break;
      case 's':
          player.direction = 4;
        break;
      case 'd':
          player.direction = 8;
        break;
      default:
        break;
    }
    update_player(&player,&berry);
    // Draw phase -------------------------------
    move_cursor(1,1);
    draw_arena(10,20);
    draw_berry(&berry);
    draw_player(&player);
    move_cursor(1,1);

    sleep(250);// sleep for smooth update
  } 
  
  disable_nbi();
  return 0;
}
