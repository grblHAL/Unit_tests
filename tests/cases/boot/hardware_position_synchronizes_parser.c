#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_restore_position = true;
    boot_hardware_position[X_AXIS] = 800;
    boot_hardware_position[Y_AXIS] = -160;
    CHECK(grbl_enter() == 0);
    CHECK(boot_position_calls == 1);
    CHECK(sys.position[X_AXIS] == 800 && sys.position[Y_AXIS] == -160);
    NEAR(gc_state.position[X_AXIS], 10);
    NEAR(gc_state.position[Y_AXIS], -2);
    return EXIT_SUCCESS;
}
