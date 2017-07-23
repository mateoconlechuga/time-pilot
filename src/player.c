#include "player.h"
#include "images.h"
#include "helpers.h"
#include "main.h"

#include <intce.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

player_t mplayer;

static void fire_bullet(void) {
    const uint8_t pdx[] = { 8, 13, 16, 16, 16, 16, 13, 9,  8,  0,  0,  0,  0,  0,  0,  6 };
    const uint8_t pdy[] = { 0,  0,  2,  6,  8, 14, 16, 16, 16, 16, 14, 9,  8,  4,  0,  0 };
    
    bullet_t *b = &mplayer.bullets[mplayer.num_bullet & MAX_PLAYER_BULLETS];
    b->dx = mplayer.dx * 2;
    b->dy = mplayer.dy * 2;
    b->x = PLAYER_X_POS + pdx[mplayer.index];
    b->y = PLAYER_Y_POS + pdy[mplayer.index];
    mplayer.num_bullet++;
}

void update_player(void) {
    uint8_t index = mplayer.index;
    
    if (mplayer.dir) {
        index += mplayer.dir;
        index &= 15;
        mplayer.dx = rdx[index];
        mplayer.dy = rdy[index];
    }
    
    if (mplayer.firing) {
        if (mplayer.ctr_bullet == 0) {
            fire_bullet();
            mplayer.ctr_bullet = 10;
        } else {
            mplayer.ctr_bullet--;
        }
    }
    
    mplayer.sprite = player_sprite[index];
    mplayer.index = index;
}
