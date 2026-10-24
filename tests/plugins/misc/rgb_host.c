#include "rgb_host.h"
unsigned rgb_calls[2], rgb_flushes[2], intensity_calls;
uint8_t intensity;
rgb_color_t colors[2][3];
rgb_color_mask_t last_mask;
static void out0(uint16_t device, rgb_color_t color) { CHECK(device < 3); colors[0][device] = color; rgb_calls[0]++; }
static void out1(uint16_t device, rgb_color_t color) { CHECK(device < 3); colors[1][device] = color; rgb_calls[1]++; }
static void masked0(uint16_t device, rgb_color_t color, rgb_color_mask_t mask) { last_mask = mask; out0(device, color); }
static void flush0(void) { rgb_flushes[0]++; }
static void flush1(void) { rgb_flushes[1]++; }
static uint8_t set_intensity(uint8_t value) { uint8_t old = intensity; intensity = value; intensity_calls++; return old; }
void prepare_rgb(bool masked)
{
 prepare_hooks();
 hal.rgb0 = (rgb_ptr_t){.out = out0, .out_masked = masked ? masked0 : NULL, .write = flush0, .num_devices = 3, .flags.is_strip = On};
 hal.rgb1 = (rgb_ptr_t){.out = out1, .write = flush1, .set_intensity = set_intensity, .num_devices = 2, .flags.is_strip = On};
 rgb_led_init();
}
