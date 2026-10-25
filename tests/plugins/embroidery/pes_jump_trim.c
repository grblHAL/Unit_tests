#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0x90, 10, 0x90, 20, 0xa0, 30, 0xa0, 40, 0xff};
    pes_open(s, sizeof(s));
    next_stitch(Stitch_Stop, 0, 0);
    next_stitch(Stitch_Jump, 1, -2);
    next_stitch(Stitch_Trim, 3, -4);
    pattern_close();
    return 0;
}
