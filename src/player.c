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
        
        switch (index) {
            case 0:
                mregion = &spawn_regions[0];
                break;
            case 4:
                mregion = &spawn_regions[1];
                break;
            case 8:
                mregion = &spawn_regions[2];
                break;
            case 12:
                mregion = &spawn_regions[3];
                break;
            default:
                break;
        }
    }
    
    if (mplayer.firing) {
        if (mplayer.ctr_bullet == 0) {
            fire_bullet();
            mplayer.ctr_bullet = 9;
        } else {
            mplayer.ctr_bullet--;
        }
    }
    
    mplayer.sprite = player_sprite[index];
    mplayer.index = index;
}
