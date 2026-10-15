#include "support/boot_homing_motion_host.h"
int main(void)
{
    prepare_boot_homing_motion();
    boot_startup_program = "G91";
    boot_program = "$H\n";
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == AXES_BITMASK);
    CHECK(gc_state.modal.distance_incremental);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(boot_motor_pulses[axis] == 110 + axis * 40);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
