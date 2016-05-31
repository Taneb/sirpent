#include "vector.h"

int vectors_equal(vector a, vector b) {
  return (a.x == b.x && a.y == b.y);
};

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
