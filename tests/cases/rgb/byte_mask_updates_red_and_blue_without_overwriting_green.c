#include "support/rgb_host.h"
#include "check.h"

int main(void)
{
    uint8_t bytes[5] = {0xA5, 10, 20, 30, 0x5A};
    rgb_1bpp_pack(bytes + 1, (rgb_color_t){.R = 88, .G = 77, .B = 99},
                  (rgb_color_mask_t){.R = true, .B = true}, 255);
    CHECK(bytes[1] == 10 && bytes[2] == 88 && bytes[3] == 99);
    CHECK(bytes[0] == 0xA5 && bytes[4] == 0x5A);
    return EXIT_SUCCESS;
}
