#include "support/motion_program_host.h"
#include "check.h"
static int32_t maximum_x, minimum_y;
static void tracked_pulse(stepper_t *stepper) { pulse_driver(stepper); if(physical_position[X_AXIS] > maximum_x) maximum_x = physical_position[X_AXIS]; if(physical_position[Y_AXIS] < minimum_y) minimum_y = physical_position[Y_AXIS]; }
int main(void)
{
    prepare_motion_program();
    hal.stepper.pulse_start = tracked_pulse;
    queue_motion_program("G0X-1");
    char scale[] = "G51X-1";
    CHECK(gc_execute_block(scale) == Status_OK);
    queue_motion_program("G3X0Y1I-1J0F100");
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 0);
    CHECK(physical_position[Y_AXIS] == 80);
    CHECK(maximum_x == 0);
    CHECK(minimum_y == 0);
    return EXIT_SUCCESS;
}
