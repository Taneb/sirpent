#include "render.h"

#include "udp_list/list.h"
#include "world.h"
#include "vector.h"

Display * display;
Drawable drawable;
GC gc;

void init_display() {
  display = XOpenDisplay(0);
  int black = BlackPixel(display, DefaultScreen(display));
  int white = WhitePixel(display, DefaultScreen(display));
  drawable = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 500, 500, 0, black, white);
  XSelectInput(display, drawable, StructureNotifyMask);
  XMapWindow(display, drawable);
  gc = XCreateGC(display, drawable, 0, 0);
  XSetForeground(display, gc, black);
  while(1) {
    XEvent e;
    XNextEvent(display, &e);
    if (e.type = MapNotify) {
      break;
    }
  }
}

void draw_world(world * w) {
  XClearWindow(display, drawable);
  list_each(w->snakes, snake) {
    list_each(snake.segments, segment) {
      vector vector = segment.position;
      short true_x = 30 + vector.x * 8;
      short true_y = 30 + !(vector.x & 1) * 4 + vector.y * 9;
      XPoint points[6] = {
	{true_x + 2, true_y - 4},
	{true_x - 3, true_y - 4},
	{true_x - 5, true_y + 0},
	{true_x - 2, true_y + 4},
	{true_x + 2, true_y + 4},
	{true_x + 5, true_y + 0}
      };
      XFillPolygon(display, drawable, gc, points, 6, Convex, CoordModeOrigin);
    }
  }
  XFlush(display);
}
