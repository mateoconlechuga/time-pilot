#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tice.h>
#include <decompress.h>

#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>

static void *player_sprite_data[17] = {
    NULL,
    player_1_compressed,
    player_2_compressed,
    player_3_compressed,
    player_4_compressed,
    player_5_compressed,
    player_6_compressed,
    player_7_compressed,
    player_8_compressed,
    player_9_compressed,
    player_10_compressed,
    player_11_compressed,
    player_12_compressed,
    player_13_compressed,
    player_14_compressed,
    player_15_compressed,
    player_16_compressed
};
static gfx_rletsprite_t **player_sprite = player_sprite_data;

#define player_sprite_size ((player_1_width+1)*player_1_height)

void main(void) {
    uint8_t i;
    uint8_t player_curr = 0;
    void *sprite_data;
    kb_key_t arrows;
    
    // start the graphics
    gfx_Begin();
    gfx_SetDrawBuffer();
    
    // decompress player sprite data
    for (i = 1; i < 17; i++) {
        sprite_data = malloc(player_sprite_size);
        dzx7_Standard(player_sprite_data[i], sprite_data);
        player_sprite[i-1] = sprite_data;
    }
    
    // set the background
    gfx_SetPalette(other_gfx_pal, sizeof_other_gfx_pal);
    
    gfx_FillScreen(black_color_index);
    gfx_SetColor(bg_color_index);
    gfx_FillRectangle(0, 0, 240, 240);
    
    // draw the test sprite
    gfx_RLETSprite(player_sprite[0], 240 / 2, 240 / 2);
    gfx_BlitBuffer();
    
    do {
        kb_Scan();
        
        arrows = kb_Data[7];
        
        if (!arrows) continue;
        
        // go for index 0
        if (arrows & kb_Up) {
            if (player_curr != 0) {
                if (player_curr >= 8) {
                    player_curr++;
                } else {
                    player_curr--;
                }
            }
        }
        if (arrows & kb_Down) {
            if (player_curr != 8) {
                if (player_curr >= 8) {
                    player_curr--;
                } else {
                    player_curr++;
                }
            }
        }
        if (arrows & kb_Right) {
            if (player_curr != 4) {
                if (player_curr < 4 || player_curr >= 12) {
                    player_curr++;
                } else {
                    player_curr--;
                }
            }
        }
        if (arrows & kb_Left) {
            if (player_curr != 12) {
                if (player_curr < 4 || player_curr >= 12) {
                    player_curr--;
                } else {
                    player_curr++;
                }
            }
        }
        
        player_curr &= 15;
        
        gfx_FillRectangle(100, 100, 100, 100);
        gfx_RLETSprite(player_sprite[player_curr], 240 / 2, 240 / 2);
        delay(80);
        gfx_BlitRectangle(gfx_buffer, 0, 0, 240, 240);
        
    } while (kb_Data[6] != kb_Clear);
    
    gfx_End();
}
