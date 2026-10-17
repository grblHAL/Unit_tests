#pragma once
#include "support/motion_program_host.h"

/* A configured 200 mm/s machine reaches cruise within a 300 mm move.
   This checks timer/pulse output, not mechanical acceleration or missed steps. */
static uint32_t fast_timer_period;
static uint64_t fast_elapsed_cycles, fast_sample_start, fast_sample_end;
static void fast_timer(uint32_t cycles)
{
    CHECK(cycles > 0);
    fast_timer_period = cycles;
}
static void fast_pulse(stepper_t *stepper)
{
    pulse_driver(stepper);
    if(axis_pulses[X_AXIS] == 9600 && !fast_sample_start) fast_sample_start = fast_elapsed_cycles;
    if(axis_pulses[X_AXIS] == 14400 && !fast_sample_end) fast_sample_end = fast_elapsed_cycles;
}
static void prepare_fast_motion(void)
{
    prepare_motion_program();
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        char maximum[] = "15000", acceleration[] = "200";
        CHECK(settings_store_setting(Setting_AxisMaxRate + axis, maximum) == Status_OK);
        CHECK(settings_store_setting(Setting_AxisAcceleration + axis, acceleration) == Status_OK);
    }
    hal.stepper.cycles_per_tick = fast_timer;
    hal.stepper.pulse_start = fast_pulse;
}
static inline void finish_fast_motion(float y, float z, bool return_to_origin)
{
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 300000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); tick++) {
        st_prep_buffer();
        fast_elapsed_cycles += fast_timer_period;
        stepper_driver_interrupt_handler();
    }
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
    CHECK(plan_get_current_block() == NULL && fast_sample_end > fast_sample_start);
    float length = sqrtf(300 * 300 + y * y + z * z);
    float measured_feed = (60.0f * length / 300.0f) * 60.0f * hal.f_step_timer / (float)(fast_sample_end - fast_sample_start);
    fprintf(stderr, "Cruise feed from 60 mm X pulse window: %.3f mm/min\n", measured_feed);
    CHECK(fabsf(measured_feed - 12000) < 120); /* One percent timer quantization allowance. */
    float endpoint[N_AXIS] = {300, y, z};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        unsigned steps = (unsigned)lroundf(endpoint[axis] * settings.axis[axis].steps_per_mm);
        CHECK(axis_pulses[axis] == steps * (return_to_origin ? 2u : 1u));
        CHECK(physical_position[axis] == (return_to_origin ? 0 : (int32_t)steps));
        CHECK(sys.position[axis] == physical_position[axis]);
    }
}
