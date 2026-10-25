#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {1, 0, 0x83, 0, 0, 0xc3, 0, 0, 3};
    dst_open(s, sizeof(s));
    next_stitch(Stitch_Jump, .1f, 0);
    next_stitch(Stitch_Stop, 0, 0);
    next_stitch(Stitch_Normal, 0, 0);
    pattern_close();
    return 0;
}
