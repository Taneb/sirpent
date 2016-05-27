#include <stdlib.h>
#define GRID_SIZE 300

struct snake {
  int snake_id;
  struct snake_segment * head;
  /* also put some network stuff here */
};

struct snake_segment {
  struct snake * snake_id;
  struct snake_segment * forward; // nullptr if head
  struct snake_segment * rearward; // nullptr if tip of tail
  int x_coord;
  int y_coord;
};

static struct snake_segment * grid0 [GRID_SIZE][GRID_SIZE];
static struct snake_segment * grid1 [GRID_SIZE][GRID_SIZE];
static struct snake_segment * grid2 [GRID_SIZE][GRID_SIZE];

struct linked_list {
  struct snake * value; /* not sure this is a good type to have for a value? */
  struct linked_list * next;
};

struct linked_list * prepend(struct snake * value, struct linked_list * tail) {
  struct linked_list * result = (struct linked_list *)malloc(sizeof(struct linked_list));
  /* hope to high hell this doesn't fail because I can't be bothered to check for that */
  
  result->value = value;
  result->next = tail;
  return result;
}

typedef enum {
  NORTH,
  NORTHEAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  NORTHWEST
} direction;

direction ask_direction(struct snake snake) {
  /* TODO actually ask */
  return SOUTH;
}

int is_out_of_bounds(int x_coord, int y_coord) {
  return x_coord < 0 || x_coord >= GRID_SIZE || y_coord < 0 || y_coord >= GRID_SIZE;
}

void update_world() {
  int x; int y;
  struct linked_list * snakes_to_remove = 0;
  for (x = 0; x < GRID_SIZE; x++) {
    for (y = 0; y < GRID_SIZE; y++) {
      if (grid0[x][y]) {
	if (grid0[x][y]->forward) {
	  // we are in the tail of a snake
	  struct snake_segment forward = *grid0[x][y]->forward;
	  grid1[forward.x_coord][forward.y_coord] = grid0[x][y];
	}
	else {
	  // we are in the head of a snake
	  direction which_way = ask_direction(*grid0[x][y]->snake_id);
	  int new_x = x, new_y = y;
	  switch (which_way) {
	  case NORTH:
	    new_y -= 1;
	    break;
	  case NORTHEAST:
	    new_x += 1;
	    new_y -= 1;
	    break;
	  case SOUTHEAST:
	    new_x += 1;
	    break;
	  case SOUTH:
	    new_y += 1;
	    break;
	  case SOUTHWEST:
	    new_x -= 1;
	    new_y += 1;
	    break;
	  case NORTHWEST:
	    new_x -= 1;
	    break;
	  }
	  
	  /* CHECK FOR COLLISIONS */
	  if (is_out_of_bounds(new_x, new_y)) {
	    snakes_to_remove = prepend(grid0[x][y]->snake_id, snakes_to_remove);
	    continue;
	  }
	  if (grid1[new_x][new_y]) {
	    /* collision */
	    snakes_to_remove = prepend(grid0[x][y]->snake_id, snakes_to_remove);
	    continue;
	  }
	  if (grid2[new_x][new_y]) {
	    /* head on collision */
	    snakes_to_remove = prepend(grid0[x][y]->snake_id, snakes_to_remove);
	    snakes_to_remove = prepend(grid2[new_x][new_y]->snake_id, snakes_to_remove);
	    continue;
	  }
	  
	  grid2[new_x][new_y] = grid0[x][y];
	}
      }
    }
  }
  for (x = 0; x < GRID_SIZE; x++) {
    for (y = 0; y < GRID_SIZE; y++) {
      if (grid1[x][y]) {
	struct linked_list * i = snakes_to_remove;
	int should_remove_segment = 0;
	while (i) {
	  if (grid1[x][y]->snake_id == i->value) {
	    should_remove_segment = 1;
	    break;
	  }
	  i = i->next;
	}
	if (should_remove_segment) {
	  grid0[x][y] = 0;
	  free(grid1[x][y]);
	}
	else {
	  grid0[x][y] = grid1[x][y];
	}
	grid1[x][y] = 0;
      }
      else if (grid2[x][y]) {
	struct linked_list * i = snakes_to_remove;
	int should_remove_segment = 0;
	while (i) {
	  if (grid2[x][y]->snake_id == i->value) {
	    should_remove_segment = 1;
	    break;
	  }
	  i = i->next;
	}
	if (should_remove_segment) {
	  grid0[x][y] = 0;
	  free(grid2[x][y]);
	}
	else {
	  grid0[x][y] = grid2[x][y];
	}
	grid2[x][y] = 0;
      }
      else {
	grid0[x][y] = grid1[x][y];
      }
      if (grid0[x][y]) {
	grid0[x][y]->x_coord = x;
	grid0[x][y]->y_coord = y;
      }
    }
  }
}

int main() {
  return 0;
}
