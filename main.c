#include <stdlib.h>

#include "list.h"

#define GRID_SIZE 300

struct snake {
  int snake_id;
  struct snake_segment * head;
  /* also put some network stuff here */
};

struct snake_segment {
  struct snake * snake_id;
  struct snake_segment * forward; /* nullptr if head */
  struct snake_segment * rearward; /* nullptr if tip of tail */
  struct vector location;
};

static struct snake_segment * grid0 [GRID_SIZE][GRID_SIZE];
static struct snake_segment * grid1 [GRID_SIZE][GRID_SIZE];
static struct snake_segment * grid2 [GRID_SIZE][GRID_SIZE];

typedef enum {
  NORTH,
  NORTHEAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  NORTHWEST
} direction;

struct vector {
  int x, y;
};

direction ask_direction(struct snake snake) {
  /* TODO actually ask */
  return SOUTH;
}

int is_out_of_bounds(struct vector cell) {
  return cell.x < 0 || cell.x >= GRID_SIZE || cell.y < 0 || cell.y >= GRID_SIZE;
}

struct vector neighbour(struct vector cell, direction to_neighbour) {
  struct vector neighbour = cell;
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

void update_world() {
  int s;
  for (s = 0; s < snakes_len; s++) {
    struct snake *snake = snakes[s];

    direction snake_direction = ask_direction(snake);
    struct vector new_head_position = neighbour(snake->head.position, snake_direction);
    if (is_out_of_bounds(new_head_position)) {
      /* @TODO: REMOVE SNAKE */
      continue;
    }

    /* Move each segment forward by 1. */
    struct snake_segment *current_segment = snake->head;
    while (current_segment->next != NULL) {
      current_segment->next.position = current_segment->position;
      current_segment = current_segment->next;
    }
    /* Update the head segment position. */
    snake->head.position = new_head_position;
  }

  /* @TODO: Collision detection. What are the rules for collisions? */

  /*
  CHECK FOR COLLISIONS
  if (is_out_of_bounds(new_head_cell)) {
    snakes_to_remove = prepend(grid0[x][y]->snake_id, snakes_to_remove);
    continue;
  }
  if (grid1[new_head_cell.x][new_head_cell.y]) {
    collision
    snakes_to_remove = prepend(grid0[x][y]->snake_id, snakes_to_remove);
    continue;
  }
  if (grid2[new_head_cell.x][new_head_cell.y]) {
    head on collision
    snakes_to_remove = prepend(grid0[x][y]->snake_id, snakes_to_remove);
    snakes_to_remove = prepend(grid2[new_head_cell.x][new_head_cell.y]->snake_id, snakes_to_remove);
    continue;
  }
  destroy(snakes_to_remove);
  */
}

int main() {
  return 0;
}
