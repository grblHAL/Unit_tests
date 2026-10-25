#include "rgb_host.h"
int main(void)
{
    rgb_start();
    rgb_state(STATE_ESTOP);
    rgb_run_next();
    for (unsigned i = 0; i < 12; i++)
        CHECK(pixels[0][i].value == 0);
    CHECK(pixels[0][12].R == 255 && pixels[0][12].G == 0);
    rgb_run_next();
    rgb_expect(0, 255, 0, 0);
    CHECK(rgb_command(0, 3, 255, true) == Status_OK);
    while (pending)
        rgb_run_next();
    for (unsigned i = 0; i < 12; i++)
        CHECK(pixels[0][i].G == 255 && pixels[0][i].R == 0 && pixels[0][i].B == 0);
    CHECK(rgb_command(0, 0, 255, true) == Status_OK && pending);
    rgb_run_next();
    for (unsigned i = 0; i < 12; i++)
        CHECK(pixels[0][i].value == 0);
    rgb_state(STATE_IDLE);
    while (pending)
        rgb_run_next();
    rgb_expect(0, 255, 255, 255);
    return 0;
}
