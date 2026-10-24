#include "support/boot_delta_manual_a_host.h"
int main(void)
{
    prepare_delta_manual_a("$G\n", 4);
    CHECK(grbl_enter() == 0);
    CHECK(manual_a_finished && manual_a_homing_events == 2 && sys.homed.mask == AXES_BITMASK);
    CHECK(strstr(engine_output, "error:") == NULL && strstr(engine_output, "[GC:") != NULL);
    for(unsigned axis = 0; axis < 3; axis++) {
        CHECK(boot_motor_pulses[axis] == pulses_after_xyz_home[axis]);
        fprintf(stderr, "Manual A home: joint%u before=%ld after=%ld\n", axis,
            (long)position_after_xyz_home[axis], (long)position_after_manual_a[axis]);
    }
    CHECK(boot_motion_ack_count() == manual_a_expected_acks);
    CHECK(boot_motor_pulses[A_AXIS] == 0 && sys.position[A_AXIS] == 0);
    CHECK(memcmp(position_after_xyz_home, position_after_manual_a, 3 * sizeof(int32_t)) == 0);
    return EXIT_SUCCESS;
}
