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
  linked_list * snakes_ll_node = w->snakes_ll_head;
  while (snakes_ll_node != NULL) {
    struct snake *snake = snakes_ll_node->value;
    direction snake_direction = ask_direction(snake);
    if (update_snake(w, snake, snake_direction) == 1) {
      // Snake died. But this is OK.
    }
    snakes_ll_node = snakes_ll_node->next;
  }

  collision_detection(w);

  snakes_ll_node = w->snakes_ll_head;
  while (snakes_ll_node != NULL) {
    struct snake *snake = snakes_ll_node->value;
    snakes_ll_node = snakes_ll_node->next;
    if (snake->dead) {
      remove_snake(snake);
    }
  }
}

int update_snake(world *w, snake *snake, direction snake_direction) {
  struct vector new_head_position = neighbour(((snake_segment *) snake->segments_ll_head->value)->position, snake_direction);
  if (is_out_of_bounds(&w->grid, new_head_position)) {
    snake->dead = 1;
    return 1;
  }

  /* Move each segment forward by 1. */
  linked_list * ll_segment = snake->segments_ll_head;
  while (ll_segment->next != NULL) {
    vector segment_position = ((snake_segment *) ll_segment->value)->position;
    ll_segment = ll_segment->next;
    ((snake_segment *) ll_segment->value)->position = segment_position;
  }

  /* Update the head segment position. */
  ((snake_segment *) snake->segments_ll_head->value)->position = new_head_position;
  return 0;
}

int heads_collided(snake *s1, snake *s2) {
  vector s1_position = ((snake_segment *) s1->segments_ll_head->value)->position;
  vector s2_position = ((snake_segment *) s2->segments_ll_head->value)->position;
  return (s1 != s2 && vectors_equal(s1_position, s2_position));
}

int segment_at_position(snake *s, vector position) {
  linked_list * segments_ll_node = s->segments_ll_head;
  while (segments_ll_node != NULL) {
    vector segment_position = ((snake_segment *) segments_ll_node->value)->position;
    if (vectors_equal(position, segment_position)) {
      return 1;
    }
    segments_ll_node = segments_ll_node->next;
  }
  return 0;
}

void collision_detection(world *w) {
  // This can be optimised somewhat, to avoid duplicate checks and already-dead checks.
  // However care is needed to avoid allowing self-collision or unfair survival.
  linked_list * snakes_ll_node = w->snakes_ll_head, * snakes_ll_collision_node;
  while (snakes_ll_node != NULL) {
    snake * s = snakes_ll_node->value;

    snakes_ll_collision_node = w->snakes_ll_head;
    while (snakes_ll_collision_node != NULL) {
      snake * collision_snake = snakes_ll_collision_node->value;

      if (heads_collided(s, collision_snake)) {
        s->dead = collision_snake->dead = 1;
        break;
      }

      if (segment_at_position(collision_snake, ((snake_segment *) s->segments_ll_head->value)->position)) {
        s->dead = 1;
        break;
      }
    }

    snakes_ll_node = snakes_ll_node->next;
  }
}

int main() {
  return 0;
}
