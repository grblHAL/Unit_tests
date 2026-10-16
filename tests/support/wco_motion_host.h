#pragma once
#include "support/motion_program_host.h"
static unsigned forced_wco_requests;
static void (*observe_wco_motion_tick)(void);
static void observe_motion_wco(report_tracking_flags_t flags)
{
    if(flags.force_wco) {
        CHECK(flags.wco && state_get() == STATE_CYCLE);
        forced_wco_requests++;
    }
}
static inline void wco_block(const char *text)
{
    char block[64];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    CHECK(gc_execute_block(block) == Status_OK);
}
static inline void run_two_offset_moves(float first_offset, float second_offset)
{
    bool saw_first = false, saw_second = false;
    grbl.on_rt_reports_added = observe_motion_wco;
    state_set(STATE_CYCLE);
    for(unsigned ticks = 0; ticks < 100000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        engine_execute_tasks(STATE_CYCLE);
        if(observe_wco_motion_tick) observe_wco_motion_tick();
        if(physical_position[X_AXIS] < 80) {
            NEAR(gc_get_offset(X_AXIS, true), first_offset);
            saw_first = true;
        /* At the shared endpoint, the first block can still be finishing. */
        } else if(physical_position[X_AXIS] > 80 && physical_position[X_AXIS] < 160) {
            NEAR(gc_get_offset(X_AXIS, true), second_offset);
            saw_second = true;
        }
    }
    CHECK(saw_first && saw_second && forced_wco_requests == 1);
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
    CHECK(physical_position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    CHECK(plan_get_current_block() == NULL);
}
