#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "rgb.h"
#include "check.h"

static inline void check_rgb(rgb_color_t color, uint8_t red, uint8_t green, uint8_t blue)
{
    CHECK(color.R == red && color.G == green && color.B == blue);
}
static inline rgb_color_mask_t all_rgb_channels(void)
{
    return (rgb_color_mask_t){.R = true, .G = true, .B = true};
}
