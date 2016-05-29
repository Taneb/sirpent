typedef struct linked_list {
  void * value;
  struct linked_list * next, * previous;
} linked_list;

linked_list * new();
linked_list * prepend(void * value, linked_list * list);
int search(void * needle, linked_list * haystack);
void destroy(linked_list * list);
