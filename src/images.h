#ifndef IMAGES_H
#define IMAGES_H

#include <graphx.h>

#include "gfx/other_gfx.h"

extern gfx_rletsprite_t **cloud_sprite;
extern gfx_rletsprite_t **player_sprite;
extern gfx_rletsprite_t **parachute_sprite;
extern gfx_rletsprite_t **enemy_explosion_sprite;
extern gfx_rletsprite_t **player_explosion_sprite;

extern gfx_rletsprite_t **prop_sprite;
extern gfx_rletsprite_t **enemy_sprite;
extern gfx_rletsprite_t **boss_sprite;

void malloc_static_images(void);
void malloc_level_images(uint8_t level);
void free_level_images(void);

#endif
