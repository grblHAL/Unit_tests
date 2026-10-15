#include "support/rgb_host.h"

int main(void)
{
    uint8_t direct[3] = {255, 255, 255}, waveform[9] = {0};
    rgb_color_t white = {.R = 255, .G = 255, .B = 255};
    rgb_1bpp_pack(direct, white, all_rgb_channels(), 0);
    CHECK(direct[0] == 0 && direct[1] == 0 && direct[2] == 0);
    rgb_3bpp_pack(waveform, white, all_rgb_channels(), 0);
    const uint8_t black[] = {0x49, 0x24, 0x92, 0x49, 0x24, 0x92, 0x49, 0x24, 0x92};
    CHECK(memcmp(waveform, black, sizeof(black)) == 0);
    check_rgb(rgb_1bpp_unpack(direct, 0), 0, 0, 0);
    check_rgb(rgb_3bpp_unpack(waveform, 0), 0, 0, 0);
    return EXIT_SUCCESS;
}
