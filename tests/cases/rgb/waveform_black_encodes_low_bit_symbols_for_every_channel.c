#include "support/rgb_host.h"

int main(void)
{
    uint8_t bytes[9] = {0};
    const uint8_t expected[] = {0x49, 0x24, 0x92, 0x49, 0x24, 0x92, 0x49, 0x24, 0x92};
    rgb_3bpp_pack(bytes, (rgb_color_t){0}, all_rgb_channels(), 255);
    CHECK(memcmp(bytes, expected, sizeof(bytes)) == 0);
    check_rgb(rgb_3bpp_unpack(bytes, 255), 0, 0, 0);
    return EXIT_SUCCESS;
}
