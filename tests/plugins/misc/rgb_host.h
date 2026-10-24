#pragma once
#include "misc_host.h"
void rgb_led_init(void);
void prepare_rgb(bool masked, bool white);
extern unsigned rgb_calls[2], rgb_flushes[2], intensity_calls;
extern uint8_t intensity;
extern rgb_color_t colors[2][3];
extern rgb_color_mask_t last_mask;
