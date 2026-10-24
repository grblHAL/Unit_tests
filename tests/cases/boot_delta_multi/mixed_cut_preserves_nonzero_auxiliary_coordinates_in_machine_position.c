#include "support/boot_delta_stream_motion_host.h"
#include "check.h"

int main(void)
{
    CHECK(N_AXIS == 5);
    prepare_boot_delta_stream_motion("G91G1Z-0.5A1B-0.5F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    for(unsigned motor = 0; motor < 3; motor++) {
        CHECK(sys.position[motor] == 5 && boot_motor_position[motor] == 5);
        CHECK(boot_motor_pulses[motor] == 5);
    }
    CHECK(sys.position[A_AXIS] == 80 && boot_motor_position[A_AXIS] == 80);
    CHECK(sys.position[B_AXIS] == -40 && boot_motor_position[B_AXIS] == -40);
    CHECK(boot_motor_pulses[A_AXIS] == 80 && boot_motor_pulses[B_AXIS] == 40);
    NEAR(gc_state.position[A_AXIS], 1);
    NEAR(gc_state.position[B_AXIS], -.5f);
    coord_data_t actual;
    system_convert_array_steps_to_mpos(actual.values, sys.position);
    NEAR(actual.values[A_AXIS], 1);
    NEAR(actual.values[B_AXIS], -.5f);
    CHECK(fabsf(actual.x) < .03f && fabsf(actual.y) < .03f);
    CHECK(fabsf(actual.z - (delta_zero_angle_height() - .5f)) < .03f);
    return EXIT_SUCCESS;
}
