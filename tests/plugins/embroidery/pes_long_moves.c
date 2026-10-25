#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0x81, 0x2c, 0x8e, 0xd4, 0xff};
    pes_open(s, sizeof(s));
    next_stitch(Stitch_Stop, 0, 0);
    next_stitch(Stitch_Normal, 30, 30);
    pattern_close();
    return 0;
}
