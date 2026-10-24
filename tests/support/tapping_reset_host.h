#pragma once
#include "support/thread_reset_motion_host.h"

static spindle_state_t tapping_feedback(spindle_ptrs_t *spindle)
{
    spindle_state_t state = thread_encoder_input(spindle);
    state.at_speed = true;
    return state;
}
static void configure_tapping_driver(spindle_ptrs_t *driver)
{
    driver->cap.at_speed = true;
    driver->get_state = tapping_feedback;
    driver->at_speed_tolerance = 1;
}
static void prepare_tapping_reset(void)
{
    configure_thread_encoder_driver = configure_tapping_driver;
    prepare_thread_reset();
    CHECK(sync_parser_block("G17") == Status_OK);
    CHECK(spindle_get(0)->cap.at_speed && thread_encoder_state.on && !thread_encoder_state.ccw);
}
