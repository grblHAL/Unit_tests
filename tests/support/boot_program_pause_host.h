#pragma once
#include "support/boot_stream_motion_host.h"
static char pause_stream_program[128];
static unsigned pause_hold_visits;
static bool pause_resume_queued;
static bool pause_single_block, pause_use_pallet;
static unsigned pause_pallet_calls;
static void pause_pallet_shuttle(void)
{
    CHECK(boot_motor_position[X_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 80);
    CHECK(!pause_resume_queued);
    pause_pallet_calls++;
}
static void pause_switch_capability(settings_t *current)
{
    CHECK(current == &settings);
    hal.signals_cap.stop_disable = true;
    hal.signals_cap.single_block = true;
    if(pause_use_pallet) hal.pallet_shuttle = pause_pallet_shuttle;
}
static void pause_motion_service(sys_state_t state)
{
    boot_motion_foreground(state);
    if(state == STATE_HOLD && sys.holding_state == Hold_Pending)
        stepper_driver_interrupt_handler();
    if(state == STATE_HOLD && sys.holding_state == Hold_Complete && !pause_resume_queued) {
        CHECK(boot_motor_position[X_AXIS] == 80 && boot_motor_pulses[X_AXIS] == 80);
        CHECK(sys.position[X_AXIS] == 80 && plan_get_current_block() == NULL);
        CHECK(boot_motion_ack_count() == (pause_single_block ? 0u : 1u));
        if(++pause_hold_visits == 4) {
            if(pause_single_block) {
                boot_control_signals.single_block = false;
                hal.control.interrupt_callback((control_signals_t){.single_block = true, .deasserted = true});
                CHECK(!sys.flags.single_block);
            }
            pause_resume_queued = true;
            CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
        }
    }
}
static void install_pause_motion_driver(void)
{
    install_boot_motion_driver();
    grbl.on_execute_delay = pause_motion_service;
}
static inline void run_boot_program_pause(const char *pause, bool disable_optional, bool expected_pause)
{
    if(pause_single_block)
        strcpy(pause_stream_program, "G1X1F100\nG91G1X1F100\n");
    else
        snprintf(pause_stream_program, sizeof(pause_stream_program), "G1X1F100\n%s\nG91G1X1F100\n", pause);
    boot_control_signals.stop_disable = disable_optional;
    boot_control_signals.single_block = pause_single_block;
    boot_during_setup = pause_switch_capability;
    prepare_boot_stream_motion(pause_stream_program);
    boot_during_init = install_pause_motion_driver;
    boot_on_realtime = pause_motion_service;
    CHECK(grbl_enter() == 0);
    check_boot_motion_completion();
    CHECK(pause_resume_queued == expected_pause);
    CHECK(pause_hold_visits == (expected_pause ? 4u : 0u));
    CHECK(boot_motor_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    CHECK(boot_motor_pulses[X_AXIS] == 160);
    CHECK(boot_motor_pulses[Y_AXIS] == 0 && boot_motor_pulses[Z_AXIS] == 0);
}
