#include "support/rgb_host.h"

int main(void)
{
    rgb_color_t color = {.R = 255, .G = 128, .B = 64, .W = 17};
    color = rgb_set_intensity(color, 128);
    check_rgb(color, 128, 64, 32);
    CHECK(color.W == 17);
    color = rgb_reset_intensity(color, 255);
    check_rgb(color, 128, 64, 32);
    CHECK(color.W == 17);
    return EXIT_SUCCESS;
}
