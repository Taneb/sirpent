#include <stdlib.h>

#include "grid.h"

grid * new_grid(int width, int height) {
  grid * g = malloc(sizeof(grid));
  g->width = width;
  g->height = height;
  g->current = malloc(sizeof(int) * width * height);
  g->next = malloc(sizeof(int) * width * height);
  return g;
}

void free_grid(grid *g) {
  free(g->current);
  free(g->next);
  free(g);
}

int vectors_equal(vector a, vector b) {
  return (a.x == b.x && a.y == b.y);
};

int is_out_of_bounds(grid *g, vector cell) {
  return cell.x < 0 || cell.x >= g->width || cell.y < 0 || cell.y >= g->height;
}

vector neighbour(vector cell, direction to_neighbour) {
  vector neighbour = cell;
  switch (to_neighbour) {
  case NORTH:
    neighbour.y--;
    break;
  case NORTHEAST:
    neighbour.x++;
    neighbour.y--;
    break;
  case SOUTHEAST:
    neighbour.x++;
    break;
  case SOUTH:
    neighbour.y++;
    break;
  case SOUTHWEST:
    neighbour.x--;
    neighbour.y++;
    break;
  case NORTHWEST:
    neighbour.x--;
    break;
  }
  return neighbour;
}
