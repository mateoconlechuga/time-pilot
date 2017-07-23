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
    uint8_t i;
    uint8_t *d;
    prop_t *p;
    bullet_t *b;
    bool update_prop2 = false;
    bool update_prop3 = false;
    
    if (props.ctr2 == 2) {
        update_prop2 = true;
        props.ctr2 = 0;
    }
    
    if (props.ctr3 == 3) {
        update_prop3 = true;
        props.ctr3 = 0;
    }
    
    // clear the screen
    gfx_SetColor(bg_color_index);
    gfx_FillRectangle(0, 0, 240, 240);
    
    // draw the props
    for (i = 0; i < props.num3; i++) {
        p = &props.depth3[i];
        gfx_RLETSprite(props.sprite3, p->x, p->y);
        if (update_prop3) {
            update_global(p);
        }
    }
    
    for (i = 0; i < props.num2; i++) {
        p = &props.depth2[i];
        gfx_RLETSprite(props.sprite2, p->x, p->y);
        if (update_prop2) {
            update_global(p);
        }
    }
    
    for (i = 0; i < props.num1; i++) {
        p = &props.depth1[i];
        gfx_RLETSprite(props.sprite1, p->x, p->y);
        update_global(p);
    }
    
    gfx_SetColor(bullet_color_index);
    for (i = 0; (i < mplayer.num_bullet) && i < 8; i++) {
        b = &mplayer.bullets[i];
        gfx_FillRectangle(b->x, b->y, 3, 3);
        update_global(b);
        update_local(b);
    }
    
    // draw the player
    gfx_RLETSprite(mplayer.sprite, PLAYER_X_POS, PLAYER_Y_POS);
    
    // copy to the screen
    gfx_BlitRectangle(gfx_buffer, 0, 0, 240, 240);
}
