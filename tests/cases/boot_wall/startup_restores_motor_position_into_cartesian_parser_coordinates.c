#include "support/boot_host.h"
int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[0] = 10000;
    boot_hardware_position[1] = 10000;
    boot_hardware_position[2] = 240;
    CHECK(grbl_enter() == 0);
    CHECK(boot_position_calls == 1 && sys.driver_started);
    NEAR(gc_state.position[0], 100);
    NEAR(gc_state.position[1], 75);
    NEAR(gc_state.position[2], 3);
    return EXIT_SUCCESS;
}
