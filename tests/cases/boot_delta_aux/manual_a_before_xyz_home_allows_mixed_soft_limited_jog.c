#include "support/boot_delta_manual_first_host.h"
int main(void)
{
    prepare_delta_manual_first("$20=1\n$J=G90Z-300F100\n$J=G90X100A-1F100\n$G\n", 8);
    CHECK(grbl_enter() == 0);
    CHECK(manual_a_finished && manual_a_homing_events == 2 && sys.homed.mask == AXES_BITMASK);
    fprintf(stderr, "Manual-first mixed jog: acks=%u A=%ld output=%s\n",
        boot_motion_ack_count(), (long)sys.position[A_AXIS], engine_output);
    CHECK(boot_motion_ack_count() == 8 && strstr(engine_output, "error:") == NULL);
    CHECK(sys.position[A_AXIS] == -80 && boot_motor_position[A_AXIS] == -80 && boot_motor_pulses[A_AXIS] == 80);
    mpos_t joint_steps;
    coord_data_t actual;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        joint_steps.values[axis] = boot_motor_position[axis] - manual_first_physical_zero[axis];
        CHECK(joint_steps.values[axis] == sys.position[axis]);
    }
    fprintf(stderr, "Mixed jog final X=100, cuboid max X=%g\n", (double)sys.work_envelope.max.x);
    kinematics.transform_steps_to_cartesian(&actual, &joint_steps);
    CHECK(fabsf(actual.x - 100) < .5f && fabsf(actual.y) < .5f && fabsf(actual.z + 300) < .5f);
    NEAR(gc_state.position[A_AXIS], -1);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
