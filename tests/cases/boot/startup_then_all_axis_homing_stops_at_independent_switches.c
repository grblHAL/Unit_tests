#include "support/boot_homing_motion_host.h"
int main(void)
{
    prepare_boot_homing_motion();
    boot_program = "$H\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == AXES_BITMASK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(boot_motor_position[axis] == 70 + (int32_t)axis * 40);
        CHECK(boot_motor_pulses[axis] == 110 + axis * 40);
        CHECK(sys.position[axis] == -10);
        NEAR(gc_state.position[axis], -.125f);
    }
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
