#ifndef _GAME_H
#define _GAME_H

#define FLAG(flags,FLAG) (flags & FLAG)
enum flags_n{DEBUG = 1, PAUSED = 2};

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

void update_player(struct player_t *player,struct berry_t *berry,int arena_height,int arena_width);
int check_collisions(struct player_t *player,int arena_height,int arena_width);

void draw_arena(int height,int width,struct player_t *player,struct berry_t *berry,char w_char,int flags);
void draw_player(struct player_t *player);
void draw_berry(struct berry_t* berry);

#endif /* _GAME_H */
