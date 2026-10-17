#include "support/boot_delta_homing_host.h"
static void configure_forearm(settings_t *current)
{
    configure_delta_homing(current);
    char length[] = "330";
    CHECK(settings_store_setting(Setting_Kinematics1, length) == Status_OK);
}
int main(void)
{
    prepare_boot_delta_homing(false);
    boot_during_setup = configure_forearm;
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && boot_delta_home_events == 1);
    CHECK(sys.homed.mask == AXES_BITMASK);
    float radial = 100 + (75 - 24) / (2 * sqrtf(3));
    float expected_home = -sqrtf(330 * 330 - radial * radial) - 1;
    CHECK(fabsf(sys.home_position[Z_AXIS] - expected_home) < .01f);
    NEAR(sys.home_position[X_AXIS], 0);
    NEAR(sys.home_position[Y_AXIS], 0);
    for(unsigned axis = 0; axis < 3; axis++) CHECK(boot_motor_pulses[axis] > 80);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
