#include "support/corexy_manual_homing_boot_host.h"

int main(void)
{
    prepare_manual_corexy_reference("$H\n$G\n");
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == AXES_BITMASK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == 0);
        NEAR(gc_state.position[axis], 0);
    }
    CHECK(boot_position_calls == 1 && boot_release_calls == 1);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
