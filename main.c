#include <stdlib.h>

#include "main.h"

direction ask_direction(snake *snake) {
  /* @TODO actually ask */
  return SOUTH;
}

void remove_snake(snake *snake) {
  /* @TODO */
}

void update_world(world *w) {
  list_each_elem (w->snakes, s) {
    direction d = ask_direction(s);
    if (update_snake(w, s, d) == 1) {
      // Snake died. But this is OK.
    }
  }

  collision_detection(w);

  list_each_elem (w->snakes, s) {
    if (s->dead) {
      list_elem_remove(s);
    }
  }
}

int update_snake(world *w, snake * s, direction snake_direction) {
  struct vector new_head_position = neighbour(list_elem_front(s->segments)->position, snake_direction);
  if (is_out_of_bounds(&w->grid, new_head_position)) {
    s->dead = 1;
    return 1;
  }

  /* Move each segment forward by 1. */
  list_each_elem (list_elem_next(s->segments), segment) {
    segment->position = list_elem_prev(segment)->position;
  }

  /* Update the head segment position. */
  list_elem_front(s->segments)->position = new_head_position;

  return 0;
}

int heads_collided(snake * s1, snake * s2) {
  vector s1_position = list_elem_front(s1->segments)->position;
  vector s2_position = list_elem_front(s2->segments)->position;
  return (s1 != s2 && vectors_equal(s1_position, s2_position));
}

int snake_has_a_segment_at_position(snake * s, vector position) {
  list_each_elem (s->segments, segment) {
    if (vectors_equal(segment->position, position)) {
      return 1;
    }
  }
  return 0;
}

void collision_detection(world *w) {
  // This can be optimised somewhat, to avoid duplicate checks and already-dead checks.
  // However care is needed to avoid allowing self-collision or unfair survival.
  list_each_elem (w->snakes, s1) {
    list_each_elem (w->snakes, s2) {
      if (heads_collided(s1, s2)) {
        s1->dead = s2->dead = 1;
        break;
      }

      vector s1_head_position = list_elem_front(s1->segments)->position;
      if (snake_has_a_segment_at_position(s2, s1_head_position)) {
        s1->dead = 1;
        break;
      }
    }
  }
}

int main() {
  return 0;
}
