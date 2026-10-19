#pragma once
#include "support/boot_homing_motion_host.h"
static bool corexy_homing_alarm_seen;
static void configure_corexy_homing(settings_t *current)
{
    CHECK(current == &settings);
    char combined[] = "3", none[] = "0";
    CHECK(settings_store_setting(Setting_HomingCycle_1, combined) == Status_OK);
    CHECK(settings_store_setting(Setting_HomingCycle_2, none) == Status_OK);
    CHECK(settings_store_setting(Setting_HomingCycle_3, none) == Status_OK);
}
static void observe_corexy_homing_alarm(sys_state_t state)
{
    CHECK(++boot_homing_service_calls < 10000);
    if(state == STATE_ALARM && sys.alarm == Alarm_HomingFail) {
        corexy_homing_alarm_seen = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_on_realtime = NULL;
    }
}
static inline void run_corexy_homing_rejection(void)
{
    prepare_boot_homing_motion();
    boot_during_setup = configure_corexy_homing;
    boot_on_realtime = observe_corexy_homing_alarm;
    boot_observe_fault_loop = true;
    boot_program = "$H\n";
    CHECK(grbl_enter() == 0);
    CHECK(corexy_homing_alarm_seen);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(boot_wake_calls == 0);
    CHECK(sys.homed.mask == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(boot_motor_pulses[axis] == 0);
    CHECK(strstr(engine_output, "ALARM:") != NULL);
}
