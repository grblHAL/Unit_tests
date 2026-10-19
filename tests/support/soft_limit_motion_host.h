#pragma once
#include "support/motion_program_host.h"
static unsigned soft_service_calls, soft_read_resets, soft_driver_resets;
static bool soft_hold_seen, soft_idle_seen, soft_alarm_seen, soft_status_requested, soft_reset_requested;
static bool soft_reset_during_hold, soft_hold_reset_sent;
static int32_t soft_stopped_position[N_AXIS];
static unsigned soft_stopped_pulses[N_AXIS];
static control_signals_t soft_controls(void) { return (control_signals_t){0}; }
static coolant_state_t soft_coolant(void) { return (coolant_state_t){0}; }
static void soft_coolant_off(coolant_state_t state) { CHECK(state.mask == 0); }
static bool soft_connected(void) { return true; }
static int32_t soft_no_input(void) { return SERIAL_NO_DATA; }
static void soft_reset_read(void) { soft_read_resets++; }
static void soft_reset_driver(void) { soft_driver_resets++; }
static void service_soft_limit(sys_state_t state)
{
    CHECK(++soft_service_calls < 200000);
    engine_ticks++;
    if(state == STATE_HOLD) soft_hold_seen = true;
    if(state == STATE_CYCLE || state == STATE_HOLD) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
        if(state == STATE_HOLD && soft_reset_during_hold && !soft_hold_reset_sent && st_is_stepping()) {
            CHECK(protocol_enqueue_realtime_command(CMD_RESET));
            soft_hold_reset_sent = true;
        }
    }
    if(state == STATE_IDLE && sys.flags.soft_limit) {
        CHECK(!st_is_stepping());
        soft_idle_seen = true;
    }
    if(state == STATE_ALARM) {
        if(soft_reset_during_hold) {
            CHECK(sys.abort && sys.position_lost && sys.alarm == Alarm_AbortCycle);
            CHECK(!sys.blocking_event && !st_is_stepping());
            return;
        }
        CHECK(sys.alarm == Alarm_SoftLimit && sys.blocking_event);
        CHECK(soft_driver_resets == 1);
        CHECK(!st_is_stepping() && !sys.position_lost);
        if(!soft_alarm_seen) {
            memcpy(soft_stopped_position, physical_position, sizeof(physical_position));
            memcpy(soft_stopped_pulses, axis_pulses, sizeof(axis_pulses));
            soft_alarm_seen = true;
        }
        CHECK(memcmp(soft_stopped_position, physical_position, sizeof(physical_position)) == 0);
        CHECK(memcmp(soft_stopped_pulses, axis_pulses, sizeof(axis_pulses)) == 0);
        if(!soft_status_requested) {
            CHECK(protocol_enqueue_realtime_command(CMD_STATUS_REPORT));
            soft_status_requested = true;
        } else if(strstr(engine_output, "<Alarm")) {
            CHECK(protocol_enqueue_realtime_command(CMD_RESET));
            soft_reset_requested = true;
        }
    }
}
static inline void prepare_soft_limit_motion(void)
{
    prepare_motion_program();
    sys.cold_start = false;
    settings.homing.flags.enabled = true;
    settings.limits.soft_enabled.mask = sys.soft_limits.mask = sys.homed.mask = AXES_BITMASK;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        settings.axis[axis].max_travel = -50;
        sys.work_envelope.min.values[axis] = -50;
        sys.work_envelope.max.values[axis] = 0;
    }
    hal.control.get_state = soft_controls;
    hal.coolant.get_state = soft_coolant;
    hal.coolant.set_state = soft_coolant_off;
    hal.stream.is_connected = soft_connected;
    hal.stream.read = soft_no_input;
    hal.stream.reset_read_buffer = soft_reset_read;
    hal.driver_reset = soft_reset_driver;
    grbl.on_execute_realtime = service_soft_limit;
    report_init_fns();
    report_init();
}
static inline void request_outside_soft_limits(void)
{
    float target[N_AXIS] = {-60};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    CHECK(mc_line(target, &data) == Status_Aborted);
    CHECK(soft_alarm_seen && soft_status_requested && soft_reset_requested);
    CHECK(sys.abort && sys.flags.soft_limit && sys.alarm == Alarm_SoftLimit);
    CHECK(!sys.position_lost);
    CHECK(soft_read_resets == 1);
    /* Automatic alarm shutdown, then the sender's explicit reset. */
    CHECK(soft_driver_resets == 2);
    CHECK(strstr(engine_output, "ALARM:2") != NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == physical_position[axis]);
    CHECK(engine_irq_depth == 0);
}
