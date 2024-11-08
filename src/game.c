#include "game.h"
#include <stdio.h>
#include <stdlib.h>


void move_cursor(int row,int column){
  printf("\033[%d;%dH",row,column);
}
void clear(){
  puts("\033[2J");
}

void update_player(struct player_t *player,struct berry_t *berry,int arena_height,int arena_width){
    if(player->segments[0].row == berry->row && player->segments[0].column == berry->column){
        player->segments[player->segment_count] = player->segments[0];
        player->segment_count++;
        int new_berry_row, new_berry_column;
        while(1){
            char overlap = 0;
            new_berry_row = (rand() % arena_height) + 2;//2 arena_height+1
            new_berry_column = (rand() % arena_width) + 2;//2 arena_width+1
        for(int i = 0; i < player->segment_count; i++){
            if(new_berry_row == player->segments[i].row && new_berry_column == player->segments[i].column){
                overlap = 1;
                break;
            }
        }
        if(!overlap){
            break;
        }
    }
    berry->row = new_berry_row;
    berry->column = new_berry_column;
  }


    for(int i = player->segment_count - 1; i > 0; i--){
        player->segments[i].column = player->segments[i - 1].column;
        player->segments[i].row = player->segments[i - 1].row;
  }

    switch(player->direction){
        case 1:
                player->segments[0].row--;
                break;
        case 2:
                player->segments[0].column--;
                break;
        case 4:
                player->segments[0].row++;
                break;
        case 8:
            player->segments[0].column++;
            break;
        default:
            break;
  }     
}
void draw_arena(int height,int width,struct player_t *player,struct berry_t *berry, char w_char,int flags){
  char blank_line[width+1];
  for(int i = 0; i < width; i++){
    blank_line[i] = ' ';
  }
  blank_line[width] = '\0';

  for(int i = 0; i < width+2; i++){
    putc(w_char,stdout);
  }
  putc('\n',stdout);

  for(int i = 0; i < height; i++){
    printf("%c%s%c\n",w_char,blank_line,w_char);
  }

  for(int i = 0; i < width+2; i++){
    putc(w_char,stdout);
  }
  printf("\nscore: %d",player->segment_count - 1);
  if(FLAG(flags, PAUSED)){
      printf("\tPAUSED");
  }else{
      printf("\t      ");
  }
  if(FLAG(flags, DEBUG)){
      printf("\nflags: %d direction: %d    ", flags,player->direction);
      printf("\nplayer: %d,%d berry: %d,%d   ",player->segments[0].row,player->segments[0].column,berry->row,berry->column);
      printf("\ncolision: %d",check_collisions(player,height,width));
  }

}


void draw_player(struct player_t *player){
  for(int i = 0; i < player->segment_count; i++){
      move_cursor(player->segments[i].row,player->segments[i].column);
    putc(player->p_char,stdout);
  }
}

void draw_berry(struct berry_t* berry){
  move_cursor(berry->row,berry->column);
  putc(berry->b_char,stdout);
}

int check_collisions(struct player_t *player,int arena_height,int arena_width){
  if(player->segments[0].row <= 1 || player->segments[0].row >=arena_height+2){
    return 1;
  }
  if(player->segments[0].column <= 1 || player->segments[0].column >= arena_width+2){
    return 2;
  }
  for (int i = 1; i < player->segment_count; i++) {
    if(player->segments[0].row ==  player->segments[i].row && player->segments[0].column == player->segments[i].column){
      return 3;
    }
  }
  return 0;
}
