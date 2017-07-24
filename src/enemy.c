#include "enemy.h"
#include "props.h"
#include "images.h"
#include "helpers.h"
#include "player.h"
#include "main.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <tice.h>

void init_enemies(void) {
    uint8_t i;
    
    mregion = &spawn_regions[4];
    
    for (i = 0; i < ENEMY_AMT; i++) {
        update_enemy(&enemy[i]);
    }
}

enemy_t enemy[ENEMY_AMT];

void update_enemy(enemy_t *e) {
    const uint8_t nindex[] = { 8, 12, 0, 4 };
    uint8_t use_dir = (uint8_t)rand();
    spawn_region_t *s;
    
    e->smart = rand() & 1;
    e->ctr = 9;
    e->reload = 9;
    
    s = &spawn_regions[use_dir & 3];
    if (e->smart) {
        e->index = nindex[use_dir & 3];
    } else {
        e->index = (8 - mplayer.index) & 15;
    }
    e->dx = rdx[e->index];
    e->dy = rdy[e->index];
    e->sprite = enemy_sprite[e->index];
    e->x = randInt(s->xmin, s->xmax);
    e->y = randInt(s->ymin, s->ymax);
    e->destroy_index = 0;
}

void update_enemies(void) {
    
}
