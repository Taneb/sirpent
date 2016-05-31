#ifndef WORLD_H
#define WORLD_H

#include "udp_list/list.h"
#include "vector.h"
#include "snake.h"

typedef struct world {
  int width, height;
  int * hexgrid;
  list(snake, snakes);
} world;

world * new_world(int width, int height);

void free_world(world * w);

int is_out_of_bounds(world * w, vector cell);

#endif
