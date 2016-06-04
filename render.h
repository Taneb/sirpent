#ifndef RENDER_H
#define RENDER_H

#include <X11/Xlib.h>

#include "world.h"

void init_display();
void draw_world(world * w);

#endif
