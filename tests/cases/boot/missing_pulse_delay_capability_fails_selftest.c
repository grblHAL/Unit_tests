#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_program = "";
    boot_pulse_delay_capability = false;
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 0 && boot_release_calls == 1);
    CHECK(!sys.driver_started && sys.alarm == Alarm_SelftestFailed);
    return EXIT_SUCCESS;
}
