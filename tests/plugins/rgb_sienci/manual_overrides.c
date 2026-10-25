#include "rgb_host.h"
int main(void)
{
    rgb_start();
    CHECK(rgb_command(0, 2, 255, true) == Status_OK);
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(0, 0, 0, 0);
    rgb_expect(1, 255, 255, 255);
#else
    for (unsigned i = 0; i < 12; i++)
        CHECK(pixels[0][i].value == 0);
    CHECK(pixels[0][12].R == 255);
#endif
    CHECK(rgb_command(0, 3, 255, true) == Status_OK);
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(0, 0, 255, 0);
#else
    for (unsigned i = 0; i < 12; i++)
        CHECK(pixels[0][i].G == 255 && pixels[0][i].R == 0);
#endif
    CHECK(rgb_command(1, 2, 255, true) == Status_OK);
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(1, 0, 0, 0);
#else
    CHECK(pixels[0][12].value == 0);
#endif
    CHECK(rgb_command(0, 1, 255, true) == Status_OK);
    CHECK(rgb_command(1, 1, 255, true) == Status_OK);
    rgb_expect(0, 255, 255, 255);
    CHECK(rgb_command(0, 0, 255, true) == Status_OK);
    rgb_state(STATE_CYCLE);
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(0, 0, 255, 0);
#else
    for (unsigned i = 0; i < 12; i++)
        CHECK(pixels[0][i].G == 255 && pixels[0][i].R == 0);
#endif

    return 0;
}
