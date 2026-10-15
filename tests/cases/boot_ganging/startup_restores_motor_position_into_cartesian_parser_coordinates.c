#include "support/boot_host.h"
int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[0] = 160;
    boot_hardware_position[1] = -240;
    boot_hardware_position[2] = 320;
    boot_hardware_position[3] = -240;
    CHECK(grbl_enter() == 0);
    CHECK(boot_position_calls == 1 && sys.driver_started);
    NEAR(gc_state.position[0], 2);
    NEAR(gc_state.position[1], -3);
    NEAR(gc_state.position[2], 4);
    NEAR(gc_state.position[3], -3);
    return EXIT_SUCCESS;
}
