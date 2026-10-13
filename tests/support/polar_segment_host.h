#pragma once
#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "planner.h"
#include "check.h"
#include <math.h>
#include <string.h>

void polar_init(void);
static bool polar_connected(void) { return true; }
static unsigned polar_previous_completion_calls, polar_previous_report_calls;
static program_flow_t polar_completion;
static bool polar_completion_check;
static void polar_previous_completion(program_flow_t flow, bool check_mode)
{
    polar_previous_completion_calls++;
    polar_completion = flow;
    polar_completion_check = check_mode;
}
static void polar_previous_report(bool newopt)
{
    (void)newopt;
    polar_previous_report_calls++;
}
static inline void prepare_polar_segments(void)
{
    engine_prepare();
    hal.stream.is_connected = polar_connected;
    grbl.on_program_completed = polar_previous_completion;
    grbl.on_report_options = polar_previous_report;
    polar_init();
    CHECK(plan_reset());
}
static inline coord_data_t polar_start_at(coord_data_t target)
{
    coord_data_t origin = {0};
    plan_line_data_t data = {.feed_rate = 100, .condition = {.rapid_motion = true}};
    CHECK(kinematics.segment_line(&target, &origin, &data, true) != NULL);
    coord_data_t *segment = kinematics.segment_line(&target, NULL, &data, false);
    CHECK(segment != NULL);
    coord_data_t start = *segment;
    CHECK(kinematics.segment_line(&target, NULL, &data, false) == NULL);
    return start;
}
static inline coord_data_t polar_cartesian(const coord_data_t *joint)
{
    return (coord_data_t){.x = joint->x * cosf(joint->y * RADDEG),
        .y = joint->x * sinf(joint->y * RADDEG), .z = joint->z};
}
