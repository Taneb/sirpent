typedef struct grid {
  int width, height;
  int *current, *next;
} grid;

typedef struct vector {
  int x, y;
} vector;

typedef enum {
  NORTH,
  NORTHEAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  NORTHWEST
} direction;

grid * new_grid(int width, int height);

void free_grid(grid *g);

int vectors_equal(vector a, vector b);

int is_out_of_bounds(grid *g, vector cell);

vector neighbour(vector cell, direction to_neighbour);
