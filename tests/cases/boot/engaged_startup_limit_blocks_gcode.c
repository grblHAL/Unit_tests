#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_check_limits = true;
    boot_limit_signals.min.mask = X_AXIS_BIT;
    boot_program = "G20\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.alarm == Alarm_LimitsEngaged);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(strstr(engine_output, "ALARM:12") != NULL);
    return EXIT_SUCCESS;
}
