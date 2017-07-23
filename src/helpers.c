#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int8_t rdx[] = {  0,  1,  2,  3,  4,  3,  2,  1,  0, -1, -2, -3, -4, -3, -2, -1 };
const int8_t rdy[] = { -4, -3, -2, -1,  0,  1,  2,  3,  4,  3,  2,  1,  0, -1, -2, -3 };

const spawn_region_t spawn_regions[] = {
    { -10, 250, -25, -16 },
    { 240, 250, -10, 250 },
    { -10, 250, 240, 250 },
    { -55, -46, -10, 250 },
    { -10, 240, -10, 240 },
};
