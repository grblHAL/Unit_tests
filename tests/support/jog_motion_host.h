#pragma once
#include "support/system_command_host.h"
#include "support/motion_program_host.h"
static inline void prepare_jog_motion(void)
{
    prepare_system_command();
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = pulse_driver;
    st_reset();
}
static inline void finish_jog_motion(void)
{
    CHECK(state_get() == STATE_JOG);
    for(unsigned ticks = 0; ticks < 100000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
    CHECK(plan_get_current_block() == NULL);
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE);
}
static inline void prepare_jog_envelope(void)
{
    sys.homed.mask = AXES_BITMASK;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        settings.axis[axis].max_travel = -10;
        sys.work_envelope.min.values[axis] = -10;
        sys.work_envelope.max.values[axis] = 0;
    }
}
