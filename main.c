#include <stdlib.h>

#include "main.h"
#include "world.h"
#include "render.h"

direction ask_direction(snake * snake) {
  /* @TODO actually ask */
  return SOUTH;
}

void update_world(world * w) {
  list_each_elem (w->snakes, s) {
    direction d = ask_direction(s);
    update_snake(s, d);
    if (is_out_of_bounds(w, list_elem_front(s->segments)->position)) {
      s->dead = 1;
    }
  }

  collision_detection(w);

  list_each_elem (w->snakes, s) {
    if (s->dead) {
      list_elem_remove(s);
    }
  }
}

void collision_detection(world * w) {
  // This can be optimised lots, to avoid duplicate checks and already-dead checks.
  // However care is needed to avoid allowing self-collision or unfair survival.
  list_each_elem (w->snakes, s1) {
    list_each_elem (w->snakes, s2) {
      if (s1 == s2) {
        continue;
      }
      if (does_snake_collide_with(s1, s2)) {
        s1->dead = 1;
        break;
      }
    }
  }
}

world * initialize_world() {
  world * w = (world *)malloc(sizeof(world));
  w->width = 30;
  w->height = 30;
  w->snakes = 0;
  snake s = {3, 0, 0};
  list_push(w->snakes, s);
  for (int x = 4; x <= 6; x++) {
    snake_segment g = {list_elem_front(w->snakes), {x, 3}};
    list_push(list_elem_front(w->snakes)->segments, g);
  }
  return w;
}



int main() {
  world * world = initialize_world();
  init_display();
  while(list_length(world->snakes)) {
    draw_world(world);
    update_world(world);
    sleep(1);
  }
  return 0;
}
