#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>

#define PLAYER_POS    (240 / 2 - 4)
#define PLAYER_CENTER ((240 / 2 - 4) + 8)

#define MAX_RADIUS          400
#define MAX_RADIUS_SQUARED  (MAX_RADIUS * MAX_RADIUS)

#define white_color_index  99
#define black_color_index  98
#define bg_color_index     97
#define bullet_color_index 96
#define red_color_index    95

typedef struct {
    // this controls where new things will spawn
    int xmin;
    int xmax;
    int ymin;
    int ymax;
} spawn_region_t;

typedef struct {
    bool done;
    bool boss_active;
    uint8_t progress;
    uint8_t num_enemy_sprites;
    uint8_t num_boss_sprites;
} level_t;

typedef struct {
    uint8_t level;
    unsigned int high;
} game_t;

extern spawn_region_t *mregion;
extern game_t mgame;
extern level_t mlevel;

void exit_game(void);

#endif
