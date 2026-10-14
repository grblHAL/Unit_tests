#pragma once
#include "support/homing_host.h"
static control_signals_t homing_command_controls;
static control_signals_t homing_command_control_state(void) { return homing_command_controls; }
static inline void prepare_homing_command(void)
{
    prepare_homing(); hal.control.get_state = homing_command_control_state;
    stored_line_t empty = "";
    settings_write_startup_line(0, empty); settings_write_startup_line(1, empty);
}
static inline status_code_t execute_homing_command(const char *text)
{
    char line[16]; CHECK(strlen(text) < sizeof(line)); strcpy(line,text);
    return system_execute_line(line, hal.stream.write);
}
static inline void check_no_command_homing_motion(void)
{
    CHECK(homing_calls == 0 && wake_calls == 0 && completed_calls == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    CHECK(sys.homed.mask == 0);
}

static inline void prepare_manual_homing_command(void)
{
    prepare_homing_command(); settings.homing.flags.manual = true;
    for(unsigned cycle = 0; cycle < N_AXIS; cycle++) settings.homing.cycle[cycle].mask = 0;
    limits_set_homing_axes();
    for(unsigned axis = 0; axis < N_AXIS; axis++) sys.position[axis] = 100 + axis;
}
static inline void check_manual_command_axis(unsigned axis)
{
    CHECK(sys.homed.mask == (1u << axis));
    for(unsigned i = 0; i < N_AXIS; i++) {
        CHECK(sys.position[i] == (i == axis ? 0 : (int32_t)(100 + i)));
        CHECK(axis_pulses[i] == 0);
    }
    CHECK(wake_calls == 0 && completed_calls == 1 && homing_success);
}
