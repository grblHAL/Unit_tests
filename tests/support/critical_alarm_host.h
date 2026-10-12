#pragma once
#include "support/serial_loop_host.h"
#include "alarms.h"
static unsigned lock_resets;
static status_code_t lock_last_status;
static void lock_reset_read(void) { lock_resets++; }
static status_code_t lock_status(status_code_t status)
{ lock_last_status = status; status_calls++; return original_status(status); }
static void lock_foreground(sys_state_t state)
{
    CHECK(state == STATE_ESTOP); CHECK(++realtime_calls < 1000);
    if(serial_text[serial_position] == 0 && status_calls >= expected_status_calls)
        system_set_exec_state_flag(EXEC_RESET);
}
static inline void run_critical_alarm_input(const char *text, unsigned responses)
{
    prepare_motion_program();
    serial_text = text; expected_status_calls = responses;
    hal.control.get_state = controls;
    hal.stream.is_connected = connected; hal.stream.read = serial_read;
    hal.stream.reset_read_buffer = lock_reset_read;
    report_init_fns(); report_init();
    original_status = grbl.report.status_message;
    grbl.report.status_message = lock_status;
    grbl.on_execute_realtime = lock_foreground;
    system_set_exec_alarm(Alarm_HardLimit);
    CHECK(!protocol_exec_rt_system());
    CHECK(sys.abort); CHECK(status_calls == responses);
    CHECK(serial_position == strlen(text)); CHECK(lock_resets == 1);
    CHECK(plan_get_current_block() == NULL);
}
