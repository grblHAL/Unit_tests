#include "support/boot_stream_motion_host.h"
int main(void)
{
    char program[128];
    snprintf(program, sizeof(program), "$%u=3\nM852\nM851\nG91G1X0.25Y0.5Z0.125F100\n",
        (unsigned)Settings_RotaryAxes);
    boot_motion_physical_nvs = true;
    prepare_boot_stream_motion(program);
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    const int32_t expected[N_AXIS] = {20, 40, 10, 0, 0};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == expected[axis]);
        CHECK(boot_motor_position[axis] == expected[axis]);
    }
    return EXIT_SUCCESS;
}
