#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {10, 20, 0x76, 0x6c, 0xff};
    pes_open(s, sizeof(s));
    next_stitch(Stitch_Stop, 0, 0);
    next_stitch(Stitch_Normal, 1, -2);
    next_stitch(Stitch_Normal, -1, 2);
    pattern_close();
    return 0;
}
