#include "draw.h"
#include "main.h"
#include "props.h"
#include "player.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <tice.h>
#include <graphx.h>

void update_screen(void) {
    int x, y;
    uint8_t i;
    uint8_t *d;
    prop_t *p;
    bullet_t *b;
    bool update_prop2 = false;
    bool update_prop3 = false;
    
    if (prop_ctr2 == 2) {
        update_prop2 = true;
        prop_ctr2 = 0;
    }
    
    if (prop_ctr3 == 3) {
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
        if ((p->depth == 3 && update_prop3) || (p->depth == 2 && update_prop2) || (p->depth == 1)) {
            update_global(p);
        }
        if (x > 265 || y > 265 || x < -60 || y < -25) {
            update_prop(p);
        }
    }
    
    gfx_SetColor(bullet_color_index);
    for (i = 0; i < 8; i++) {
        b = &mplayer.bullets[i];
        gfx_FillRectangle(b->x, b->y, 3, 3);
        update_glocal(b);
    }
    
    // draw the player
    gfx_RLETSprite(mplayer.sprite, PLAYER_X_POS, PLAYER_Y_POS);
    
    // copy to the screen
    gfx_BlitRectangle(gfx_buffer, 0, 0, 240, 240);
}
