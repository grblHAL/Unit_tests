#include "support/rgb_host.h"

static void output(uint16_t device, rgb_color_t color) { (void)device; (void)color; }
int main(void)
{
    rgb_ptr_t device = {.out = output, .cap = {.R = 255, .G = 255, .B = 255}};
    CHECK(rgb_is_neopixels(&device) && !rgb_is_onoff(&device));
    device.cap = (rgb_color_t){.R = 1, .G = 1, .B = 1};
    CHECK(!rgb_is_neopixels(&device) && rgb_is_onoff(&device));
    const rgb_color_t mixed[] = {
        {.R = 255, .G = 1, .B = 255}, {.R = 255, .G = 255, .B = 1},
        {.R = 1, .G = 255, .B = 1}, {.R = 1, .G = 1, .B = 255}
    };
    for(unsigned i = 0; i < sizeof(mixed) / sizeof(mixed[0]); i++) {
        device.cap = mixed[i];
        CHECK(!rgb_is_neopixels(&device) && !rgb_is_onoff(&device));
    }
    device.cap = (rgb_color_t){.R = 1, .G = 1, .B = 1};
    device.out = NULL;
    CHECK(!rgb_is_neopixels(&device) && !rgb_is_onoff(&device));
    device.cap = (rgb_color_t){.R = 255, .G = 255, .B = 255};
    CHECK(!rgb_is_neopixels(&device) && !rgb_is_onoff(&device));
    return EXIT_SUCCESS;
}
