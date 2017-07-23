#include "props.h"
#include "images.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <tice.h>

props_t props;

void init_props(void) {
    uint8_t i;
    
    props.sprite1 = cloud_sprite[2];
    props.sprite2 = cloud_sprite[1];
    props.sprite3 = cloud_sprite[0];
    
    for (i = 0; i < PROP_MAX_AMT * 2; i++) {
        add_prop();
    }
}


void add_prop(void) {
    uint8_t depth = randInt(1, 3);
    prop_t *prop;
    uint8_t *num;
    
    switch (depth) {
        case 1:
            num = &props.num1;
            prop = &props.depth1[*num];
            break;
        case 2:
            num = &props.num2;
            prop = &props.depth2[*num];
            break;
        default:
            num = &props.num3;
            prop = &props.depth3[*num];
            break;
    }
    
    if (*num < PROP_MAX_AMT) {
        prop->x = randInt(0, 240);
        prop->y = randInt(0, 240);
        *num += 1;
    }
}

void update_props(void) {
    props.ctr2++;
    props.ctr3++;
}
