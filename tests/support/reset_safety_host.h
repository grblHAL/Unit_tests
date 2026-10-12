#pragma once
#include "support/coolant_host.h"
static control_signals_t reset_controls;
static unsigned reset_driver_calls, reset_input_calls;
static control_signals_t reset_read_controls(void) { return reset_controls; }
static void reset_driver(void) { reset_driver_calls++; }
static void reset_input(void) { reset_input_calls++; }
static inline void prepare_reset_safety(void)
{
    prepare_coolant();
    hal.control.get_state = reset_read_controls;
    hal.driver_reset = reset_driver;
    hal.stream.reset_read_buffer = reset_input;
}
