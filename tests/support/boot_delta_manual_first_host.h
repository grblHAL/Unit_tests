#pragma once
#include "support/boot_delta_manual_a_host.h"
static char manual_first_program[256];
static int32_t manual_first_physical_zero[N_AXIS];
static void observe_manual_a_then_xyz(axes_signals_t cycle, bool success)
{
    CHECK(success);
    if(manual_a_homing_events++ == 0) {
        CHECK(cycle.mask == A_AXIS_BIT && sys.homed.mask == A_AXIS_BIT);
        for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(boot_motor_pulses[axis] == 0);
    } else {
        CHECK(manual_a_homing_events == 2 && cycle.mask == 7 && sys.homed.mask == AXES_BITMASK);
        memcpy(manual_first_physical_zero, boot_motor_position, sizeof(manual_first_physical_zero));
        memcpy(position_after_xyz_home, sys.position, sizeof(position_after_xyz_home));
        memcpy(pulses_after_xyz_home, boot_motor_pulses, sizeof(pulses_after_xyz_home));
        for(unsigned axis = 0; axis < 3; axis++) CHECK(sys.position[axis] == 0 && boot_motor_pulses[axis] > 80);
    }
}
static void install_manual_a_first(void)
{
    install_manual_a_driver();
    unsigned automatic_options = settings.homing.flags.value;
    settings.homing.flags.manual = true;
    unsigned manual_options = settings.homing.flags.value;
    settings.homing.flags.manual = false;
    snprintf(manual_first_program, sizeof(manual_first_program),
        "$22=%u\n$HA\n$22=%u\n$H\n%s", manual_options, automatic_options, manual_a_tail);
    boot_program = manual_first_program;
    manual_a_expected_responses = 0;
    for(const char *line = boot_program; *line; line++)
        if(*line == '\n') manual_a_expected_responses++;
    grbl.on_homing_completed = observe_manual_a_then_xyz;
}
static void prepare_delta_manual_first(const char *tail, unsigned expected_acks)
{
    prepare_delta_manual_a(tail, expected_acks);
    boot_during_init = install_manual_a_first;
}
