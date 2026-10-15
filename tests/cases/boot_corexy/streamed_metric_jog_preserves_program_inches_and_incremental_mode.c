#include "support/boot_stream_motion_host.h"
int main(void)
{
    boot_startup_program = "G20G91";
    prepare_boot_stream_motion("$J=G21G91X0.5Y0.25F100\n");
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(sys.position[0] == 60 && sys.position[1] == 20);
    CHECK(boot_motor_position[0] == 60 && boot_motor_position[1] == 20);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    NEAR(gc_state.position[0], .5f);
    NEAR(gc_state.position[1], .25f);
    return EXIT_SUCCESS;
}
