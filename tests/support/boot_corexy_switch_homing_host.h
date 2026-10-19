#pragma once
#include "support/boot_stream_motion_host.h"
static bool corexy_home_finished, corexy_single_home;
static home_signals_t corexy_switches(void)
{
    home_signals_t signals = {0};
    /* A = X + Y, B = X - Y: switches sense carriage travel, not motor rotation. */
    if(boot_motor_position[0] + boot_motor_position[1] >= 160) signals.a.x = On;
    if(boot_motor_position[0] - boot_motor_position[1] >= 240) signals.a.y = On;
    if(boot_motor_position[2] >= 160) signals.a.z = On;
    return signals;
}
static void install_corexy_homing_driver(void)
{
    install_boot_homing_driver();
    hal.homing.get_state = corexy_switches;
}
static void configure_separate_cycles(settings_t *current)
{
    CHECK(current == &settings);
    char x[] = "1", y[] = "2", z[] = "4";
    CHECK(settings_store_setting(Setting_HomingCycle_1, z) == Status_OK);
    CHECK(settings_store_setting(Setting_HomingCycle_2, x) == Status_OK);
    CHECK(settings_store_setting(Setting_HomingCycle_3, y) == Status_OK);
}
static void finish_corexy_home(sys_state_t state)
{
    boot_homing_foreground(state);
    if(boot_reads == strlen(boot_program) && boot_motion_ack_count() == 2 &&
       (corexy_single_home ? state == STATE_ALARM && sys.alarm == Alarm_HomingRequired : state == STATE_IDLE) && !plan_get_current_block()) {
        corexy_home_finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
        boot_on_realtime = NULL;
    }
}
static inline void run_corexy_switch_homing(bool single)
{
    corexy_single_home = single;
    prepare_boot_homing_motion();
    boot_during_init = install_corexy_homing_driver;
    boot_during_setup = configure_separate_cycles;
    boot_on_realtime = finish_corexy_home;
    boot_observe_fault_loop = true;
    boot_read_limit = 100000;
    boot_program = single ? "$HX\n$G\n" : "$H\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(corexy_home_finished && sys.homed.mask == (single ? X_AXIS_BIT : AXES_BITMASK));
    CHECK(boot_wake_calls >= (single ? 1u : 3u));
    CHECK(corexy_switches().a.mask == 0);
    CHECK(boot_motor_pulses[0] > 0 && boot_motor_pulses[1] > 0);
    CHECK(single ? boot_motor_pulses[2] == 0 : boot_motor_pulses[2] > 0);
    float motor_a = sys.position[0] / settings.axis[0].steps_per_mm;
    float motor_b = sys.position[1] / settings.axis[1].steps_per_mm;
    NEAR(gc_state.position[X_AXIS], (motor_a + motor_b) * .5f);
    NEAR(gc_state.position[Y_AXIS], (motor_a - motor_b) * .5f);
    NEAR(gc_state.position[Z_AXIS], sys.position[2] / settings.axis[2].steps_per_mm);
    CHECK(strstr(engine_output, "error:") == NULL);
    /* Initial homing-required startup alarm is expected before $H. */
    CHECK(state_get() == (single ? STATE_ALARM : STATE_IDLE));
}
