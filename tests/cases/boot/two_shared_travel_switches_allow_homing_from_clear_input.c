#include "support/boot_homing_motion_host.h"

static unsigned shared_limit_reads;
static limit_signals_t shared_travel_switches(void)
{
    shared_limit_reads++;
    home_signals_t home = boot_homing_switches();
    return (limit_signals_t){.min.mask = home.a.mask};
}
static void install_shared_travel_switches(void)
{
    install_boot_homing_driver();
    settings.limits.flags.two_switches = true;
    settings_write_global();
    hal.home_cap.a.mask = 0;
    hal.homing.get_state = NULL; /* CORE derives homing signals from the shared limit input. */
    hal.limits_cap.min.mask = AXES_BITMASK;
    hal.limits.get_state = shared_travel_switches;
}

int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_shared_travel_switches;
    CHECK(grbl_enter() == 0);
    CHECK(shared_limit_reads > 0);
    CHECK(sys.homed.mask == X_AXIS_BIT);
    CHECK(boot_motor_pulses[X_AXIS] == 110);
    CHECK(boot_motor_position[X_AXIS] == 70);
    CHECK(sys.position[X_AXIS] == -10);
    NEAR(gc_state.position[X_AXIS], -.125f);
    CHECK(!limit_signals_merge(hal.limits.get_state()).value);
    for(unsigned axis = 1; axis < N_AXIS; axis++)
        CHECK(boot_motor_pulses[axis] == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "ALARM:1\r\n") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
