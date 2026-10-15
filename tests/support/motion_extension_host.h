#pragma once
#include "support/cutter_parser_host.h"
#include "state_machine.h"

static mc_line_ptr previous_line_extension;
static mc_arc_ptr previous_arc_extension;
static unsigned extension_line_calls, extension_arc_calls;
static bool extension_accept = true;
static float extension_target[N_AXIS], extension_feed;
static int32_t extension_turns;
static plane_t extension_plane;
static status_code_t extend_line(float *target, plan_line_data_t *data)
{
    extension_line_calls++;
    memcpy(extension_target, target, sizeof(extension_target));
    extension_feed = data->feed_rate;
    return extension_accept ? previous_line_extension(target, data) : Status_GcodeInvalidTarget;
}
static status_code_t extend_arc(float *target, plan_line_data_t *data, float *position,
                               float *offset, float radius, plane_t plane, int32_t turns)
{
    extension_arc_calls++;
    memcpy(extension_target, target, sizeof(extension_target));
    extension_feed = data->feed_rate;
    extension_turns = turns;
    extension_plane = plane;
    return extension_accept ? previous_arc_extension(target, data, position, offset, radius, plane, turns)
                            : Status_GcodeInvalidTarget;
}
static inline void prepare_motion_extension(void)
{
    prepare_cutter_parser();
    settings.arc_tolerance = .02f;
    state_set(STATE_IDLE);
    previous_line_extension = grbl.mc_line;
    previous_arc_extension = grbl.mc_arc;
    CHECK(previous_line_extension != NULL && previous_arc_extension != NULL);
    grbl.mc_line = extend_line;
    grbl.mc_arc = extend_arc;
}
