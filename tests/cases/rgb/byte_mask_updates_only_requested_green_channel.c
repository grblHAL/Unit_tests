#include "support/rgb_host.h"

int main(void)
{
    uint8_t bytes[3] = {10, 20, 30};
    rgb_1bpp_pack(bytes, (rgb_color_t){.R = 88, .G = 77, .B = 99},
                  (rgb_color_mask_t){.G = true}, 255);
    CHECK(bytes[0] == 77 && bytes[1] == 20 && bytes[2] == 30);
    return EXIT_SUCCESS;
}
