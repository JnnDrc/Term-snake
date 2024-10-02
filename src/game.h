#ifndef _GAME_H
#define _GAME_H
struct segment_t{
  int row;
  int column;
};
struct berry_t{
  int row;
  int column;
  char b_char;
};
struct player_t{
  struct segment_t segments[200];
  int segment_count,direction;
  char p_char;
};


void clear();
void move_cursor(int row,int column);

void update_player(struct player_t *player,struct berry_t *berry);
void draw_player(struct player_t *player);
void draw_berry(struct berry_t* berry);
void draw_arena(int height,int width);
int check_collisions(struct player_t *player);

#endif /* _GAME_H */
