#pragma once
#include "support/hold_spindle_host.h"
#include "override.h"
static coolant_state_t stop_coolant;
static unsigned stop_cancel_calls, stop_reset_calls, stop_timer_calls;
static coolant_state_t stop_get_coolant(void) { return stop_coolant; }
static void stop_set_coolant(coolant_state_t state) { stop_coolant = state; }
static void stop_cancel_input(void) { stop_cancel_calls++; }
static void stop_reset_driver(void) { stop_reset_calls++; }
static void service_stop_timer(sys_state_t state)
{
    (void)state;
    CHECK(++stop_timer_calls < 200000);
    stepper_driver_interrupt_handler();
}
static inline void start_stop_motion(void)
{
    prepare_motion_program();
    hal.control.get_state = hold_spindle_controls;
    hal.stream.is_connected = hold_spindle_connected;
    hal.stream.cancel_read_buffer = stop_cancel_input;
    hal.driver_reset = stop_reset_driver;
    hal.coolant.get_state = stop_get_coolant;
    hal.coolant.set_state = stop_set_coolant;
    hal.coolant_cap.flood = true;
    spindle_ptrs_t *spindle = spindle_get(0);
    spindle->cap.variable = true;
    spindle->rpm_min = 100;
    spindle->rpm_max = 12000;
    spindle->set_state = hold_spindle_set;
    spindle->get_state = hold_spindle_get;
    char spindle_command[] = "M3S5000", coolant_command[] = "M8";
    CHECK(gc_execute_block(spindle_command) == Status_OK);
    CHECK(gc_execute_block(coolant_command) == Status_OK);
    queue_motion_program("G1X20F100");
    queue_motion_program("G1X40F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(axis_pulses[X_AXIS] > 0 && axis_pulses[X_AXIS] < 1600);
    grbl.on_execute_realtime = service_stop_timer;
}
static inline void stop_program(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_STOP));
    /* Stop returns cancellation, unlike abort/reset. Main loop clears cancel. */
    CHECK(!protocol_exec_rt_system());
    CHECK(sys.cancel && !sys.abort);
    CHECK(stop_cancel_calls == 1 && stop_reset_calls == 1);
    CHECK(state_get() == STATE_IDLE && !sys.suspend);
    CHECK(plan_get_current_block() == NULL && !st_is_stepping());
    CHECK(!hold_spindle_output_state.on && stop_coolant.value == 0);
    CHECK(!gc_spindle_get(0)->state.on && gc_state.modal.coolant.value == 0);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    NEAR(gc_state.position[X_AXIS], (float)physical_position[X_AXIS] / settings.axis[X_AXIS].steps_per_mm);
    CHECK(!sys.position_lost && sys.alarm == Alarm_None);
}
