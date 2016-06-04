#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>

#include "udp_list/list.h"
#include "vector.h"
#include "world.h"
#include "snake.h"

#define GRID_SIZE 300

direction ask_direction(snake * snake);

void update_world(world * w);

void collision_detection(world * w);

#endif
