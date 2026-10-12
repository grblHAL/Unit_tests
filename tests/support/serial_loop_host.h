#pragma once
#include "support/motion_program_host.h"
#include "report.h"
#include <string.h>
static const char *serial_text;
static size_t serial_position;
static unsigned status_calls, expected_status_calls, realtime_calls;
static status_message_ptr original_status;
static bool connected(void) { return true; }
static control_signals_t controls(void) { return (control_signals_t){0}; }
static int32_t serial_read(void)
{
    while(serial_text[serial_position]) {
        uint8_t byte = (uint8_t)serial_text[serial_position++];
        if(!protocol_enqueue_realtime_command(byte)) return byte;
    }
    return SERIAL_NO_DATA;
}
static status_code_t record_status(status_code_t status)
{
    status_calls++;
    return original_status(status);
}
static void execute_foreground(sys_state_t state)
{
    CHECK(++realtime_calls < 200000);
    if(state == STATE_CYCLE || state == STATE_HOLD)
        stepper_driver_interrupt_handler();
    if(serial_text[serial_position] == 0 && status_calls >= expected_status_calls &&
       (state == STATE_IDLE || state == STATE_CHECK_MODE) && plan_get_current_block() == NULL && !st_is_stepping()) {
        sys.flags.exit = true;
        sys.abort = true;
    }
}
static inline void run_serial_program(const char *text, unsigned responses)
{
    prepare_motion_program();
    sys.cold_start = false;
    settings.homing.flags.nx_scrips_on_homed_only = true;
    serial_text = text;
    expected_status_calls = responses;
    hal.control.get_state = controls;
    hal.stream.is_connected = connected;
    hal.stream.read = serial_read;
    report_init_fns();
    report_init();
    original_status = grbl.report.status_message;
    grbl.report.status_message = record_status;
    grbl.on_execute_realtime = execute_foreground;
    CHECK(!protocol_main_loop());
    CHECK(status_calls == responses);
    CHECK(serial_position == strlen(text));
}
