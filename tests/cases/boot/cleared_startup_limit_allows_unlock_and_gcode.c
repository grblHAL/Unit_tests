#include "support/boot_host.h"
#include "check.h"
static unsigned clear_calls;
static void clear_limit(void) { CHECK(sys.alarm == Alarm_LimitsEngaged); boot_limit_signals.min.mask = 0; clear_calls++; boot_before_read = NULL; }
int main(void)
{
    boot_check_limits = true;
    boot_limit_signals.min.mask = X_AXIS_BIT;
    boot_before_read = clear_limit;
    boot_program = "$X\nG20\n";
    CHECK(grbl_enter() == 0);
    CHECK(clear_calls == 1);
    CHECK(sys.alarm == Alarm_None && gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
