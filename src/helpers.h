#ifndef HELPERS_H
#define HELPERS_H

#include "main.h"

#include <stdint.h>

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} bullet_t;

extern const int8_t rdx[];
extern const int8_t rdy[];
extern const uint8_t pdx[];
extern const uint8_t pdy[];
extern const uint8_t font[];

extern const spawn_region_t spawn_regions[];

#define update_global(p) \
    do { p->y -= mplayer.dy; p->x -= mplayer.dx; } while (0)
#define update_glocal(p) \
    do { p->y += p->dy - mplayer.dy; p->x += p->dx - mplayer.dx; } while (0)

#endif
