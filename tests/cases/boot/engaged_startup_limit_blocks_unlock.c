#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_check_limits = true;
    boot_limit_signals.min.mask = X_AXIS_BIT;
    boot_program = "$X\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.alarm == Alarm_LimitsEngaged);
    char expected[32];
    snprintf(expected, sizeof(expected), "error:%u", (unsigned)Status_LimitsEngaged);
    CHECK(strstr(engine_output, expected) != NULL);
    return EXIT_SUCCESS;
}
