#include "support/boot_delta_homing_host.h"
static void configure_angled_home(settings_t *current)
{
    configure_delta_homing(current);
    char angle[] = "30";
    CHECK(settings_store_setting(Setting_Kinematics6, angle) == Status_OK);
}
int main(void)
{
    prepare_boot_delta_homing(false);
    boot_during_setup = configure_angled_home;
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && boot_delta_home_events == 1);
    CHECK(sys.homed.mask == AXES_BITMASK);
    /* Symmetric linkage geometry at 30 degrees, then the configured 1 mm pull-off. */
    float radial = 100 * cosf((float)M_PI / 6) + (75 - 24) / (2 * sqrtf(3));
    float height = -100 * sinf((float)M_PI / 6) - sqrtf(300 * 300 - radial * radial);
    CHECK(fabsf(sys.home_position[Z_AXIS] - (height - 1)) < .01f);
    NEAR(sys.home_position[X_AXIS], 0);
    NEAR(sys.home_position[Y_AXIS], 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    for(unsigned axis = 0; axis < 3; axis++) CHECK(boot_motor_pulses[axis] > 80);
    return EXIT_SUCCESS;
}
