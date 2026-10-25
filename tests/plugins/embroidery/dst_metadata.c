#include "embroidery_host.h"
int main(void)
{
    const uint8_t s[] = {0, 0, 0xf3};
    dst_open(s, sizeof(s));
    CHECK(!strcmp(pattern_api.name, "Pocket") && pattern_api.stitches == 4 &&
          pattern_api.color_changes == 2);
    CHECK(fabsf(pattern_api.max.x - 12.1f) < 0.0001f && pattern_api.min.x == -2 &&
          pattern_api.max.y == 8 && fabsf(pattern_api.min.y + 1.1f) < 0.0001f);
    CHECK(!strcmp(pattern_api.get_thread_color(5), "None"));
    pattern_close();
    return 0;
}
