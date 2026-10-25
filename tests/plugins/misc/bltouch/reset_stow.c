#include "bltouch_host.h"
int main(void)
{
    load_bltouch();
    command_bltouch(Probe_Deploy);
    hal.driver_reset();
    CHECK(resets == 1 && angle == 10);
    run_bltouch_immediate();
    CHECK(angle == 90 && outputs == 3);
    return 0;
}
