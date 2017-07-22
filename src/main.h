#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#define white_color_index 99
#define black_color_index 98
#define bg_color_index    97

typedef struct {
    uint8_t num_enemy_sprites;
    uint8_t num_boss_sprites;
} level_t;

typedef struct {
    uint8_t level;
} game_t;

extern game_t mgame;
extern level_t mlevel;

#endif
