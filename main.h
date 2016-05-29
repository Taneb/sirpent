#include <stdlib.h>

#include "list.h"
#include "grid.h"

#define GRID_SIZE 300

typedef struct world world;
typedef struct snake snake;
typedef struct snake_segment snake_segment;

struct world {
  grid grid;
  linked_list * snakes_ll_head;
};

struct snake {
  /*struct player *player;*/
  linked_list * segments_ll_head, * segments_ll_tail;
  int length, dead;
};

struct snake_segment {
  snake * snake;
  vector position;
};

direction ask_direction(snake * snake);

void remove_snake(snake *snake);

void update_world(world * w);

int update_snake(world *w, snake *snake, direction snake_direction);

void collision_detection(world * w);
