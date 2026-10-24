#include "support/boot_delta_manual_a_host.h"
int main(void)
{
    prepare_delta_manual_a("$20=1\n$J=G91A999F100\n$J=G91A-1F100\n$G\n", 6);
    CHECK(grbl_enter() == 0);
    CHECK(manual_a_finished && manual_a_homing_events == 2 && sys.homed.mask == AXES_BITMASK);
    CHECK(sys.soft_limits.mask & A_AXIS_BIT);
    char expected[32];
    snprintf(expected, sizeof(expected), "error:%u" ASCII_EOL, (unsigned)Status_TravelExceeded);
    CHECK(strstr(engine_output, expected) != NULL && strstr(engine_output, "[GC:") != NULL);
    fprintf(stderr, "Manual A legal retry: acks=%u expected=%u position=%ld pulses=%u\n",
        boot_motion_ack_count(), manual_a_expected_acks, (long)sys.position[A_AXIS], boot_motor_pulses[A_AXIS]);
    CHECK(boot_motion_ack_count() == manual_a_expected_acks);
    CHECK(boot_motor_position[A_AXIS] == -80 && sys.position[A_AXIS] == -80);
    CHECK(boot_motor_pulses[A_AXIS] == 80 && plan_get_current_block() == NULL);
    NEAR(gc_state.position[A_AXIS], -1);
    /* The companion regression independently checks manual-home XYZ references. */
    for(unsigned axis = 0; axis < 3; axis++) {
        CHECK(boot_motor_pulses[axis] == pulses_after_xyz_home[axis]);
        CHECK(sys.position[axis] == position_after_manual_a[axis]);
    }
    return EXIT_SUCCESS;
}
