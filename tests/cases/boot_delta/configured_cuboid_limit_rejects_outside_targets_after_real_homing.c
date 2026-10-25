#include "support/boot_delta_homing_host.h"
static void configure_cuboid_limit(settings_t *current)
{
    configure_delta_homing(current);
    char flags[] = "2";
    CHECK(settings_store_setting(Setting_Kinematics7, flags) == Status_OK);
}
int main(void)
{
    prepare_boot_delta_homing(false);
    boot_during_setup = configure_cuboid_limit;
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && sys.homed.mask == AXES_BITMASK);
    int32_t before[N_AXIS];
    unsigned pulses[N_AXIS];
    memcpy(before, sys.position, sizeof(before));
    memcpy(pulses, boot_motor_pulses, sizeof(pulses));
    float target[N_AXIS] = {0};
    target[Z_AXIS] = (sys.work_envelope.min.z + sys.work_envelope.max.z) * .5f;
    CHECK(grbl.check_travel_limits(target, (axes_signals_t){.mask = AXES_BITMASK}, true, &sys.work_envelope));
    target[X_AXIS] = sys.work_envelope.max.x + 1;
    CHECK(!grbl.check_travel_limits(target, (axes_signals_t){.mask = AXES_BITMASK}, true, &sys.work_envelope));
    target[X_AXIS] = 0;
    target[Y_AXIS] = sys.work_envelope.min.y - 1;
    CHECK(!grbl.check_travel_limits(target, (axes_signals_t){.mask = AXES_BITMASK}, true, &sys.work_envelope));
    target[Y_AXIS] = 0;
    CHECK(grbl.check_travel_limits(target, (axes_signals_t){.mask = AXES_BITMASK}, true, &sys.work_envelope));
    CHECK(memcmp(before, sys.position, sizeof(before)) == 0);
    CHECK(memcmp(pulses, boot_motor_pulses, sizeof(pulses)) == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
