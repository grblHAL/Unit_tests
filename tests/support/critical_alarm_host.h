#pragma once
#include "support/serial_loop_host.h"
#include "alarms.h"
static unsigned lock_resets;
static alarm_code_t lock_alarm = Alarm_HardLimit;
static control_signals_t lock_controls;
static unsigned lock_release_after_callbacks;
static bool lock_reset_requested_while_input_asserted;
static control_signals_t lock_control_state(void) { return lock_controls; }
static status_code_t lock_last_status;
static void lock_reset_read(void) { lock_resets++; }
static status_code_t lock_status(status_code_t status)
{ lock_last_status = status; status_calls++; return original_status(status); }
static void lock_foreground(sys_state_t state)
{
    /* Legacy critical-loop callbacks used ESTOP context; the public scheduler
       now passes the actual ALARM state. Both must remain critically locked. */
    CHECK(state == STATE_ESTOP || state == STATE_ALARM);
    CHECK(sys.alarm == lock_alarm && sys.blocking_event);
    CHECK(++realtime_calls < 1000);
    if(lock_release_after_callbacks && realtime_calls >= lock_release_after_callbacks)
        lock_controls.mask = 0;
    if(serial_text[serial_position] == 0 && status_calls >= expected_status_calls) {
        if(lock_controls.e_stop || lock_controls.motor_fault)
            lock_reset_requested_while_input_asserted = true;
        system_set_exec_state_flag(EXEC_RESET);
    }
}
static inline void run_critical_alarm_input(const char *text, unsigned responses)
{
    prepare_motion_program();
    serial_text = text; expected_status_calls = responses;
    hal.control.get_state = lock_control_state;
    hal.stream.is_connected = connected; hal.stream.read = serial_read;
    hal.stream.reset_read_buffer = lock_reset_read;
    report_init_fns(); report_init();
    original_status = grbl.report.status_message;
    grbl.report.status_message = lock_status;
    grbl.on_execute_realtime = lock_foreground;
    system_set_exec_alarm(lock_alarm);
    CHECK(!protocol_exec_rt_system());
    CHECK(sys.abort); CHECK(status_calls == responses);
    CHECK(serial_position == strlen(text)); CHECK(lock_resets == 1);
    CHECK(plan_get_current_block() == NULL);
}
