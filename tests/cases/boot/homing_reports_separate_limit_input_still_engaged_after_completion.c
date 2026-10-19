#include "support/boot_homing_motion_host.h"
static bool asserted_limit;
static unsigned completion_calls;
static void record_home_completion(axes_signals_t cycle, bool success)
{
    CHECK(cycle.mask == X_AXIS_BIT && !success);
    completion_calls++;
}
static void install_homing_with_separate_limits(void)
{
    install_boot_homing_driver();
    hal.limits_cap.min.mask = AXES_BITMASK;
    settings.limits.flags.hard_enabled = true;
    settings.limits.flags.check_at_init = true;
    settings_write_global();
    grbl.on_homing_completed = record_home_completion;
}
static void assert_separate_limit_during_homing(sys_state_t state)
{
    boot_homing_foreground(state);
    if(state == STATE_HOMING && boot_motor_pulses[X_AXIS] >= 80) {
        boot_limit_signals.min.x = true;
        asserted_limit = true;
    }
}
int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_homing_with_separate_limits;
    boot_on_realtime = assert_separate_limit_during_homing;
    CHECK(grbl_enter() == 0);
    CHECK(asserted_limit && boot_limit_signals.min.x);
    CHECK(completion_calls == 1);
    CHECK(boot_motor_pulses[X_AXIS] == 110 && boot_motor_position[X_AXIS] == 70);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    CHECK(strstr(engine_output, "error:45") != NULL);
    return EXIT_SUCCESS;
}
