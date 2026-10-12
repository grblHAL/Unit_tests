#include "support/motion_program_host.h"
#include "check.h"
static int32_t maximum_x;
static void tracked_pulse(stepper_t *stepper) { pulse_driver(stepper); if(physical_position[X_AXIS] > maximum_x) maximum_x = physical_position[X_AXIS]; }
int main(void)
{
    prepare_motion_program();
    hal.stepper.pulse_start = tracked_pulse;
    coord_system_data_t home = {.coord.x = -10};
    settings_write_coord_data(CoordinateSystem_G28, &home);
    queue_motion_program("G28X5");
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == -800);
    CHECK(axis_pulses[X_AXIS] == 1600);
    CHECK(maximum_x == 400);
    CHECK(physical_position[Y_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
