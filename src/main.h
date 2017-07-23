#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>

#define PLAYER_X_POS        (240 / 2 - 4)
#define PLAYER_Y_POS        (240 / 2 - 4)

#define MAX_RADIUS          400
#define MAX_RADIUS_SQUARED  (MAX_RADIUS * MAX_RADIUS)

#define white_color_index  99
#define black_color_index  98
#define bg_color_index     97
#define bullet_color_index 96

typedef struct {
    bool done;
    uint8_t num_enemy_sprites;
    uint8_t num_boss_sprites;
} level_t;

typedef struct {
    uint8_t level;
} game_t;

extern game_t mgame;
extern level_t mlevel;

#endif
