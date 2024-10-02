#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "input.h"
#include "game.h"


int main(int argc, char** argv){
  // Initialization phase -----------------------
  srand(time(NULL));
  char player_char = '*', berry_char = '@', wall_char = '#';
  if(argc > 2){
    for(int i = 1; i < argc; i++){
      if(!strcmp(argv[i],"-p")){
        player_char = argv[++i][0];
      }
      if(!strcmp(argv[i],"-b")){
        berry_char = argv[++i][0];
      }
      if(!strcmp(argv[i],"-w")){
        wall_char = argv[++i][0];
      }
    }
  } 
  struct player_t player = {{{5,10}},1,0,player_char};
  struct berry_t berry = {4,17,berry_char};
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
    draw_arena(10,20,wall_char);
    draw_berry(&berry);
    draw_player(&player);
    move_cursor(1,1);

    sleep(250);// sleep for smooth update
  } 
  
  disable_nbi();
  return 0;
}
