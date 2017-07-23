#include "enemy.h"
#include "props.h"
#include "images.h"
#include "helpers.h"
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
uint8_t num_enemies;

void update_enemy(enemy_t *e) {
    uint8_t depth = randInt(1, 3);
    uint8_t use_dir = (uint8_t)rand();
    spawn_region_t *s;
    
    e->sprite = enemy_sprite[0];
    
    if (use_dir & 1) {
        s = mregion;
    } else {
        s = &spawn_regions[use_dir & 3];
    }
    
    e->x = randInt(s->xmin, s->xmax);
    e->y = randInt(s->ymin, s->ymax);
    e->destroy_index = 0;
    num_enemies += 1;
}

void update_enemies(void) {
    prop_ctr2++;
    prop_ctr3++;
}
