#include "rgb_host.h"
int main(void)
{
    rgb_start();
    bus_busy = true;
    unsigned before = counts[0];
    rgb_state(STATE_ALARM);
    rgb_run_next();
    CHECK(counts[0] == before && last_delay == 80);
    bus_busy = false;
    rgb_run_next();
    CHECK(counts[0] > before && last_delay == 60 && pixels[0][12].R == 255);
    rgb_state(STATE_IDLE);
    while (pending)
        rgb_run_next();
    CHECK(!pending);
    return 0;
}
