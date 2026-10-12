#pragma once
#include "support/engine_host.h"
#include "stepper.h"
#include "state_machine.h"
#include "protocol.h"
#include "motion_control.h"
#include "check.h"
static unsigned axis_pulses[N_AXIS];
static int32_t physical_position[N_AXIS];
static unsigned wake_calls;
static void enable_motors(axes_signals_t axes, bool hold) { (void)axes; (void)hold; }
static void idle_driver(bool clear) { (void)clear; }
static void wake_driver(void) { wake_calls++; }
static void timer_cycles(uint32_t cycles) { CHECK(cycles > 0); }
static void pulse_driver(stepper_t *stepper)
{
    for(unsigned i = 0; i < N_AXIS; i++)
        if(stepper->step_out.mask & (1u << i)) {
            axis_pulses[i]++;
            physical_position[i] += stepper->dir_out.mask & (1u << i) ? -1 : 1;
        }
}
static inline void prepare_stepper(void)
{
    engine_parser_prepare();
    grbl.on_execute_realtime = protocol_execute_noop;
    state_set(STATE_IDLE);
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = pulse_driver;
    st_reset();
    CHECK(wake_calls == 0);
}
static inline void run_stepper_move(float x, float y, float z)
{
    float target[N_AXIS] = {x, y, z};
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.condition.target_validated = data.condition.target_valid = true;
    CHECK(mc_line(target, &data) == Status_Handled);
    state_set(STATE_CYCLE);
    CHECK(state_get() == STATE_CYCLE);
    CHECK(wake_calls == 1);
    for(unsigned ticks = 0; ticks < 100000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
    CHECK(plan_get_current_block() == NULL);
}
