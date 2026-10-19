#pragma once
#include "support/spindle_sync_motion_host.h"
static bool sync_parser_driver_running;
static void sync_parser_wake(void)
{
    sync_parser_driver_running = true;
    wake_driver();
}
static void sync_parser_idle(bool clear)
{
    sync_parser_driver_running = false;
    idle_driver(clear);
}
static void service_sync_parser_driver(sys_state_t state)
{
    sync_motion_realtime(state);
    CHECK(sync_realtime_calls < 100000);
    /* Encoder feedback advances independently. Step interrupts run only after
       each driver wakeup, never during that move's index acquisition wait. */
    if(sync_parser_driver_running && (state & (STATE_CYCLE | STATE_HOLD))) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}
static inline void prepare_sync_parser(void)
{
    prepare_spindle_sync_motion();
    hal.stepper.wake_up = sync_parser_wake;
    hal.stepper.go_idle = sync_parser_idle;
    grbl.on_execute_realtime = service_sync_parser_driver;
}
static inline status_code_t sync_parser_block(const char *text)
{
    char block[96];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
