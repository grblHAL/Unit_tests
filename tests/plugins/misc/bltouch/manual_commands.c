#include "bltouch_host.h"
int main(void)
{
    load_bltouch();
    CHECK(hal.driver_cap.bltouch_probe && angle == 90 && outputs == 1);
    NEAR(last_delay, 0.75f);
    command_bltouch(Probe_Deploy);
    CHECK(angle == 10 && outputs == 2);
    NEAR(last_delay, 0.75f);
    unsigned before = delays;
    command_bltouch(Probe_Deploy);
    CHECK(outputs == 2 && delays == before);
    command_bltouch(Probe_Stow);
    CHECK(angle == 90 && outputs == 3);
    return 0;
}
