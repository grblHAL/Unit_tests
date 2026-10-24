#pragma once
#include "support/boot_delta_homing_host.h"
static unsigned manual_a_homing_events, manual_a_expected_acks, manual_a_expected_responses;
static unsigned pulses_after_xyz_home[N_AXIS];
static int32_t position_after_xyz_home[N_AXIS], position_after_manual_a[N_AXIS];
static bool manual_a_finished;
static char manual_a_program[192];
static const char *manual_a_tail;
static void observe_xyz_and_manual_a(axes_signals_t cycle, bool success)
{
    CHECK(success);
    if(manual_a_homing_events++ == 0) {
        CHECK(cycle.mask == 7 && sys.homed.mask == 7);
        memcpy(pulses_after_xyz_home, boot_motor_pulses, sizeof(pulses_after_xyz_home));
        memcpy(position_after_xyz_home, sys.position, sizeof(position_after_xyz_home));
    } else {
        CHECK(manual_a_homing_events == 2 && cycle.mask == A_AXIS_BIT);
        CHECK(sys.homed.mask == AXES_BITMASK);
        for(unsigned axis = 0; axis < N_AXIS; axis++)
            CHECK(boot_motor_pulses[axis] == pulses_after_xyz_home[axis]);
        memcpy(position_after_manual_a, sys.position, sizeof(position_after_manual_a));
    }
}
static unsigned manual_a_command_responses(void)
{
    unsigned count = boot_motion_ack_count();
    const char *cursor = engine_output;
    while((cursor = strstr(cursor, "error:"))) {
        CHECK(cursor == engine_output || cursor[-1] == '\n');
        if(strchr(cursor, '\n')) count++;
        cursor += strlen("error:");
    }
    return count;
}
static void service_manual_a(sys_state_t state)
{
    boot_homing_foreground(state);
    if(state == STATE_JOG && boot_homing_timer_running)
        stepper_driver_interrupt_handler();
    if(!manual_a_finished && boot_reads == strlen(boot_program) &&
       manual_a_command_responses() == manual_a_expected_responses && state == STATE_IDLE && !plan_get_current_block()) {
        manual_a_finished = true;
        CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    }
}
static void install_manual_a_driver(void)
{
    install_delta_homing_driver();
    settings.homing.flags.manual = true;
    unsigned manual_options = settings.homing.flags.value;
    settings.homing.flags.manual = false;
    memset(settings.homing.cycle, 0, sizeof(settings.homing.cycle));
    settings.homing.cycle[0].mask = 7;
    hal.home_cap.a.mask = 7; /* Three delta switches; operator references the auxiliary axis. */
    settings_write_global();
    snprintf(manual_a_program, sizeof(manual_a_program), "$H\n$22=%u\n$HA\n%s", manual_options, manual_a_tail);
    boot_program = manual_a_program;
    for(const char *line = boot_program; *line; line++)
        if(*line == '\n') manual_a_expected_responses++;
    grbl.on_homing_completed = observe_xyz_and_manual_a;
    grbl.on_execute_delay = service_manual_a;
}
static void prepare_delta_manual_a(const char *tail, unsigned expected_acks)
{
    manual_a_tail = tail;
    manual_a_expected_acks = expected_acks;
    prepare_boot_delta_homing(false);
    boot_during_init = install_manual_a_driver;
    boot_on_realtime = service_manual_a;
}
