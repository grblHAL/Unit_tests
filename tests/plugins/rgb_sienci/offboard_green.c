#include "rgb_host.h"
static void offboard(unsigned r, unsigned g, unsigned b)
{
#if STATUS_LIGHT_ENABLE == 2
    rgb_expect(1, r, g, b);
#else
    for (unsigned i = 12; i < hal.rgb0.num_devices; i++)
        CHECK(pixels[0][i].R == r && pixels[0][i].G == g && pixels[0][i].B == b);
#endif
}
int main(void)
{
    rgb_start();
    CHECK(rgb_command(1, 3, 255, true) == Status_OK);
    offboard(0, 255, 0);
    rgb_state(STATE_ALARM);
#if STATUS_LIGHT_ENABLE == 3
    rgb_run_next();
#endif
    offboard(0, 255, 0);
    CHECK(rgb_command(1, 2, 255, true) == Status_OK);
#if STATUS_LIGHT_ENABLE == 3
    rgb_run_next();
#endif
    offboard(0, 0, 0);
    rgb_state(STATE_CYCLE);
    offboard(0, 0, 0);
    CHECK(rgb_command(1, 0, 255, true) == Status_OK);
    offboard(0, 255, 0);
    rgb_state(STATE_SLEEP);
    offboard(127, 127, 127);
    while (pending)
        rgb_run_next();
    offboard(127, 127, 127);
    return 0;
}
