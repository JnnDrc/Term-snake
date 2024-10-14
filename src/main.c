#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "input.h"
#include "game.h"

#define HELP_TEXT "-----------Term-snake----------\n"\
                  "  The Snake game for terminal  \n"\
                  "-------------------------------\n"\
                  "How to play:                   \n"\
                  "\t Use WASD to move the snake  \n"\
                  "\t[default=*].                 \n"\
                  "\t Eat berrys[default=@] to    \n"\
                  "\tgrow and earn score.         \n"\
                  "\t Avoid walls[default=#] and  \n"\
                  "\tyourself[default*].          \n"\
                  "\t Fill the entirety of the    \n"\
                  "\tarena to win                 \n"\
                  "Custom arguments:              \n"\
                  "custom settings:               \n"\
                  "\t -s: change game speed       \n"\
                  "customization:                 \n"\
                  "\t -p: change player charecter \n"\
                  "\t -b: change berry character  \n"\
                  "\t -w: change walls character  \n"\
                  "debug:                         \n"\
                  "\t -d: play in debug mode      \n"\
                  "by-JnnDrc------------------v1.3\n"\

int main(int argc, char** argv){
  // Initialization phase -----------------------
  srand(time(NULL));
  char player_char = '*', berry_char = '@', wall_char = '#';
  int sleep_time = 200;
  int arena_height = 10, arena_width = arena_height * 2;
  int flags = 0;
    
  if(argc > 1){
    for(int i = 1; i < argc; i++){
      if(!strcmp(argv[i],"-h")){
        printf(HELP_TEXT);
        return 0;
      }
      if(!strcmp(argv[i],"-d")){
          flags |= DEBUG;
      }
      if (argc > 2){
        if(!strcmp(argv[i],"-p")){
          player_char = argv[++i][0];
        }
        if(!strcmp(argv[i],"-b")){
          berry_char = argv[++i][0];
        }
        if(!strcmp(argv[i],"-w")){
          wall_char = argv[++i][0];
        }
        if(!strcmp(argv[i],"-s")){
          sleep_time = atoi(argv[++i]);
        }
      }
    }
  } 
  struct player_t player = {{{arena_height/2,arena_width/2}},1,0,player_char};
  struct berry_t berry = {4,17,berry_char};
  clear();
  enable_nbi();
  // Game loop ----------------------------------
  for(;;){
    // Update phase -----------------------------
    if(player.segment_count == arena_height * arena_width){
      move_cursor(1,1);
      clear();
      printf("You win\n score: %d",player.segment_count - 1);
      goto exit;
    }
    if(check_collisions(&player,arena_height,arena_width)){
      move_cursor(1,1);
      clear();
      printf("You loose\n score: %d",player.segment_count - 1);
      goto exit;
    }
    switch(get_key()){
      case 'w':
          if (player.direction != 4 || player.segment_count == 1 ){
            player.direction = 1;
          }
        break;
      case 'a':
          if(player.direction != 8 || player.segment_count == 1){
            player.direction = 2;
          }
        break;
      case 's':
          if (player.direction != 1 || player.segment_count ==  1 ){
            player.direction = 4;
          }
        break;
      case 'd':
          if (player.direction != 2 || player.segment_count == 1 ){
            player.direction = 8;
          }
        break;
      case ' ':
        flags ^= PAUSED;
        break;
      case 'q':
        clear();
        goto exit;     
      default:
        break;
    }
    if (!FLAG(flags,PAUSED)){
        update_player(&player,&berry,arena_height,arena_width);
    }
    // Draw phase -------------------------------
    move_cursor(1,1);
    fflush(stdout);
    draw_arena(arena_height,arena_width,&player,&berry,wall_char,flags);
    fflush(stdout);
    draw_berry(&berry);
    fflush(stdout);
    draw_player(&player);
    fflush(stdout);
    move_cursor(1,1);
    fflush(stdout);

    sleep(sleep_time);// sleep for smooth update
  } 
exit:
  disable_nbi();
  return 0;
}
