#pragma once
#include "support/stepper_host.h"
#include <string.h>
static inline void prepare_motion_program(void)
{
    prepare_stepper();
    settings.arc_tolerance = .02f;
}
static inline void queue_motion_program(const char *text)
{
    char block[128];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    CHECK(gc_execute_block(block) == Status_OK);
    CHECK(plan_get_current_block() != NULL);
}
static inline void execute_motion_program(void)
{
    state_set(STATE_CYCLE);
    CHECK(wake_calls == 1);
    for(unsigned ticks = 0; ticks < 100000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
    CHECK(plan_get_current_block() == NULL);
}
