#include "props.h"
#include "images.h"
#include "helpers.h"
#include "main.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <tice.h>

void init_props(void) {
    uint8_t i;
    
    mregion = &spawn_regions[4];
    
    for (i = 0; i < PROP_AMT; i++) {
        update_prop(&props[i]);
    }
}

prop_t props[PROP_AMT];
uint8_t num_props;
uint8_t prop_ctr2;
uint8_t prop_ctr3;

void update_prop(prop_t *p) {
    uint8_t depth = randInt(1, 3);
    uint8_t use_dir = (uint8_t)rand();
    spawn_region_t *s;
    
    switch (depth) {
        case 1:
            p->sprite = cloud_sprite[2];
            break;
        case 2:
            p->sprite = cloud_sprite[1];
            break;
        default:
            p->sprite = cloud_sprite[0];
            break;
    }
    
    p->depth = depth;
    if (use_dir & 1) {
        s = mregion;
    } else {
        s = &spawn_regions[use_dir & 3];
    }
    p->x = randInt(s->xmin, s->xmax);
    p->y = randInt(s->ymin, s->ymax);
    num_props += 1;
}

void update_props(void) {
    prop_ctr2++;
    prop_ctr3++;
}
