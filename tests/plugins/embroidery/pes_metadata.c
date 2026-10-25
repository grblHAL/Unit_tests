#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0xff};
    pes_open(s, sizeof(s));
    CHECK(!strcmp(pattern_api.name, "Sample"));
    CHECK(pattern_api.size.x == 120 && pattern_api.size.y == 80);
    CHECK(!strcmp(pattern_api.get_thread_color(5), "Red") &&
          !strcmp(pattern_api.get_thread_color(2), "Blue") &&
          !strcmp(pattern_api.get_thread_color(255), "Undefined"));
    stitch_t first = next_stitch(Stitch_Stop, 0, 0);
    CHECK(first.color == 5);
    CHECK(vfs_tell(pattern_file) == 580);
    CHECK(!pattern_api.get_stitch(&first, pattern_file));
    pattern_close();
    return 0;
}
