#pragma once
#include "support/fast_motion_host.h"
static uint64_t override_window_start, override_window_end;
static unsigned override_sample_start_step = 20800, override_sample_end_step = 22400;
static void fast_override_pulse(stepper_t *stepper)
{
    fast_pulse(stepper);
    if(axis_pulses[X_AXIS] == override_sample_start_step && !override_window_start) override_window_start = fast_elapsed_cycles;
    if(axis_pulses[X_AXIS] == override_sample_end_step && !override_window_end) override_window_end = fast_elapsed_cycles;
}
static inline void queue_short_fast_segments(void)
{
    queue_motion_program("G1X150F12000");
    /* Collinear CAM segments are shorter than the distance needed to slow
       from the original feed to the new override feed. */
    CHECK(plan_get_block_buffer_available() >= 12);
    for(unsigned i = 1; i <= 10; i++) {
        char block[48];
        snprintf(block, sizeof(block), "G1X%.1f", 150.0f + .5f * i);
        queue_motion_program(block);
    }
    queue_motion_program("G1X300");
}
static inline void run_fast_override(bool restore)
{
    prepare_fast_motion();
    hal.stepper.pulse_start = fast_override_pulse;
    queue_short_fast_segments();
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    bool reduced = false, restored = false;
    for(unsigned tick = 0; tick < 300000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); tick++) {
        st_prep_buffer();
        fast_elapsed_cycles += fast_timer_period;
        stepper_driver_interrupt_handler();
        if(!reduced && physical_position[X_AXIS] >= 11760) {
            reduced = true;
            for(unsigned i = 0; i < 9; i++) CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_COARSE_MINUS));
            CHECK(protocol_exec_rt_system());
            CHECK(sys.override.feed_rate == 10);
        }
        if(restore && !restored && physical_position[X_AXIS] >= 22800) {
            restored = true;
            CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_FEED_RESET));
            CHECK(protocol_exec_rt_system());
            CHECK(sys.override.feed_rate == 100);
        }
    }
    CHECK(reduced && restored == restore && (sys.rt_exec_state & EXEC_CYCLE_COMPLETE));
    CHECK(override_window_end > override_window_start);
    float span = (float)(override_sample_end_step - override_sample_start_step) / settings.axis[X_AXIS].steps_per_mm;
    float feed = span * 60.0f * hal.f_step_timer / (float)(override_window_end - override_window_start);
    fprintf(stderr, "Reduced cruise feed: %.3f mm/min\n", feed);
    CHECK(fabsf(feed - 1200) < 24);
    CHECK(axis_pulses[X_AXIS] == 24000 && physical_position[X_AXIS] == 24000);
    CHECK(sys.position[X_AXIS] == 24000 && gc_state.position[X_AXIS] == 300);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
}
