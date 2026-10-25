#include "rgb_host.h"
int main(void)
{
    rgb_prepare();
    hal.rgb0.write = hal.rgb1.write = NULL;
    hal.rgb0.set_intensity = hal.rgb1.set_intensity = NULL;
    status_light_init();
    rgb_run_next();
    rgb_expect(0, 255, 255, 255);
    CHECK(rgb_command(0, 2, 80, true) == Status_OK);
    CHECK(rgb_command(1, 3, 80, true) == Status_OK);
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(0, 0, 0, 0);
    rgb_expect(1, 0, 255, 0);
#else
    for (unsigned i = 0; i < 16; i++)
        CHECK(pixels[0][i].R == 0 && pixels[0][i].B == 0 && pixels[0][i].G == (i < 12 ? 0 : 255));
#endif
    CHECK(brightness[0] == 255 && brightness[1] == 255 && writes[0] == 0 && writes[1] == 0 &&
          warnings == 0);
    return 0;
}
