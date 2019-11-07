#include "main.h"
#include "draw.h"
#include "props.h"
#include "enemy.h"
#include "images.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tice.h>
#include <compression.h>

#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>

spawn_region_t *mregion;
game_t mgame;
level_t mlevel;

void exit_game(void) {
    gfx_End();
    exit(0);
}

void update_keyboard(void) {
    kb_key_t g1;
    kb_key_t g7;
    static kb_key_t g1_prev;
    static kb_key_t g7_prev;

    kb_Scan();

    g1 = kb_Data[1];
    g7 = kb_Data[7];

    if ((g1 != g1_prev) || (g7 != g7_prev)) {
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
    }
    g7_prev = g7;
    g1_prev = g1;
}

void main(void) {
    uint8_t i;
    uint24_t x;
    uint8_t y;

    // seed random
    srand(rtc_Time());

    // decompress images
    malloc_static_images();

    // set the level
    mgame.level = 1;
    mgame.high = 10000;

    mlevel.progress = 0;
    mlevel.boss_active = false;

    init_player();

    // start the graphics
    gfx_Begin();
    gfx_SetPalette(other_gfx_pal, sizeof_other_gfx_pal, 0);

    // set the background
    gfx_FillScreen(black_color_index);
    gfx_SetTextFGColor(red_color_index);
    gfx_SetFontData((uint8_t*)font);
    gfx_SetMonospaceFont(8);
    gfx_PrintStringXY("HI-SCORE", 320 - 64, 0);
    gfx_PrintStringXY("1-UP", 320 - 56, 32);
    gfx_SetTextFGColor(white_color_index);
    gfx_SetTextBGColor(black_color_index);
    gfx_SetTextTransparentColor(0);
    gfx_SetColor(white_color_index);
    gfx_Rectangle_NoClip(240 + 11, 190, 58, 3);
    gfx_PrintStringXY("LEVEL ", 320 - 68, 200);
    gfx_PrintUInt(mgame.level, 1);
    i = mplayer.lives;
    x = 320 - 74;
    y = 110;
    while (i--) {
        gfx_RLETSprite_NoClip(player_sprite[0], x, y);
        x += 18;
        if (i == 4) {
            y += 18;
            x = 320 - 74;
        }
    }
    update_scores(0);
    gfx_SetClipRegion(0, 0, 240, 240);

    // decompress level sprites
    malloc_level_images(mgame.level);

    init_props();
    init_enemies();

    do {
        update_keyboard();
        update_player();
        update_props();
        update_parachutes();
        update_screen();
    } while (!mlevel.done);

    exit_game();
}
