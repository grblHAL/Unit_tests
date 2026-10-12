#pragma once
#include "support/motion_program_host.h"
#include "report.h"
static unsigned canned_realtime_calls;
static control_signals_t canned_controls(void) { return (control_signals_t){0}; }
static bool canned_connected(void) { return true; }
static void canned_foreground(sys_state_t state)
{
    CHECK(++canned_realtime_calls < 200000);
    if(state == STATE_CYCLE || state == STATE_HOLD)
        stepper_driver_interrupt_handler();
}
static inline void prepare_canned_motion(void)
{
    prepare_motion_program();
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        settings.axis[axis].acceleration = 36000;
    hal.control.get_state = canned_controls;
    hal.stream.is_connected = canned_connected;
    grbl.on_execute_realtime = canned_foreground;
    report_init_fns();
    report_init();
}
static inline status_code_t canned_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
static inline void execute_canned(const char *text)
{
    CHECK(canned_block(text) == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(plan_get_current_block() == NULL);
}
