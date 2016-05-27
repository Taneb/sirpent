#include <stdlib.h>

#include "list.h"

linked_list * new() {
  return 0;
}

linked_list * prepend(void * value, linked_list * list) {
  linked_list * new = (linked_list *)malloc(sizeof(linked_list));
  new->value = value;
  new->next = list;
  return new;
}

int search(void * needle, linked_list * haystack) {
  while (haystack) {
    if (haystack->value == needle) {
      return 1;
    }
    haystack = haystack->next;
  }
  return 0;
}

void destroy(linked_list * list) {
  while(list) {
    linked_list * tmp = list->next;
    free(list);
    list = tmp;
  }
}
