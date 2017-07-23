#ifndef PROPS_H
#define PROPS_H

#include <stdint.h>
#include <graphx.h>

typedef struct {
    int x;
    int y;
} prop_t;

#define PROP_MAX_AMT 20

typedef struct {
    uint8_t ctr2;
    uint8_t ctr3;
    uint8_t num1;
    uint8_t num2;
    uint8_t num3;
    prop_t depth1[PROP_MAX_AMT];
    prop_t depth2[PROP_MAX_AMT];
    prop_t depth3[PROP_MAX_AMT];
    gfx_rletsprite_t *sprite1;
    gfx_rletsprite_t *sprite2;
    gfx_rletsprite_t *sprite3;
} props_t;

extern props_t props;

void init_props(void);
void add_prop(void);
void update_props(void);

#endif
