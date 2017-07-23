#include "draw.h"
#include "main.h"
#include "props.h"
#include "enemy.h"
#include "player.h"
#include "images.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <tice.h>
#include <graphx.h>

#define chk_collision(x, y, w, h, x1, y1, w1, h1) \
    gfx_CheckRectangleHotspot(x, y, w, h, x1, y1, w1, h1)

#define chk_collision_player(x, y, w, h) \
    (!mplayer.done && chk_collision(x, y, w, h, PLAYER_X_POS + 3, PLAYER_Y_POS + 3, 10, 10))

void update_screen(void) {
    int x, y;
    uint8_t i;
    uint8_t j;
    uint8_t *d;
    prop_t *p;
    enemy_t *e;
    bullet_t *b;
    parachute_t *parachute;
    bool update_prop2 = false;
    bool update_prop3 = false;
    bool destroy = false;
    
    if (prop_ctr2 == 2) {
        update_prop2 = true;
        prop_ctr2 = 0;
    }
    
    if (prop_ctr3 == 4) {
        update_prop3 = true;
        prop_ctr3 = 0;
    }
    
    // clear the screen
    gfx_SetColor(bg_color_index);
    gfx_FillRectangle(0, 0, 240, 240);
    
    // draw the props
    for (i = 0; i < PROP_AMT; i++) {
        p = &props[i];
        gfx_RLETSprite(p->sprite, x = p->x, y = p->y);
        if (p->depth == 1 || (update_prop2 && p->depth == 2) || (update_prop3 && p->depth == 3)) {
            update_global(p);
        }
        if (x > 265 || y > 265 || x < -60 || y < -25) {
            update_prop(p);
        }
    }
    
    // draw the enemies
    for (i = 0; i < ENEMY_AMT; i++) {
        e = &enemy[i];
        destroy = e->destroy_index == 12;
        gfx_RLETSprite(e->sprite, x = e->x, y = e->y);
        
        if (e->destroy_index) {
            e->sprite = enemy_explosion_sprite[e->destroy_index / 4];
            e->destroy_index++;
        } else {
            
            e->y += -1;
            
            for (j = 0; j < 8; j++) {
                b = &mplayer.bullets[j];
                if (chk_collision(x + 2, y + 2, 12, 12, b->x, b->y, 3, 3)) {
                    e->destroy_index = 1;
                    b->y = 60000;
                    b->dx = 0;
                    b->dy = 0;
                    update_scores(100);
                    update_progress();
                    break;
                }
            }
            if (chk_collision_player(x + 2, y + 2, 12, 12)) {
                mplayer.failed = true;
                mplayer.index = 0;
                e->destroy_index = 1;
            }
        }
        
        e->y -= mplayer.dy;
        e->x -= mplayer.dx;
        
        if (x > 300 || y > 300 || x < -60 || y < -60 || destroy) {
            update_enemy(e);
        }
    }
    
    for (i = 0; i < PARACHUTE_AMT; i++) {
        parachute = &parachutes[i];
        gfx_RLETSprite(parachute_sprite_current, x = parachute->x, y = parachute->y);
        parachute->y -= mplayer.dy - 1;
        parachute->x -= mplayer.dx;
        if (chk_collision_player(x + 1, y + 1, 14, 14)) {
            if (mplayer.parachute_chain != 5000) {
                mplayer.parachute_chain += 1000;
            }
            update_parachute(parachute);
            update_scores(mplayer.parachute_chain);
        }
    }
    
    gfx_SetColor(bullet_color_index);
    for (i = 0; i < 8; i++) {
        b = &mplayer.bullets[i];
        gfx_FillRectangle(b->x, b->y, 3, 3);
        update_glocal(b);
    }
    
    // draw the player
    if (!mplayer.done) {
        gfx_RLETSprite_NoClip(mplayer.sprite, PLAYER_X_POS, PLAYER_Y_POS);
    }
    
    // copy to the screen
    gfx_BlitRectangle(gfx_buffer, 0, 0, 240, 240);
}
