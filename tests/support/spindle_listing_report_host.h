#pragma once
#include "support/engine_host.h"
#include "spindle_control.h"
#include "report.h"
#include "check.h"
#include <string.h>
static spindle_state_t report_spindle_state(spindle_ptrs_t *spindle)
{
    (void)spindle;
    return (spindle_state_t){0};
}
static void report_spindle_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    (void)spindle; (void)state; (void)rpm;
}
static spindle_ptrs_t listed_spindle = {
    .type = SpindleType_Basic, .get_state = report_spindle_state,
    .set_state = report_spindle_output
};
static void prepare_spindle_listing(void)
{
    engine_prepare();
    CHECK(spindle_register(&listed_spindle, "fixture spindle") == 0);
    if(listed_spindle.cap.laser)
        settings.mode = Mode_Laser;
    CHECK(spindle_select(0));
    CHECK(spindle_is_enabled(0));
    report_init_fns();
    report_init();
    engine_output[0] = 0;
}
