#include "support/boot_homing_motion_host.h"
int main(void)
{
    prepare_boot_homing_motion();
    boot_startup_program = "G91";
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(boot_motor_pulses[X_AXIS] == 110);
    for(unsigned axis = 1; axis < N_AXIS; axis++) CHECK(boot_motor_pulses[axis] == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
