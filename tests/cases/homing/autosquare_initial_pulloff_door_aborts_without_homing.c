#include "support/autosquare_homing_host.h"

int main(void)
{
    prepare_autosquare_homing();
    squared_primary = 80; squared_secondary = 120;
    interrupt_request = EXEC_SAFETY_DOOR;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_Unhandled);
    CHECK(sys.alarm == Alarm_HomingFailDoor);
    CHECK(sys.homed.mask == 0);
    CHECK(reset_calls == 1 && !homing_success);
    return EXIT_SUCCESS;
}
