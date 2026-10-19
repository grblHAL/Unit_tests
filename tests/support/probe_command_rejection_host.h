#pragma once
#include "support/probe_motion_host.h"
static inline void reject_probe_then_measure_contact(const char *text, status_code_t expected)
{
    prepare_probe_motion();
    char command[64];
    CHECK(strlen(text) < sizeof(command));
    strcpy(command, text);
    status_code_t actual = gc_execute_block(command);
    if(actual != expected)
        fprintf(stderr, "Probe command '%s': status=%u expected=%u\n", text, (unsigned)actual, (unsigned)expected);
    CHECK(actual == expected);
    CHECK(plan_get_current_block() == NULL && completed_calls == 0);
    CHECK(!hal.probe.get_state().is_probing && sys.alarm == Alarm_None);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0);
    char valid[] = "G38.2X1F100";
    CHECK(gc_execute_block(valid) == Status_OK);
    CHECK(sys.flags.probe_succeeded && sys.probe_position[X_AXIS] == 40);
    CHECK(completed_calls == 1 && sys.alarm == Alarm_None);
    NEAR(gc_state.position[X_AXIS], (float)sys.position[X_AXIS] / settings.axis[X_AXIS].steps_per_mm);
}
