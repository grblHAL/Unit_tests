#pragma once
#include "support/laser_program_host.h"
#include "support/motion_program_host.h"
static inline void prepare_pwm_stepper_mode(machine_mode_t mode)
{
    prepare_pwm_program_mode(mode, false);
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].acceleration = 36000;
    hal.f_step_timer = 1000000;
    hal.stepper.enable = enable_motors;
    hal.stepper.go_idle = idle_driver;
    hal.stepper.wake_up = wake_driver;
    hal.stepper.cycles_per_tick = timer_cycles;
    hal.stepper.pulse_start = pulse_driver;
    st_reset();
}

static inline void prepare_laser_stepper(void)
{ prepare_pwm_stepper_mode(Mode_Laser); }
