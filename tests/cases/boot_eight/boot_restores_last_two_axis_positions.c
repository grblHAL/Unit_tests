#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    CHECK(N_AXIS == 8);
    boot_restore_position = true;
    boot_hardware_position[U_AXIS] = 400;
    boot_hardware_position[V_AXIS] = -160;
    CHECK(grbl_enter() == 0);
    CHECK(sys.driver_started && boot_position_calls == 1);
    NEAR(gc_state.position[U_AXIS], 5);
    NEAR(gc_state.position[V_AXIS], -2);
    return EXIT_SUCCESS;
}
