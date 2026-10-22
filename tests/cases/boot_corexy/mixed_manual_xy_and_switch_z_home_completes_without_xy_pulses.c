#include "support/boot_corexy_switch_homing_host.h"

static void configure_mixed_reference(settings_t *current)
{
    CHECK(current == &settings);
    char options[] = "43";
    CHECK(settings_store_setting(Setting_HomingEnable, options) == Status_OK);
    for(unsigned slot = 0; slot < N_AXIS; slot++) {
        char mask[] = {slot == 0 ? '4' : '0', '\0'};
        CHECK(settings_store_setting((setting_id_t)(Setting_HomingCycle_1 + slot), mask) == Status_OK);
    }
    CHECK(sys.homing.mask == Z_AXIS_BIT);
}

int main(void)
{
    prepare_boot_homing_motion();
    boot_during_init = install_corexy_homing_driver;
    boot_during_setup = configure_mixed_reference;
    boot_on_realtime = finish_corexy_home;
    boot_observe_fault_loop = true;
    boot_read_limit = 100000;
    boot_program = "$H\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(corexy_home_finished && sys.homed.mask == AXES_BITMASK);
    CHECK(boot_motor_pulses[0] == 0 && boot_motor_pulses[1] == 0);
    CHECK(boot_motor_pulses[2] > 0 && boot_wake_calls > 0);
    CHECK(corexy_switches().a.mask == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == 0);
        NEAR(gc_state.position[axis], 0);
    }
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
