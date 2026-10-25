#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0, 0x24, 0x27, 0, 0x18, 0x1b};
    dst_open(s, sizeof(s));
    next_stitch(Stitch_Normal, 10.8f, 10.8f);
    next_stitch(Stitch_Normal, -10.8f, -10.8f);
    pattern_close();
    return 0;
}
