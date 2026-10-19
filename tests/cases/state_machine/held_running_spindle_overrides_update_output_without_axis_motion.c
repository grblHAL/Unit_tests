#include "support/held_running_spindle_override_host.h"
int main(void)
{
    start_registered_running_hold();
    CHECK(!settings.flags.set_rpm_0_during_hold);
    change_held_running_spindle(CMD_OVERRIDE_SPINDLE_COARSE_PLUS, 110, 550);
    change_held_running_spindle(CMD_OVERRIDE_SPINDLE_COARSE_MINUS, 100, 500);
    change_held_running_spindle(CMD_OVERRIDE_SPINDLE_FINE_PLUS, 101, 505);
    change_held_running_spindle(CMD_OVERRIDE_SPINDLE_FINE_MINUS, 100, 500);
    change_held_running_spindle(CMD_OVERRIDE_SPINDLE_COARSE_MINUS, 90, 450);
    change_held_running_spindle(CMD_OVERRIDE_SPINDLE_RESET, 100, 500);
    finish_registered_running_hold();
    return EXIT_SUCCESS;
}
