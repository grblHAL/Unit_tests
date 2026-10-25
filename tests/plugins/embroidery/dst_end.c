#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0, 0, 0xf3, 1, 0, 3};
    dst_open(s, sizeof(s));
    stitch_t end = {0};
    CHECK(!pattern_api.get_stitch(&end, pattern_file));
    CHECK(vfs_tell(pattern_file) == 515);
    pattern_close();
    return 0;
}
