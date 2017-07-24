#ifndef PLAYER_H
#define PLAYER_H

#include "helpers.h"

#include <stdint.h>
#include <graphx.h>

#define MAX_PLAYER_BULLETS 7

typedef struct {
    int8_t dx;
    int8_t dy;
    int8_t dx_save;
    int8_t dy_save;
    int8_t velocity;
    
    // bullet stuff
    bool firing;
    uint8_t ctr_bullet;
    uint8_t num_bullet;
    bullet_t bullets[MAX_PLAYER_BULLETS+1];
    int8_t dir;
    
    uint8_t lives;
    
    uint8_t index;
    gfx_rletsprite_t *sprite;
    
    unsigned int score;
    bool failed;
    bool done;
    
    unsigned int parachute_chain;
    
    // used for controlling velocity
    uint8_t ctr;
    uint8_t reload;
    
    // used for controlling rotation speed
    uint8_t rotate;
} player_t;

extern player_t mplayer;

void init_player(void);
void update_player(void);
void update_scores(unsigned int score);
void update_progress(void);

#endif
