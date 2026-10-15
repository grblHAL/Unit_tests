#include "support/rgb_host.h"

int main(void)
{
    uint8_t bytes[3] = {0};
    rgb_color_t color = {.R = 34, .G = 17, .B = 51};
    rgb_1bpp_pack(bytes, color, all_rgb_channels(), 255);
    CHECK(bytes[0] == 17 && bytes[1] == 34 && bytes[2] == 51);
    check_rgb(rgb_1bpp_unpack(bytes, 255), 34, 17, 51);
    return EXIT_SUCCESS;
}
