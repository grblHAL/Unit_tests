#include "support/boot_host.h"
#include "check.h"

static void omit_uninitialized_step_enable(void) { hal.stepper.enable = NULL; }

int main(void)
{
    boot_program = "";
    boot_during_init = omit_uninitialized_step_enable;
    boot_init_success = false;
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 0 && boot_release_calls == 1);
    CHECK(!sys.driver_started);
    CHECK(sys.alarm == Alarm_SelftestFailed);
    CHECK(boot_enabled_axes.mask == 0);
    return EXIT_SUCCESS;
}
