#include "support/boot_delta_homing_host.h"
static float previous_bottom;
static void configure_floor(settings_t *current)
{
    configure_delta_homing(current);
    previous_bottom = sys.work_envelope.min.z;
    char height[] = "350";
    CHECK(settings_store_setting(Setting_Kinematics5, height) == Status_OK);
}
int main(void)
{
    prepare_boot_delta_homing(false);
    boot_during_setup = configure_floor;
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && sys.homed.mask == AXES_BITMASK);
    CHECK(sys.work_envelope.min.z >= -350.01f);
    CHECK(sys.work_envelope.min.z > previous_bottom);
    CHECK(sys.work_envelope.max.z > sys.work_envelope.min.z);
    CHECK(fabsf(sys.home_position[Z_AXIS] - (delta_zero_angle_height() - 1)) < .01f);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
