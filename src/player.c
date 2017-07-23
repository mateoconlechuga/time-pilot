#include "player.h"
#include "images.h"
#include "helpers.h"
#include "main.h"

#include <intce.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    
    if (mplayer.done) {
        mplayer.index++;
        if (mplayer.index == 20) {
            exit_game();
        }
        return;
    } else
    
    if (mplayer.failed) {
        if (index == 4 * 4) {
            mplayer.done = true;
            mplayer.index = 0;
        } else {
            mplayer.sprite = player_explosion_sprite[index / 4];
            mplayer.index++;
        }
        return;
    }
    
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

void update_scores(unsigned int score) {
    uint8_t len;
    
    gfx_SetDrawScreen();
    
    mplayer.score += score;
    
    if (mplayer.score > mgame.high) {
        mgame.high = mplayer.score;
    }
    
    len = log10(mgame.high) + 1;
    gfx_SetTextXY(303 - len * 8, 9);
    gfx_PrintUInt(mgame.high, len);
    len = log10(mplayer.score) + 1;
    gfx_SetTextXY(303 - len * 8, 41);
    gfx_PrintUInt(mplayer.score, len);
    
    gfx_SetDrawBuffer();
}

void update_progress(void) {
    gfx_SetDrawScreen();
    
    if (mlevel.progress == 56) {
        mlevel.boss_active = true;
    } else {
        mlevel.progress++;
    
        gfx_SetColor(white_color_index);
        gfx_SetPixel(240 + 11 + mlevel.progress, 191);
    }
    
    gfx_SetDrawBuffer();
}
