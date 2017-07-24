#ifndef ENEMY_H
#define ENEMY_H

#include <stdint.h>
#include <graphx.h>

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int hit_x;
    int hit_xlen;
    int hit_y;
    int hit_ylen;
    gfx_rletsprite_t *sprite;
    uint8_t destroy_index;
    
    uint8_t dir;
    bool smart;
    uint8_t index;
    uint8_t turn;
    
    uint8_t ctr;
    uint8_t reload;
} enemy_t;

#define ENEMY_AMT 10

extern enemy_t enemy[ENEMY_AMT];

void init_enemies(void);
void update_enemy(enemy_t *e);
void update_enemies(void);

#endif
