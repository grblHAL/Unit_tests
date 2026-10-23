#pragma once
#include "support/ram_macro_protocol_host.h"
#include "support/motion_program_host.h"
static unsigned scoped_motion_services;
static void service_scoped_motion(sys_state_t state)
{
    CHECK(++scoped_motion_services < 200000);
    if(state == STATE_CYCLE || state == STATE_HOLD) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}
static void install_scoped_motion(void)
{
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = pulse_driver;
    st_reset();
    grbl.on_execute_realtime = service_scoped_motion;
}
