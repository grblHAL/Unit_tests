#include "support/boot_host.h"
static void advertise_driver_door(void)
{
    hal.signals_cap.safety_door_ajar = true;
}
int main(void)
{
    boot_during_init = advertise_driver_door;
    boot_program = "$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(!hal.signals_cap.safety_door_ajar);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    return EXIT_SUCCESS;
}
