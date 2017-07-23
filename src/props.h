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

#define PROP_AMT 16

extern prop_t props[PROP_AMT];
extern uint8_t prop_ctr2;
extern uint8_t prop_ctr3;

void init_props(void);
void update_prop(prop_t *p);
void update_props(void);

typedef struct {
    int x;
    int y;
} parachute_t;

#define PARACHUTE_AMT 2

extern parachute_t parachutes[PARACHUTE_AMT];
extern gfx_rletsprite_t *parachute_sprite_current;
extern uint8_t parachute_ctr;
extern uint8_t parachute_index;

void update_parachute(parachute_t *p);
void update_parachutes(void);

#endif
