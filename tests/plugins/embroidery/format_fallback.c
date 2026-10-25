#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {1, 0, 3};
    dst_open(s, sizeof(s));
    CHECK(!vfs_seek(pattern_file, 0));
    embroidery_t api = {0};
    CHECK(!brother_open_file(pattern_file, &api) && vfs_tell(pattern_file) == 0);
    CHECK(tajima_open_file(pattern_file, &api));
    stitch_t stitch = {0};
    CHECK(api.get_stitch(&stitch, pattern_file) && stitch.type == Stitch_Normal &&
          fabsf(stitch.target.x - .1f) < .0001f);
    pattern_close();
    return 0;
}
