#ifndef SNAKE_H
#define SNAKE_H

#include "udp_list/list.h"
#include "vector.h"

typedef struct snake snake;
typedef struct snake_segment snake_segment;

struct snake {
  /*struct player *player;*/
  int length, dead;
  list(snake_segment, segments);
};

struct snake_segment {
  snake * snake;
  vector position;
};

void update_snake(snake * s, direction snake_direction);

int are_snake_heads_colliding(snake * s1, snake * s2);

int does_snake_has_a_segment_at_position(snake * s, vector position);

int does_snake_collide_with(snake * s1, snake * s2);

#endif
