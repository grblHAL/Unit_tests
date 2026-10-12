#pragma once
#include "support/canned_motion_host.h"
#include "spindle_control.h"
static spindle_state_t canned_spindle_state;
static unsigned canned_spindle_events;
static struct { spindle_state_t state; float rpm; int32_t z; } canned_spindle_log[16];
static void canned_spindle_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    CHECK(spindle == spindle_get(0));
    CHECK(canned_spindle_events < 16);
    canned_spindle_state = state;
    canned_spindle_log[canned_spindle_events].state = state;
    canned_spindle_log[canned_spindle_events].rpm = rpm;
    canned_spindle_log[canned_spindle_events++].z = physical_position[Z_AXIS];
}
static spindle_state_t canned_spindle_input(spindle_ptrs_t *spindle)
{
    CHECK(spindle == spindle_get(0));
    spindle_state_t state = canned_spindle_state;
    state.at_speed = true;
    return state;
}
static inline void prepare_canned_spindle(void)
{
    prepare_canned_motion();
    spindle_ptrs_t *spindle = spindle_get(0);
    spindle->cap.at_speed = spindle->cap.direction = true;
    spindle->rpm_min = 100;
    spindle->rpm_max = 12000;
    spindle->at_speed_tolerance = 1;
    spindle->set_state = canned_spindle_output;
    spindle->get_state = canned_spindle_input;
}
