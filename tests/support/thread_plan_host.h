#pragma once
#include "support/sync_parser_host.h"
#include "motion_control.h"
static unsigned thread_move_count;
static struct { float xyz[N_AXIS]; plan_line_data_t data; } thread_moves[256];
bool __wrap_plan_buffer_line(float *target, plan_line_data_t *data)
{
    CHECK(thread_move_count < 256);
    memcpy(thread_moves[thread_move_count].xyz, target, sizeof(float) * N_AXIS);
    thread_moves[thread_move_count++].data = *data;
    return true;
}
static control_signals_t thread_controls(void) { return (control_signals_t){0}; }
static bool thread_connected(void) { return true; }
static inline void prepare_thread_plan(void)
{
    prepare_sync_parser();
    hal.control.get_state = thread_controls;
    hal.stream.is_connected = thread_connected;
    state_set(STATE_IDLE);
}
static inline void prepare_thread_parser_plan(void)
{
    prepare_thread_plan();
    /* Programmed/measured 2000 RPM with enough Z feed capacity for inch pitch. */
    settings.axis[Z_AXIS].max_rate = 5000;
}
static inline gc_thread_data basic_thread(void)
{
    return (gc_thread_data){.pitch = 1, .z_final = 10, .peak = 1,
        .initial_depth = 0.5f, .depth = 1, .depth_degression = 1, .cut_direction = 1};
}
static inline void capture_thread(gc_thread_data *thread)
{
    float position[N_AXIS] = {0};
    plan_line_data_t data = {0};
    data.spindle.hal = spindle_get(0);
    data.feed_rate = thread->pitch;
    mc_thread(&data, position, thread, false);
}
