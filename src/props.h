#ifndef PROPS_H
#define PROPS_H

#include <stdint.h>
#include <graphx.h>

typedef struct {
    int x;
    int y;
    gfx_rletsprite_t *sprite;
    uint8_t depth;
} prop_t;

#define PROP_AMT 18

extern prop_t props[PROP_AMT];
extern uint8_t num_props;
extern uint8_t prop_ctr2;
extern uint8_t prop_ctr3;

void init_props(void);
void update_prop(prop_t *p);
void update_props(void);

#endif
