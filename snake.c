#include "snake.h"

void update_snake(snake * s, direction snake_direction) {
  struct vector new_head_position = neighbour(list_elem_front(s->segments)->position, snake_direction);

  /* Move each segment forward by 1. */
  int flag = 1; /* we use this to skip the head */
  vector position;
  list_each_elem (s->segments, segment) {
    vector tmp = segment->position;
    if (flag) {
      flag = 0;
      position = tmp;
      continue;
    }
    segment->position = position;
    position = tmp;
  }

  /* Update the head segment position. */
  list_elem_front(s->segments)->position = new_head_position;
}

int are_snake_heads_colliding(snake * s1, snake * s2) {
  vector s1_position = list_elem_front(s1->segments)->position;
  vector s2_position = list_elem_front(s2->segments)->position;
  return (s1 != s2 && vectors_equal(s1_position, s2_position));
}

int does_snake_has_a_segment_at_position(snake * s, vector position) {
  list_each_elem (s->segments, segment) {
    if (vectors_equal(segment->position, position)) {
      return 1;
    }
  }
  return 0;
}

int does_snake_collide_with(snake * s1, snake * s2) {
  vector s1_head_position = list_elem_front(s1->segments)->position;
  return does_snake_has_a_segment_at_position(s2, s1_head_position);
}
