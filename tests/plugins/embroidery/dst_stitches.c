#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0x85, 0x81, 0x03, 0x4a, 0x42, 0x03, 0, 0, 0xf3};
    dst_open(s, sizeof(s));
    next_stitch(Stitch_Normal, 1.3f, .4f);
    next_stitch(Stitch_Normal, -1.3f, -.4f);
    stitch_t end = {0};
    CHECK(!pattern_api.get_stitch(&end, pattern_file));
    pattern_close();
    return 0;
}
