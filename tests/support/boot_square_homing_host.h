#pragma once
#include "support/boot_homing_motion_host.h"
static unsigned engaged_reads;
static bool start_on_switches;
static float square_trim;
static bool reset_during_trim, trim_reset_sent;
static void square_foreground(sys_state_t state)
{
    if(reset_during_trim && !trim_reset_sent && boot_wake_calls >= 5 && boot_homing_timer_running) {
        trim_reset_sent = true;
        protocol_enqueue_realtime_command(CMD_RESET);
    }
    boot_homing_foreground(state);
}
static home_signals_t square_switches(void)
{
    home_signals_t state = {0};
    state.a.y = boot_motor_position[Y_AXIS] >= 120;
    state.a.a = state.b.y = boot_motor_position[A_AXIS] >= 200;
    if(state.a.y && state.b.y) engaged_reads++;
    return state;
}
static void install_square_driver(void)
{
    install_boot_homing_driver();
    settings.homing.pulloff = .5f;
    settings.axis[Y_AXIS].dual_axis_offset = square_trim;
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].steps_per_mm = 80;
    settings.homing.cycle[0].mask = (1u << Y_AXIS) | (1u << A_AXIS);
    settings.homing.dual_axis.fail_length_percent = 20;
    settings.homing.dual_axis.fail_distance_min = 2;
    settings.homing.dual_axis.fail_distance_max = 5;
    settings_write_global();
    boot_motor_position[Y_AXIS] = start_on_switches ? 120 : 0;
    boot_motor_position[A_AXIS] = start_on_switches ? 200 : 0;
    hal.homing.get_state = square_switches;
    hal.home_cap.a.mask = (1u << Y_AXIS) | (1u << A_AXIS);
    hal.home_cap.b.y = On;
    grbl.on_execute_delay = square_foreground;
}
static void check_square_homing(bool engaged)
{
    start_on_switches = engaged;
    prepare_boot_homing_motion();
    boot_during_init = install_square_driver;
    boot_on_realtime = square_foreground;
    boot_program = "$H\n";
    CHECK(grbl_enter() == 0);
    if(reset_during_trim) {
        CHECK(trim_reset_sent);
        CHECK(strstr(engine_output, "ALARM:6") != NULL);
        CHECK(!sys.homed.y && !sys.homed.a);
        CHECK(boot_motor_position[Y_AXIS] == 80);
        CHECK(boot_motor_position[A_AXIS] <= 160 && boot_motor_position[A_AXIS] >= 140);
        CHECK(boot_motor_pulses[X_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
        CHECK(plan_get_current_block() == NULL);
        return;
    }
    CHECK(engaged_reads > 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "ALARM:8") == NULL);
    CHECK(sys.homed.y && sys.homed.a);
    CHECK(boot_motor_position[Y_AXIS] == 80 - (square_trim < 0 ? 20 : 0));
    CHECK(boot_motor_position[A_AXIS] == 160 - (square_trim > 0 ? 20 : 0));
    CHECK(boot_motor_pulses[Y_AXIS] > 80);
    CHECK(boot_motor_pulses[A_AXIS] > 80);
    CHECK(boot_motor_pulses[X_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
    CHECK(!square_switches().a.y && !square_switches().b.y);
    CHECK(plan_get_current_block() == NULL);

}

