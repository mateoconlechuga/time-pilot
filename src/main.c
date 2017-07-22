#include "main.h"
#include "images.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tice.h>
#include <decompress.h>

#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>

game_t mgame;
level_t mlevel;

void main(void) {
    uint8_t i;
    uint8_t player_curr = 0;
    kb_key_t arrows;
    
    // decompress images
    malloc_static_images();
    
    // set the level
    mgame.level = 1;
    
    // start the graphics
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(other_gfx_pal, sizeof_other_gfx_pal);
    
    // set the background
    gfx_FillScreen(black_color_index);
    gfx_SetColor(bg_color_index);
    gfx_FillRectangle(0, 0, 240, 240);
    
    
    // decompress level sprites
    malloc_level_images(mgame.level);
    
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
