#include "support/boot_delta_homing_host.h"
static float original_bottom;
static void configure_motor_travel(settings_t *current)
{
    configure_delta_homing(current);
    original_bottom = sys.work_envelope.min.z;
    char angle[] = "30";
    CHECK(settings_store_setting(Setting_Kinematics8, angle) == Status_OK);
}
int main(void)
{
    prepare_boot_delta_homing(false);
    boot_during_setup = configure_motor_travel;
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && boot_delta_home_events == 1);
    CHECK(isfinite(sys.work_envelope.min.z) && isfinite(sys.work_envelope.max.z));
    CHECK(sys.work_envelope.min.z > original_bottom);
    CHECK(sys.work_envelope.min.z < sys.work_envelope.max.z);
    NEAR(sys.home_position[X_AXIS], 0);
    NEAR(sys.home_position[Y_AXIS], 0);
    CHECK(fabsf(sys.home_position[Z_AXIS] - (delta_zero_angle_height() - 1)) < .01f);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
