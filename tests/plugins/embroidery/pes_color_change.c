#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0xfe, 0xb0, 1, 1, 1, 0xff};
    pes_open(s, sizeof(s));
    CHECK(next_stitch(Stitch_Stop, 0, 0).color == 5);
    CHECK(next_stitch(Stitch_Stop, 0, 0).color == 2);
    next_stitch(Stitch_Normal, .1f, -.1f);
    pattern_close();
    return 0;
}
