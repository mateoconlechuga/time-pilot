#include "images.h"
#include "main.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <compression.h>
#include <graphx.h>

#include "gfx/other_gfx.h"
#include "gfx/level1_gfx.h"
#include "gfx/level2_gfx.h"
#include "gfx/level3_gfx.h"
#include "gfx/level4_gfx.h"
#include "gfx/level5_gfx.h"

gfx_rletsprite_t **prop_sprite;

const unsigned int cloud_sizes[4] = {
    0,
    cloud_1_size,
    cloud_2_size,
    cloud_3_size,
};
const void *cloud_sprite_data[4] = {
    NULL,
    cloud_1_compressed,
    cloud_2_compressed,
    cloud_3_compressed,
};
gfx_rletsprite_t **cloud_sprite = cloud_sprite_data;

// ---------------------------------------------------

const unsigned int asteroid_sizes[4] = {
    0,
    asteroid_1_size,
    asteroid_2_size,
    asteroid_3_size,
};
const void *asteroid_sprite_data[4] = {
    NULL,
    asteroid_1_compressed,
    asteroid_2_compressed,
    asteroid_3_compressed,
};
gfx_rletsprite_t **asteroid_sprite = asteroid_sprite_data;

// ---------------------------------------------------

const unsigned int player_explosion_sizes[5] = {
    0,
    player_explosion_1_size,
    player_explosion_2_size,
    player_explosion_3_size,
    player_explosion_4_size,
};
const void *player_explosion_sprite_data[5] = {
    NULL,
    player_explosion_1_compressed,
    player_explosion_2_compressed,
    player_explosion_3_compressed,
    player_explosion_4_compressed,
};
gfx_rletsprite_t **player_explosion_sprite = player_explosion_sprite_data;

// ---------------------------------------------------

const unsigned int enemy_explosion_sizes[5] = {
    0,
    enemy_explosion_1_size,
    enemy_explosion_2_size,
    enemy_explosion_3_size,
    enemy_explosion_4_size,
};
const void *enemy_explosion_sprite_data[5] = {
    NULL,
    enemy_explosion_1_compressed,
    enemy_explosion_2_compressed,
    enemy_explosion_3_compressed,
    enemy_explosion_4_compressed,
};
gfx_rletsprite_t **enemy_explosion_sprite = enemy_explosion_sprite_data;

// ---------------------------------------------------

const void *parachute_sprite_data[5] = {
    NULL,
    parachute_1_compressed,
    parachute_2_compressed,
    parachute_3_compressed,
    parachute_4_compressed,
};
gfx_rletsprite_t **parachute_sprite = parachute_sprite_data;
#define parachute_sprite_size ((parachute_1_width+1)*parachute_1_height)

// ---------------------------------------------------

const void *player_sprite_data[17] = {
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
gfx_rletsprite_t **player_sprite = player_sprite_data;
#define player_sprite_size (player_1_width*player_1_height)

// ---------------------------------------------------

static void *decompress(void *loc, unsigned int size) {
    void *sprite_data = malloc(size);
    dzx7_Standard(loc, sprite_data);
    return sprite_data;
}

void malloc_static_images(void) {
    uint8_t i;
    
    // decompress player sprite data
    for (i = 1; i < 17; i++) {
        player_sprite[i-1] = decompress(player_sprite_data[i], player_sprite_size);
    }
    
    // decompress cloud sprite data
    for (i = 1; i < 4; i++) {
        uint8_t j = i-1;
        
        cloud_sprite[j] = decompress(cloud_sprite_data[i], cloud_sizes[i]);
        asteroid_sprite[j] = decompress(asteroid_sprite_data[i], asteroid_sizes[i]);
    }
    
    // decompress parachute/explosion sprite data
    for (i = 1; i < 5; i++) {
        uint8_t j = i-1;
        
        parachute_sprite[j] = decompress(parachute_sprite_data[i], parachute_sprite_size);
        player_explosion_sprite[j] = decompress(player_explosion_sprite_data[i], player_explosion_sizes[i]);
        enemy_explosion_sprite[j] = decompress(enemy_explosion_sprite_data[i], enemy_explosion_sizes[i]);
    }
}

// ---------------------------------------------------

const void *enemy_level1_sprite_data[16] = {
    enemy_level1_1_compressed,
    enemy_level1_2_compressed,
    enemy_level1_3_compressed,
    enemy_level1_4_compressed,
    enemy_level1_5_compressed,
    enemy_level1_6_compressed,
    enemy_level1_7_compressed,
    enemy_level1_8_compressed,
    enemy_level1_9_compressed,
    enemy_level1_10_compressed,
    enemy_level1_11_compressed,
    enemy_level1_12_compressed,
    enemy_level1_13_compressed,
    enemy_level1_14_compressed,
    enemy_level1_15_compressed,
    enemy_level1_16_compressed,
};
#define enemy_level1_size 200

const void *boss_level1_sprite_data[4] = {
    boss_level1_1_compressed,
    boss_level1_2_compressed,
    boss_level1_3_compressed,
    boss_level1_4_compressed,
};
#define boss_level1_size 420

// ---------------------------------------------------

const void *enemy_level2_sprite_data[16] = {
    enemy_level2_1_compressed,
    enemy_level2_2_compressed,
    enemy_level2_3_compressed,
    enemy_level2_4_compressed,
    enemy_level2_5_compressed,
    enemy_level2_6_compressed,
    enemy_level2_7_compressed,
    enemy_level2_8_compressed,
    enemy_level2_9_compressed,
    enemy_level2_10_compressed,
    enemy_level2_11_compressed,
    enemy_level2_12_compressed,
    enemy_level2_13_compressed,
    enemy_level2_14_compressed,
    enemy_level2_15_compressed,
    enemy_level2_16_compressed,
};
#define enemy_level2_size 180

const void *boss_level2_sprite_data[4] = {
    boss_level2_1_compressed,
    boss_level2_2_compressed,
    boss_level2_3_compressed,
    boss_level2_4_compressed,
};
#define boss_level2_size 180

// ---------------------------------------------------

const void *enemy_level3_sprite_data[9] = {
    enemy_level3_1_compressed,
    enemy_level3_2_compressed,
    enemy_level3_3_compressed,
    enemy_level3_4_compressed,
    enemy_level3_5_compressed,
    enemy_level3_6_compressed,
    enemy_level3_7_compressed,
    enemy_level3_8_compressed,
    enemy_level3_9_compressed,
};
#define enemy_level3_size 100

const void *boss_level3_sprite_data[4] = {
    boss_level3_1_compressed,
    boss_level3_2_compressed,
    boss_level3_3_compressed,
    boss_level3_4_compressed,
};
#define boss_level3_size 220

// ---------------------------------------------------

const void *enemy_level4_sprite_data[16] = {
    enemy_level4_1_compressed,
    enemy_level4_2_compressed,
    enemy_level4_3_compressed,
    enemy_level4_4_compressed,
    enemy_level4_5_compressed,
    enemy_level4_6_compressed,
    enemy_level4_7_compressed,
    enemy_level4_8_compressed,
    enemy_level4_9_compressed,
    enemy_level4_10_compressed,
    enemy_level4_11_compressed,
    enemy_level4_12_compressed,
    enemy_level4_13_compressed,
    enemy_level4_14_compressed,
    enemy_level4_15_compressed,
    enemy_level4_16_compressed,
};
#define enemy_level4_size 180

const void *boss_level4_sprite_data[3] = {
    boss_level4_1_compressed,
    boss_level4_2_compressed,
    boss_level4_3_compressed,
};
#define boss_level4_size 220

// ---------------------------------------------------

const void *enemy_level5_sprite_data[1] = {
    enemy_level5_compressed,
};
//#define enemy_level5_size enemy_level5_size

const void *boss_level5_sprite_data[4] = {
    boss_level5_1_compressed,
    boss_level5_2_compressed,
    boss_level5_3_compressed,
    boss_level5_4_compressed,
};
#define boss_level5_size 400

// ---------------------------------------------------

void *enemy_sprite_data[16];
gfx_rletsprite_t **enemy_sprite = enemy_sprite_data;

void *boss_sprite_data[6];
gfx_rletsprite_t **boss_sprite = boss_sprite_data;

void malloc_level_images(uint8_t level) {
    void *sprite_data;
    uint8_t i = 0;
    uint8_t j = 0;
    
#define decompress_enemy(num, index) \
    enemy_sprite[index] = decompress(enemy_level##num##_sprite_data[i], enemy_level##num##_size)

#define decompress_boss(num, index) \
    boss_sprite[index] = decompress(boss_level##num##_sprite_data[i], boss_level##num##_size)
    
    mlevel.num_enemy_sprites = 16;
    mlevel.num_boss_sprites = 4;
    
    switch (level) {
        case 1:
            for (; i < 16; i++) {
                decompress_enemy(1, i);
            }
            for (; j < 4; j++) {
                decompress_boss(1, j);
            }
            break;
        case 2:
            for (; i < 16; i++) {
                decompress_enemy(2, i);
            }
            for (; j < 4; j++) {
                decompress_boss(2, j);
            }
            break;
        case 3:
            for (; i < 9; i++) {
                decompress_enemy(3, i);
            }
            for (; j < 4; j++) {
                decompress_boss(3, j);
            }
            mlevel.num_enemy_sprites = 9;
            break;
        case 4:
            for (; i < 16; i++) {
                decompress_enemy(4, i);
            }
            for (; j < 3; j++) {
                decompress_boss(4, j);
            }
            mlevel.num_boss_sprites = 3;
            break;
        case 5:
            for (; i < 1; i++) {
                decompress_enemy(5, i);
            }
            for (; j < 4; j++) {
                decompress_boss(5, j);
            }
            mlevel.num_enemy_sprites = 1;
            break;
    }
    
#undef decompress_boss
#undef decompress_enemy
}


void free_level_images(void) {
    uint8_t i = 0;
    uint8_t j = 0;
    
    for (; i < mlevel.num_enemy_sprites; i++) {
        free(enemy_sprite[i]);
    }
    for (; j < mlevel.num_boss_sprites; j++) {
        free(boss_sprite[j]);
    }
}
