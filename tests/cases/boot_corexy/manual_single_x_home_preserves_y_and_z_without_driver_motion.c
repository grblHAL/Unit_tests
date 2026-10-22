#include "support/corexy_manual_homing_boot_host.h"

int main(void)
{
    prepare_manual_corexy_reference("$HX\n$G\n");
    CHECK(grbl_enter() == 0);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(sys.position[0] == 400 && sys.position[1] == -400 && sys.position[2] == 80);
    NEAR(gc_state.position[X_AXIS], 0);
    NEAR(gc_state.position[Y_AXIS], 5);
    NEAR(gc_state.position[Z_AXIS], 1);
    CHECK(boot_position_calls == 1 && boot_release_calls == 1);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
