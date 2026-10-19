#pragma once
#include "support/probe_motion_host.h"
#include "support/backlash_settings_host.h"
static inline void probe_then_compensated_followup(bool reverse)
{
    prepare_probe_motion();
    CHECK(store_backlash("0.1") == Status_OK);
    char probe_command[] = "G38.2X1F100";
    CHECK(gc_execute_block(probe_command) == Status_OK);
    CHECK(sys.flags.probe_succeeded && sys.probe_position[X_AXIS] == 40);
    CHECK(completed_calls == 1);
    int32_t stopped = sys.position[X_AXIS], motor_stopped = physical_position[X_AXIS];
    unsigned before = axis_pulses[X_AXIS], wakes = wake_calls;
    CHECK(stopped >= 40 && stopped < 60);
    CHECK(motor_stopped - stopped == 8);
    NEAR(gc_state.position[X_AXIS], stopped / settings.axis[X_AXIS].steps_per_mm);
    queue_motion_program(reverse ? "G91G1X-0.25F100" : "G91G1X0.25F100");
    state_set(STATE_CYCLE);
    CHECK(wake_calls == wakes + 1);
    for(unsigned ticks = 0; ticks < 100000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
    CHECK(plan_get_current_block() == NULL);
    int32_t travel = reverse ? -20 : 20;
    CHECK(sys.position[X_AXIS] == stopped + travel);
    CHECK(axis_pulses[X_AXIS] - before == (reverse ? 28u : 20u));
    CHECK(physical_position[X_AXIS] == motor_stopped + travel - (reverse ? 8 : 0));
    NEAR(gc_state.position[X_AXIS], (stopped + travel) / settings.axis[X_AXIS].steps_per_mm);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
}
