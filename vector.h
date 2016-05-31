#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
  int x, y;
} vector;

typedef enum {
  NORTH,
  NORTHEAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  NORTHWEST
} direction;

int vectors_equal(vector a, vector b);

vector neighbour(vector cell, direction to_neighbour);

#endif
