#include "main.h"
#include "draw.h"
#include "props.h"
#include "images.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tice.h>
#include <intce.h>
#include <decompress.h>

#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>

spawn_region_t *mregion;
game_t mgame;
level_t mlevel;

void exit_game(void) {
    int_Reset();
    gfx_End();
    exit(0);
}

// called when user presses or releases a key
void interrupt isr_keyboard(void) {
    kb_key_t g1 = kb_Data[1];
    kb_key_t g7 = kb_Data[7];
    
    // check if firing is enabled
    if (g1 & kb_2nd) {
        mplayer.firing = true;
        mplayer.ctr_bullet = 0;
    } else {
        mplayer.firing = false;
    }
    
    if (g7 & kb_Right) {
        mplayer.dir = 1;
    } else if (g7 & kb_Left) {
        mplayer.dir = -1;
    } else {
        mplayer.dir = 0;
    }
    
    if (g1 & kb_Del) {
        exit_game();
    }
    
    int_Acknowledge = INT_KEYBOARD;
    kb_IntAcknowledge = KB_DATA_CHANGED;
}

void main(void) {
    uint8_t i;
    uint8_t player_curr = 0;
    kb_key_t arrows;
    
    // seed random
    srand(rtc_Time());
    
    // decompress images
    malloc_static_images();
    
    // set the level
    mgame.level = 1;
    
    // start the graphics
    gfx_Begin();
    gfx_SetPalette(other_gfx_pal, sizeof_other_gfx_pal);
    
    // set the background
    gfx_FillScreen(black_color_index);
    gfx_SetDrawBuffer();
    
    // setup interrupts
    int_Initialize();
    
    int_SetVector(KEYBOARD_IVECT, isr_keyboard);
    int_EnableConfig = INT_KEYBOARD;
    kb_SetMode(MODE_3_CONTINUOUS);
    kb_EnableInt = KB_DATA_CHANGED;
    
    // decompress level sprites
    malloc_level_images(mgame.level);
    
    // enable interrupts
    int_Enable();
    
    init_props();
    
    do {
        update_player();
        update_props();
        update_screen();
    } while (!mlevel.done);
    
    exit_game();
}
