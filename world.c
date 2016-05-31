#include <stdlib.h>

#include "world.h"

world * new_world(int width, int height) {
  world * w = malloc(sizeof(world));
  w->width = width;
  w->height = height;
  w->hexgrid = malloc(sizeof(int) * width * height);
  w->snakes = NULL;
  return w;
}

void free_world(world * w) {
  free(w->hexgrid);
  w->hexgrid = NULL;
  list_clear(w->snakes);
  free(w);
}

int is_out_of_bounds(world * w, vector cell) {
  return cell.x < 0 || cell.x >= w->width || cell.y < 0 || cell.y >= w->height;
}
