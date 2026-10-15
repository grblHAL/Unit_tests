#include "support/boot_homing_motion_host.h"
int main(void)
{
    prepare_boot_homing_motion();
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(boot_motor_pulses[X_AXIS] == 110);
    CHECK(boot_motor_position[X_AXIS] == 70);
    CHECK(sys.position[X_AXIS] == -10);
    NEAR(gc_state.position[X_AXIS], -.125f);
    for(unsigned axis = 1; axis < N_AXIS; axis++) CHECK(boot_motor_pulses[axis] == 0);
    CHECK(strstr(engine_output, "ALARM:18") == NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
