#include <stdlib.h>

#include "udp_list/list.h"
#include "grid.h"

#define GRID_SIZE 300

typedef struct world world;
typedef struct snake snake;
typedef struct snake_segment snake_segment;

struct world {
  grid grid;
  list(snake, snakes);
};

struct snake {
  /*struct player *player;*/
  int length, dead;
  list(snake_segment, segments);
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
