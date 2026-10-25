#include "support/motion_program_host.h"

static int32_t minimum_position[N_AXIS];
static void observe_uvw_pulse(stepper_t *stepper)
{
    pulse_driver(stepper);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(physical_position[axis] < minimum_position[axis])
            minimum_position[axis] = physical_position[axis];
}
int main(void)
{
    prepare_motion_program();
    hal.stepper.pulse_start = observe_uvw_pulse;
    char block[] = "G1U1V2W3F100";
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(N_AXIS == 6);
    NEAR(gc_state.position[3], 1);
    NEAR(gc_state.position[4], 2);
    NEAR(gc_state.position[5], 3);
    CHECK(gc_state.position[X_AXIS] == 0);
    queue_motion_program("G91G1U-2V-4W-6");
    queue_motion_program("G1U1V2W3");
    execute_motion_program();
    const unsigned expected_pulses[N_AXIS] = {0, 0, 0, 320, 640, 960};
    const int32_t expected_minimum[N_AXIS] = {0, 0, 0, -80, -160, -240};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(axis_pulses[axis] == expected_pulses[axis]);
        CHECK(minimum_position[axis] == expected_minimum[axis]);
        CHECK(physical_position[axis] == 0 && sys.position[axis] == 0);
        NEAR(gc_state.position[axis], 0);
    }
    return EXIT_SUCCESS;
}
