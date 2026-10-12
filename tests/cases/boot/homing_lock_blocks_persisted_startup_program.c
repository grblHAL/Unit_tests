#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_homing_required = true;
    boot_startup_program = "G20";
    CHECK(grbl_enter() == 0);
    CHECK(sys.alarm == Alarm_HomingRequired);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(strstr(engine_output, "ALARM:11") != NULL);
    CHECK(strstr(engine_output, "Homing cycle required") != NULL);
    return EXIT_SUCCESS;
}
