#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_homing_required = true;
    boot_program = "$X\nG20\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.alarm == Alarm_HomingRequired);
    CHECK(!gc_state.modal.units_imperial);
    char expected[32];
    snprintf(expected, sizeof(expected), "error:%u", (unsigned)Status_HomingRequired);
    CHECK(strstr(engine_output, expected) != NULL);
    return EXIT_SUCCESS;
}
